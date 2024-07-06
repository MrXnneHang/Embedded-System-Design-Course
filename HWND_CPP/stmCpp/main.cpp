#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fcntl.h> // for _O_U16TEXT
#include <io.h> // for _setmode

// �ص����������ռ��Ӵ��ھ��
BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam) {
    auto& windows = *reinterpret_cast<std::vector<HWND>*>(lParam);
    windows.push_back(hwnd);
    return TRUE; // ����ö����һ���Ӵ���
}

void TypeTextInTextBox(HWND hwndTextBox, LPCWSTR text) {
    // �����ı���
    SetFocus(hwndTextBox);

    // �����ı����ı���
    SendMessage(hwndTextBox, WM_SETTEXT, 0, (LPARAM)text);
}

void PrintWindowInfo(HWND hwnd) {
    wchar_t className[256];
    wchar_t windowText[256];

    // ��ȡ��������
    GetClassName(hwnd, className, sizeof(className) / sizeof(className[0]));

    // ��ȡ������ʽ
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);

    // ��ȡ���ڱ��⣨������ EDIT �� RichEdit �ؼ��Ĵ���
    int length = GetWindowTextLength(hwnd);
    std::wstring text(length, L'\0');
    GetWindowText(hwnd, &text[0], length + 1);

    if (className == std::wstring(L"WindowsForms10.EDIT.app.0.141b42a_r8_ad1") ||
        className == std::wstring(L"WindowsForms10.RichEdit20W.app.0.141b42a_r8_ad1")) {
        // ���Ի�ȡ�����ı�����
        length = SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);
        text.resize(length);
        SendMessage(hwnd, WM_GETTEXT, length + 1, (LPARAM)&text[0]);
    }

    // ��ӡ��Ϣ
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
    // ���ÿ���̨��֧�� Unicode
    _setmode(_fileno(stdout), _O_U8TEXT);

    if (argc != 4) {
        std::wcerr << L"������������" << std::endl;
        return 1;
    }

    std::wstring input_data = argv[1];
    int open_chuankou = std::stoi(argv[2]);
    int close_chuankou = std::stoi(argv[3]);

    // ��ȡ�����ھ��
    HWND hwndParent = FindWindow(NULL, TEXT("����ԭ�Ӵ��ڵ������� V2.8"));
    if (hwndParent == NULL) {
        std::wcerr << L"δ�ҵ�������" << std::endl;
        return 1;
    }

    std::vector<HWND> childWindows;

    // ö�ٸ������µ������Ӵ���
    if (!EnumChildWindows(hwndParent, EnumChildWindowsProc, reinterpret_cast<LPARAM>(&childWindows))) {
        std::wcerr << L"EnumChildWindows ʧ��" << std::endl;
        return 1;
    }

    // ���Ҿ���ָ����ʽ���Ӵ���
    DWORD targetStyle = 0x56210044; // Ҫ���ҵ��Ӵ�����ʽ
    HWND hwndTextBox = NULL;

    for (HWND hwnd : childWindows) {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        if (style == targetStyle) {
            hwndTextBox = hwnd;
            PrintWindowInfo(hwnd);
            break;
        }
    }

    if (input_data != L"") {
        if (hwndTextBox == NULL) {
            std::wcerr << L"δ�ҵ�����ָ����ʽ���Ӵ���" << std::endl;
            return 1;
        }

        // �����ı����ı���
        TypeTextInTextBox(hwndTextBox, input_data.c_str());

        // ���Ҳ����� "����" ��ť
        HWND hwndSendButton = FindChildWindowByTitle(hwndParent, L"����");
        if (hwndSendButton) {
            SendMessage(hwndSendButton, BM_CLICK, 0, 0);
        }
        else {
            std::wcerr << L"δ�ҵ����Ͱ�ť" << std::endl;
        }
    }

    if (close_chuankou == 1) {
        HWND hwndSendButton = FindChildWindowByTitle(hwndParent, L"�رմ���");
        if (hwndSendButton) {
            SendMessage(hwndSendButton, BM_CLICK, 0, 0);
        }
        else {
            std::wcerr << L"�����Ѿ��ر�" << std::endl;
        }
    }

    if (open_chuankou == 1) {
        HWND hwndSendButton = FindChildWindowByTitle(hwndParent, L"�򿪴���");
        if (hwndSendButton) {
            SendMessage(hwndSendButton, BM_CLICK, 0, 0);
        }
        else {
            std::wcerr << L"�����Ѿ���" << std::endl;
        }
    }

    Sleep(300);

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
        std::wcerr << L"δ�ҵ�����ָ����ʽ�������" << std::endl;
        return 1;
    }

    return 0;
}
