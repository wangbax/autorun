#include <windows.h>
#include <string>
#include <iostream>

std::wstring GetExePath(const std::wstring& appName) {
    wchar_t buffer[MAX_PATH];
    // 获取当前执行路径
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring currentPath(buffer);
    // 找到最后一个反斜杠，以获取目录路径
    size_t lastBackslash = currentPath.find_last_of(L"\\");
    std::wstring directory = currentPath.substr(0, lastBackslash + 1);
    // 拼接目录和应用程序名称来形成完整路径
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
        wsprintfW(message, L"启动失败: %d", GetLastError());
        // MessageBox(NULL, message, L"错误", MB_OK);
    }
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc != 2) {
        std::wcerr << L"用法: " << argv[0] << L" <可执行文件名>" << std::endl;
        return 1;
    }

    std::wstring appName = argv[1];
    RunProcess(appName);
    return 0;
}