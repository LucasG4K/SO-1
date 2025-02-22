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

    bool SelectCore(int* core);

    bool SelectRamStorage(PCB* process);
  public:
    CPU();
    int ULAs_counter();
    int Pipeline_counter();
    void ProcessCore(PCB* process);
    void StoreRegisterToPCB(Core* selectedCore, PCB* process);
    void LoadRegisterFromPCB(Core* selectedCore, PCB* process);
};

#endif