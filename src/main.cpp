#include "CPU.hpp"
#include "RAM.hpp"

vector<string> read_ROM() {
  ifstream codigo("./dataset/codigo.txt");
  vector<string> retorno;
  string temp;
  while (getline(codigo, temp)) {
    retorno.push_back(temp);
  }
  return retorno;
}

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