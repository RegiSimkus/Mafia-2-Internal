// dllmain.cpp : Defines the entry point for the DLL application.
#include "includes.h"
#include "globals.h"
#include "utils.h"
#include "infinite_ammo.h"

FILE* file;
BOOL WINAPI MainThread(HMODULE hModule)
{

    while (!(GetAsyncKeyState(VK_END) & 1)) 
    { 
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            Mafia2::Hacks::InfiniteAmmo::Toggle();
        }
        Sleep(2); 
    }

    Sleep(150);

    FreeConsole();
    if (file)
        fclose(file);
    FreeLibraryAndExitThread(g_hModule, 0);
    FreeLibraryAndExitThread(hModule, 0);
    return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        g_hModule = hModule;
        AllocConsole();
        freopen_s(&file, "CONOUT$", "w", stdout);

        HANDLE handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
        if (handle)
            CloseHandle(handle);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}