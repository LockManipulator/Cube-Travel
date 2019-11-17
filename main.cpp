#include "main.h"
#include "cwmods/cwsdk.h"
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <windows.h>

#include "src/memory/memory_helper.h"

class Mod : GenericMod {
	virtual void Initialize() override {
		auto glider_use = MemoryHelper::FindPattern("0F 84 86 ? ? ? 49 8B 8E");
		auto boat_use = MemoryHelper::FindPattern("74 66 4D 8B 86 48 04");
		auto rein_use = MemoryHelper::FindPattern("74 14 49 8B 45 08");
		auto rein_stay = MemoryHelper::FindPattern("E8 D4 3B D8 FF 84 C0 75 0B 49 8B 86 48 04");
		auto boat_stay = MemoryHelper::FindPattern("E8 82 3B D8 FF 84 C0 75 0B 49 8B 86 48 04 ? ? C6 40 68");

		MemoryHelper::PatchMemory<uint8_t>(glider_use + 0x01, 0x80);
		MemoryHelper::PatchMemory<uint8_t>(boat_use, 0x70);
		MemoryHelper::PatchMemory<uint8_t>(rein_use, 0x70);
		MemoryHelper::PatchMemory<uint8_t>(rein_stay + 0x07, 0xEB);
		MemoryHelper::PatchMemory<uint8_t>(boat_stay + 0x07, 0xEB);
	}
};

EXPORT Mod* MakeMod() {
	return new Mod();
}