// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

void PatchIt();

void ThreadProc()
{
	Sleep(5000);
	PatchIt();
}

void StartHook()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadProc, 0, 0, 0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		StartHook();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

