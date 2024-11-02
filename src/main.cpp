#include "CPU.hpp"
#include "RAM.hpp"

int main() {
  vector<string> instrucoes = read_ROM();

  CPU cpu;

  RAM ram;

  while (cpu.InstructionFetch(instrucoes)) {
    cpu.InstructionDecode();
    cpu.Execute();
    cpu.MemoryAccess(ram);
    cpu.WriteBack();
  }

  cpu.print_clock();

  return 0;
}