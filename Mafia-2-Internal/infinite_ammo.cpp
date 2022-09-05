#include "infinite_ammo.h"
#include <Windows.h>

using namespace Mafia2::Hacks;

unsigned char InfiniteAmmo::pOriginalBytes[3];
bool InfiniteAmmo::bEnabled = false;

void InfiniteAmmo::Enable()
{
	if (bEnabled) return;
	bEnabled = true;

	static DWORD dwBase = (DWORD)GetModuleHandleA("mafia2.exe");
	uintptr_t addy = dwBase + 0x5A46E7;
	
	DWORD dwOldProtect;
	VirtualProtect((void*)addy, 3, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	pOriginalBytes[0] = *(BYTE*)addy;
	pOriginalBytes[1] = *(BYTE*)(addy + 1);
	pOriginalBytes[2] = *(BYTE*)(addy + 2);

	*(BYTE*)(addy) = 0x90;
	*(BYTE*)(addy + 1) = 0x90;
	*(BYTE*)(addy + 2) = 0x90;

	VirtualProtect((void*)addy, 3, dwOldProtect, &dwOldProtect);
}

void InfiniteAmmo::Disable()
{
	if (!bEnabled) return;
	bEnabled = false;

	static DWORD base = (DWORD)GetModuleHandleA("mafia2.exe");
	uintptr_t addy = base + 0x5A46E7;

	DWORD dwOldProtect;
	VirtualProtect((void*)addy, 3, PAGE_EXECUTE_READWRITE, &dwOldProtect);


	*(BYTE*)(addy) = pOriginalBytes[0];
	*(BYTE*)(addy + 1) = pOriginalBytes[1];
	*(BYTE*)(addy + 2) = pOriginalBytes[2];

	VirtualProtect((void*)addy, 3, dwOldProtect, &dwOldProtect);
}

void InfiniteAmmo::Toggle()
{
	if (bEnabled)
		Disable();
	else
		Enable();
}