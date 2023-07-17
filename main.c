#include <stdio.h>
#include <Windows.h>

int main(int argc, char **argv) {
    if (argv[1] == NULL) {
        printf("Usage : dll_executor <DLL_PATH>\n");
        return -1;
    }

    char* Dll_Path = argv[1];
    HMODULE hModule = LoadLibraryA(Dll_Path);
    if (hModule == NULL) {
        printf("Failed to load the dll.\n");
    }

    LPCSTR Function_To_Execute = "DllMain"; // Function to execute in the dll
    
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, Function_To_Execute), NULL, 0, NULL);
    if (hThread == NULL) {
        printf("Failed to create thread.\n");
    }

    printf("Dll Executed!\n");
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    FreeLibrary(hModule);

    return 0;
}