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

  int clock = 0;
  vector<string> instrucoes = read_ROM();

  CPU cpu;

  RAM ram;

  for(auto a : instrucoes) cout <<a << endl;

  while (clock < instrucoes.size()) {
    cpu.InstructionFetch(instrucoes);
    cpu.InstructionDecode();
    cpu.Execute();
    cpu.MemoryAccess(ram);
    cpu.WriteBack();

    clock++;
  }
}