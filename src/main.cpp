#include "CPU.hpp"

int main() {
  CPU cpu;
  PCB processo1("3423");
  PCB processo2("sada");
  PCB processo3("athrt");
  int processFinished=0;
  while (processFinished<3)
  {
    cpu.ProcessCore();
  }
}