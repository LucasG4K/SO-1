#ifndef _CPU
#define _CPU
#define MultiCore 2

#include "Core.hpp"
#include "PCB.hpp"

class CPU {
  private:
    RAM ram;
    Core cores[MultiCore];
    int Process_RAM[32] = { -1 };
  public:
    CPU();
    void ProcessCore(PCB process);
    int RamManager();
};

#endif