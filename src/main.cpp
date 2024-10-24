#include "CPU.hpp"
#include "RAM.hpp"

vector<string> read_ROM() {
  ifstream codigo("codigo.txt");
  vector<string> retorno;
  string temp;
  while (getline(codigo, temp)) {
    retorno.push_back(temp);
  }
  return retorno;
}

int main() {
  int clock = 0;
  vector<string> instrucoes = read_ROM();

  CPU cpu;

  RAM ram;

  while (clock < instrucoes.size()) {
    cpu.InstructionFetch(instrucoes);
    cpu.InstructionDecode();
    cpu.Execute();
    cpu.MemoryAccess(ram);

    clock++;
  }
}