#include "main.h"
#include "cwmods/cwmods.h"
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <windows.h>

#include "src/memory/memory_helper.h"

void* Offset(void* x1, uint64_t x2) {
	return (void*)((char*)x1 + x2);
}

void Popup(const char* title, const char* msg) {
	MessageBoxA(0, msg, title, MB_OK | MB_ICONINFORMATION);
}

class Mod : GenericMod {
	virtual void Initialize() override {
		auto glider_use = MemoryHelper::FindPattern("0F 84 86 ? ? ? 49 8B 8E");
		auto boat_use = MemoryHelper::FindPattern("74 66 4D 8B 86 48 04");
		auto reins_use = MemoryHelper::FindPattern("74 14 49 8B 45 08");
		auto reins_stay = MemoryHelper::FindPattern("E8 D4 3B D8 FF 84 C0 75 0B 49 8B 86 48 04");
		auto boat_stay = MemoryHelper::FindPattern("E8 82 3B D8 FF 84 C0 75 0B 49 8B 86 48 04 ? ? C6 40 68");

		MemoryHelper::PatchMemory<uint8_t>(glider_use + 0x01, 0x80);
		MemoryHelper::PatchMemory<uint8_t>(boat_use, 0x70);
		MemoryHelper::PatchMemory<uint8_t>(reins_use, 0x70);
		MemoryHelper::PatchMemory<uint8_t>(reins_stay + 0x07, 0xEB);
		MemoryHelper::PatchMemory<uint8_t>(boat_stay + 0x07, 0xEB);
	}
};

EXPORT Mod* MakeMod() {
	return new Mod();
}

/*
To do:

1. Function to get all the artifacts in the inventory for each boost
2. Change name of each boost
3. Modify each base stat based off number of artifacts of that type in inventory
4. 

Code caves used:
50301
1694B0
1694C2
50CB1
5F01F

Next hook: 5B63FE

*/