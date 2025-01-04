#include "CPU.hpp"

CPU::CPU(){
  for (auto &&i : this->cores)
    i=Core(&ram);
}

void CPU::ProcessCore(PCB* process){

  if (process->get_state()!="blocked"){
    // Escolhe um pedaço de ram pra guardar o processo
    int ramProcess=RamManager();
    if (ramProcess==-1)
    {
      cout<<"Nenhuma ram disponível"<<endl;
      return;
    }
    else{
      process->set_ram(ramProcess);
    }
  }

  // Escolhe um core pro processo
  Core selectedCore;
  bool foundCore=false;
  for (int i = 0; i < MultiCore; i++)
  {
    // Ve se o core esta sendo usado, e já trava ele se estiver
    if (pthread_mutex_trylock(&cores->get_lock())==0){
      selectedCore=this->cores[i];
      foundCore=true;
    }
  }
  if (!foundCore)
  {
    cout<<"Nenhum core disponível"<<endl;
    return;
  }
  
  try
  {
    selectedCore.set_process(process);
    while (selectedCore.InstructionFetch()) {
      selectedCore.InstructionDecode();
      selectedCore.Execute();
      selectedCore.MemoryAccess();
      selectedCore.WriteBack();
      selectedCore.CheckQuantum();
    }
  }
  catch(const exception& e){}  
}

int CPU::RamManager(){
  for (int i = 1; i < NumRamStorage; i++)
  {
    if (Process_RAM[i] == false){
      Process_RAM[i] = true;
      return i;
    }
  }
  return -1;
}