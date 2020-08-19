// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include <Windows.h>
#include "pluginapi.h"

#define NSIS_MAX_STRLEN 1024
#define BUFF_SIZE 512
#define PIPE_NAME TEXT("\\\\.\\pipe\\")

TCHAR szBuf[NSIS_MAX_STRLEN];
extern "C" {
    void __declspec(dllexport) ReadNamedPipe(HWND hwndParent,
        int string_size,
        LPTSTR variables,
        stack_t** stacktop,
        extra_parameters* extra, ...)
    {
        EXDLL_INIT();
        popstring(szBuf);
        MessageBox(hwndParent, szBuf, _T("11"), MB_OK);

        HANDLE hPipe;
        char wBuf[BUFF_SIZE];
        char rBuf[BUFF_SIZE];
        BOOL fSuccess = FALSE;
        DWORD dwMode, cbWrite, cbRead;
        TCHAR ret[BUFF_SIZE];
        
        hPipe = CreateFile(szBuf,
            GENERIC_WRITE|GENERIC_READ,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);
        if (hPipe != INVALID_HANDLE_VALUE)
        {
            dwMode = PIPE_WAIT;
            fSuccess = SetNamedPipeHandleState(hPipe, &dwMode, NULL, NULL);
            if (!fSuccess)
            {
                _tcscpy(ret, TEXT("0"));
                setuservariable(INST_0, ret);
            }
            else
            {
                lstrcpy(wBuf, "ID\n");
                WriteFile(
                    hPipe,
                    wBuf,
                    lstrlen(wBuf),
                    &cbWrite,
                    NULL);
                lstrcpy(rBuf, "\0");
                fSuccess = ReadFile(
                    hPipe,
                    rBuf,
                    BUFF_SIZE,
                    &cbRead,
                    NULL);
                if (fSuccess)
                {
                    rBuf[cbRead - 2] = 0;
                    setuservariable(INST_0, rBuf);
                }
            }
            
            CloseHandle(hPipe);
        }
        else
        {
            _tcscpy(ret, TEXT("0"));
            setuservariable(INST_0, ret);
        }
    }
};


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

