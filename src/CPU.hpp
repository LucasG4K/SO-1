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
  public:
    CPU();
    void ProcessCore(PCB* process);
    int RamManager();
};

#endif