#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fcntl.h> // for _O_U8TEXT
#include <io.h> // for _setmode
#include <thread>
#include <chrono>

// 回调函数用于收集子窗口句柄
BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam) {
    auto& windows = *reinterpret_cast<std::vector<HWND>*>(lParam);
    windows.push_back(hwnd);
    return TRUE; // 继续枚举下一个子窗口
}

void TypeTextInTextBox(HWND hwndTextBox, LPCWSTR text) {
    // 激活文本框
    SetFocus(hwndTextBox);

    // 发送文本到文本框
    SendMessage(hwndTextBox, WM_SETTEXT, 0, (LPARAM)text);

    // 延迟 500 毫秒
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void PrintWindowInfo(HWND hwnd) {
    wchar_t className[256];
    wchar_t windowText[256];

    // 获取窗口类名
    GetClassName(hwnd, className, sizeof(className) / sizeof(className[0]));

    // 获取窗口样式
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);

    // 获取窗口标题（包括对 EDIT 和 RichEdit 控件的处理）
    int length = GetWindowTextLength(hwnd);
    std::wstring text(length, L'\0');
    GetWindowText(hwnd, &text[0], length + 1);

    if (className == std::wstring(L"WindowsForms10.EDIT.app.0.141b42a_r8_ad1") ||
        className == std::wstring(L"WindowsForms10.RichEdit20W.app.0.141b42a_r8_ad1")) {
        // 尝试获取更多文本内容
        length = SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);
        text.resize(length);
        SendMessage(hwnd, WM_GETTEXT, length + 1, (LPARAM)&text[0]);
    }

    // 打印信息
    std::wcout << text << std::endl;
    std::wcout << L"--------------------------" << std::endl;
}

HWND FindChildWindowByTitle(HWND parent, const std::wstring& title) {
    std::vector<HWND> childWindows;
    EnumChildWindows(parent, EnumChildWindowsProc, reinterpret_cast<LPARAM>(&childWindows));
    for (HWND hwnd : childWindows) {
        wchar_t windowText[256];
        GetWindowText(hwnd, windowText, sizeof(windowText) / sizeof(windowText[0]));
        if (title == windowText) {
            return hwnd;
        }
    }
    return NULL;
}

int wmain(int argc, wchar_t* argv[]) {
    // 设置控制台以支持 UTF-8
    _setmode(_fileno(stdout), _O_U8TEXT);

    if (argc != 2) {
        std::wcerr << L"Usage: " << argv[0] << L" <text_to_type>" << std::endl;
        return 1;
    }

    // 获取传入的文本
    std::wstring textToType = argv[1];
    bool shouldTypeText = !textToType.empty();

    // 获取父窗口句柄
    HWND hwndParent = FindWindow(NULL, TEXT("正点原子串口调试助手 V2.8"));
    if (hwndParent == NULL) {
        std::wcerr << L"未找到父窗口" << std::endl;
        return 1;
    }

    std::vector<HWND> childWindows;

    // 枚举父窗口下的所有子窗口
    if (!EnumChildWindows(hwndParent, EnumChildWindowsProc, reinterpret_cast<LPARAM>(&childWindows))) {
        std::wcerr << L"EnumChildWindows 失败" << std::endl;
        return 1;
    }

    // 查找具有指定样式的子窗口
    DWORD targetStyle = 0x56210044; // 要查找的子窗口样式
    HWND hwndTextBox = NULL;

    for (HWND hwnd : childWindows) {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        if (style == targetStyle) {
            hwndTextBox = hwnd;
            PrintWindowInfo(hwnd);
            break;
        }
    }

    if (shouldTypeText) {
        if (hwndTextBox == NULL) {
            std::wcerr << L"未找到具有指定样式的子窗口" << std::endl;
            return 1;
        }

        // 输入文本到文本框并延迟
        TypeTextInTextBox(hwndTextBox, textToType.c_str());

        // 查找并触发 "发送" 按钮
        HWND hwndSendButton = FindChildWindowByTitle(hwndParent, L"发送");
        if (hwndSendButton) {
            PrintWindowInfo(hwndSendButton);
            SendMessage(hwndSendButton, BM_CLICK, 0, 0);
        }
        else {
            std::wcerr << L"未找到发送按钮" << std::endl;
        }

        //// 查找并触发 "清除接收" 按钮
        //HWND hwndClearButton = FindChildWindowByTitle(hwndParent, L"清除接收");
        //if (hwndClearButton) {
        //    PrintWindowInfo(hwndClearButton);
        //    SendMessage(hwndClearButton, BM_CLICK, 0, 0);
        //}
        //else {
        //    std::wcerr << L"未找到清除接收按钮" << std::endl;
        //}
    }

    // 查找具有另一个指定样式的子窗口（输出框）
    DWORD targetStyle1 = 0x562108C4;
    DWORD targetStyle2 = 0x560108C4;
    HWND hwndOutputBox = NULL;

    for (HWND hwnd : childWindows) {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        if (style == targetStyle1 || style == targetStyle2) {
            hwndOutputBox = hwnd;
            PrintWindowInfo(hwnd);
            break;
        }
    }

    if (hwndOutputBox == NULL) {
        std::wcerr << L"未找到具有指定样式的输出框" << std::endl;
        return 1;
    }

    return 0;
}
