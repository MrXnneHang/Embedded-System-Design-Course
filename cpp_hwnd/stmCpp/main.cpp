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
    std::wcout << L"���ھ��: " << hwnd << std::endl;
    std::wcout << L"����: " << className << std::endl;
    std::wcout << L"����: " << text << std::endl;
    std::wcout << L"��ʽ: " << std::hex << style << std::endl;
    std::wcout << L"--------------------------" << std::endl;
}

int main() {
    // ���ÿ���̨��֧�� Unicode
    _setmode(_fileno(stdout), _O_U16TEXT);

    // ��ȡ�����ھ��
    HWND hwndParent = FindWindow(NULL, TEXT("����ԭ�Ӵ��ڵ������� V2.8"));
    if (hwndParent == NULL) {
        std::wcerr << L"δ�ҵ�������" << std::endl;
        return 1;
    }
    else {
        std::wcout << L"�ҵ�������\n";
    }

    std::vector<HWND> childWindows;

    // ö�ٸ������µ������Ӵ���
    if (!EnumChildWindows(hwndParent, EnumChildWindowsProc, reinterpret_cast<LPARAM>(&childWindows))) {
        std::wcerr << L"EnumChildWindows ʧ��" << std::endl;
        return 1;
    }

    std::wcout << L"�ҵ��Ӵ�������: " << childWindows.size() << std::endl;

    // ���Ҿ���ָ����ʽ���Ӵ���
    DWORD targetStyle = 0x56210044; // Ҫ���ҵ��Ӵ�����ʽ
    HWND hwndTextBox = NULL;

    for (HWND hwnd : childWindows) {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        //std::wcout << L"��鴰�ھ��: " << hwnd << L", ��ʽ: " << std::hex << style << std::endl;
        if (style == targetStyle) {
            // �ҵ�����ָ����ʽ���Ӵ��ڣ�����Ϊ�ı���ؼ���
            hwndTextBox = hwnd;
            PrintWindowInfo(hwnd);
            break;
        }
    }

    if (hwndTextBox == NULL) {
        std::wcerr << L"δ�ҵ�����ָ����ʽ���Ӵ���" << std::endl;
        return 1;
    }
    else {
        std::wcout << L"�ҵ��ı���\n";
    }

    // �����ı����ı���
    LPCWSTR textToType = L"efg"; // Ҫ������ı�
    TypeTextInTextBox(hwndTextBox, textToType);

    // ���Ҿ�����һ��ָ����ʽ���Ӵ���
    targetStyle = 0x560108C4;
    HWND hwndOutputBox = NULL;

    for (HWND hwnd : childWindows) {
        DWORD style = GetWindowLong(hwnd, GWL_STYLE);
        if (style == targetStyle) {
            hwndOutputBox = hwnd;
            PrintWindowInfo(hwnd);
            break;
        }
    }

    if (hwndOutputBox == NULL) {
        std::wcerr << L"δ�ҵ�����ָ����ʽ���Ӵ���" << std::endl;
        return 1;
    }
    else {
        std::wcout << L"�ҵ������\n";
    }

    return 0;
}
