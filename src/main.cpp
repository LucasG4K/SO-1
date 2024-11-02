#include "CPU.hpp"
#include "RAM.hpp"

int main() {
  int clock = 0;
  vector<string> instrucoes = read_ROM();

  CPU cpu;

  RAM ram;

  while (cpu.InstructionFetch(instrucoes)) {
    cpu.InstructionDecode();
    cpu.Execute();
    cpu.MemoryAccess(ram);
    cpu.WriteBack();
    clock+=5;
  }

  cout << "CLOCK: " << clock << endl;

  return 0;
}