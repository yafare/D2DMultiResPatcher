#pragma once

#include <Windows.h>

#define DETOURS_INTERNAL // for CDetourEnableWriteOnCodePage & DetourGenXXX functions
#include "Detours/detours.h"

inline void HookFunction(void* hook_addr, void* function)
{
	CDetourEnableWriteOnCodePage hlp((PBYTE)hook_addr);
	DetourGenJmp((PBYTE)hook_addr, (PBYTE)function);
}

#define HOOK_ADDR_FUNC(FUNC_NAME, FROM_ADDR, HOOK_ADDR) \
void FUNC_NAME(void) \
{ \
	HookFunction((PBYTE)FROM_ADDR, (PBYTE)HOOK_ADDR); \
}
