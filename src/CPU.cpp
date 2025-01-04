#include "CPU.hpp"

CPU::CPU(){}

void CPU::ProcessCore(PCB process){
  int clock = 0;

  // Escolhe um core pro processo
  Core selectedCore;
  bool foundCore=false;
  for (int i = 0; i < MultiCore; i++)
  {
    if (this->cores[i].get_inUse()==false){
        this->cores[i]=Core(&ram);
        selectedCore=this->cores[i];
        foundCore=true;
    }
  }
  if (!foundCore)
  {
    cout<<"Nenhum core disponível"<<endl;
    return;
  }

  // Escolhe um pedaço de ram pra guardar o processo
  int ramProcess=RamManager();
  if (ramProcess==-1)
  {
    cout<<"Nenhuma ram disponível"<<endl;
    return;
  }

  while (selectedCore.InstructionFetch(process.get_instruction())) {
    selectedCore.InstructionDecode();
    selectedCore.Execute();
    selectedCore.MemoryAccess(ramProcess);
    selectedCore.WriteBack();
    clock+=5;
  }

  cout << "CLOCK: " << clock << endl;
}

int CPU::RamManager(){
  for (int i = 1; i < NumRam; i++)
  {
    if (Process_RAM[i]==-1)
      return i;
  }
  return -1;
}