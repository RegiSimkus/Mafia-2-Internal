#pragma once

namespace Mafia2
{
	namespace Hacks
	{
		namespace InfiniteAmmo
		{
			extern bool bEnabled;
			extern unsigned char pOriginalBytes[3];
			void Enable();
			void Disable();
			void Toggle();
		}
	}
}