#include <windows.h>
#include <string>
#include <iostream>

std::wstring GetExePath(const std::wstring& appName) {
    wchar_t buffer[MAX_PATH];
    // ��ȡ��ǰִ��·��
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring currentPath(buffer);
    // �ҵ����һ����б�ܣ��Ի�ȡĿ¼·��
    size_t lastBackslash = currentPath.find_last_of(L"\\");
    std::wstring directory = currentPath.substr(0, lastBackslash + 1);
    // ƴ��Ŀ¼��Ӧ�ó����������γ�����·��
    return directory + appName;
}

void RunProcess(const std::wstring& appName) {
    std::wstring exePath = GetExePath(appName);
    SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
    sei.lpVerb = L"open";
    sei.lpFile = exePath.c_str();
    sei.nShow = SW_SHOWNORMAL;
    sei.fMask = SEE_MASK_NOCLOSEPROCESS;
    if (!ShellExecuteEx(&sei)) {
        WCHAR message[64];
        wsprintfW(message, L"����ʧ��: %d", GetLastError());
        // MessageBox(NULL, message, L"����", MB_OK);
    }
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 2) {
        std::wcerr << L"�÷�: " << argv[0] << L" <��ִ���ļ���>" << std::endl;
        return 1;
    }

    std::wstring appName = argv[1];
    RunProcess(appName);
    return 0;
}