#include "CPU.hpp"

int main() {
  int clock = 0;
  vector<string> instrucoes = read_ROM();

  CPU cpu;
  Cache cache;
  RAM ram;

  while (cpu.InstructionFetch(instrucoes)) {
    cpu.InstructionDecode();
    cpu.Execute();
    cpu.MemoryAccess(ram, cache);
    cpu.WriteBack();
    clock+=5;
  }

  cout << "CLOCK: " << clock << endl;

  return 0;
}