#ifndef _CPU
#define _CPU

#include "Core.hpp"
#include "PCB.hpp"
#include <chrono>

class CPU {
  private:
    RAM ram;
    Core cores[MultiCore];
    bool Process_RAM[32] = { false };

    bool SelectCore(Core* core);

    bool SelectRamStorage(PCB* process);
    void StoreRegisterToRam(Core* selectedCore, int ramToStore);
    void LoadRegisterFromRam(Core* selectedCore, int ramToStore);
  public:
    CPU();
    void ProcessCore(PCB* process);
};

#endif