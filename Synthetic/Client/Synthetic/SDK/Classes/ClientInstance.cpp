#include "ClientInstance.h"

uintptr_t ClientInstance::getBaseAddr(){
    return (uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe"));
};

Player* ClientInstance::getPlayer(){
    static unsigned int offset = NULL;
    
    if(offset == NULL)
        offset = *reinterpret_cast<int*>(Mem::findSig("48 8B 89 ? ? ? ? 48 85 C9 ? ? 33 C0 48 8B 5C 24 ?") + 3);
    
    return *reinterpret_cast<Player**>((uintptr_t)(this) + offset);
};

GameSettings* ClientInstance::getSettings(){
    uintptr_t baseAddr = (uintptr_t)(getBaseAddr() + 0x04074610);
    std::vector<unsigned int> offsets = { 0x10, 0x10, 0x38, 0x0 };
    
    return (GameSettings*)(Mem::findMultiLvlPtr(baseAddr, offsets));
};

MinecraftGame* ClientInstance::getMinecraftGame(){
    static unsigned int offset = 0xA8;
    
    if (offset == NULL)
		return nullptr;
    
    return *reinterpret_cast<MinecraftGame**>((uintptr_t)(this) + offset);
};

GuiData* ClientInstance::getGuiData(){
    static unsigned int offset = 0x4D8;
	
    if (offset == NULL)
		return nullptr;
    
	return *reinterpret_cast<GuiData**>((uintptr_t)(this) + offset);
};


void ClientInstance::grabMouse(){
    using GrabMouse = void * (__thiscall*) (ClientInstance*);
    GrabMouse _GrabMouse = reinterpret_cast<GrabMouse>(VTable[270]);
    _GrabMouse(this);
};

void ClientInstance::releaseMouse(){
    using ReleaseMouse = void * (__thiscall*) (ClientInstance*);
    ReleaseMouse _ReleaseMouse = reinterpret_cast<ReleaseMouse>(VTable[271]);
    _ReleaseMouse(this);
};