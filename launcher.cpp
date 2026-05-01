#include <windows.h>
#include <string>

void LaunchGame() {
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    CreateProcessA("javaw.exe", "-jar minecraft.jar", NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
    
    LPVOID pDllPath = VirtualAllocEx(pi.hProcess, NULL, 256, MEM_COMMIT, PAGE_READWRITE);
    WriteProcessMemory(pi.hProcess, pDllPath, "C:\\VoidClient.dll", 16, NULL);
    
    HANDLE hThread = CreateRemoteThread(pi.hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, pDllPath, 0, NULL);
    ResumeThread(pi.hThread);
}
