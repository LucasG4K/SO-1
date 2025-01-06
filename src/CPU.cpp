#include "CPU.hpp"

CPU::CPU(){
  for (auto &&i : this->cores)
    i=Core(&ram);
}

void CPU::ProcessCore(PCB* process){
  // Seleciona core e ramstorage
  Core selectedCore;
  if(!SelectRamStorage(process)) return;
  if(!SelectCore(&selectedCore)) return;
  
  // Carrega registradores da ram e desbloqueia processo
  if (process->get_state()=="blocked")
  {
    Checkpoint("Registradores carregando");
    LoadRegisterFromRam(&selectedCore, process->get_ram());
    process->unblock_process();
    Success("Registradores carregados, processo desbloqueado");
  }

  // Pipeline
  try
  {
    Checkpoint("Começando Pipeline");
    selectedCore.set_process(process);
    while (selectedCore.InstructionFetch()) {
      selectedCore.InstructionDecode();
      selectedCore.Execute();
      selectedCore.MemoryAccess();
      selectedCore.WriteBack();
      selectedCore.CheckQuantum();
    }
    
    // Finalizar processo
    this->Process_RAM[process->get_ram()]=false;
    process->finish_process();
    pthread_mutex_unlock(&selectedCore.get_lock());
  }
  // Caso quantum seja atingido (ao buscar recurso ou por demorar mesmo)
  catch(int quantum){
    Error("Processo bloqueado");
    // Bloqueia o processo
    process->block_process(quantum);
    // Guarda banco de registradores no storage RAM selecionada
    StoreRegisterToRam(&selectedCore,process->get_ram());
    // Libera Core
    pthread_mutex_unlock(&selectedCore.get_lock());
  }  
}

// Escolhe um core pro processo, se todos estiverem cheios, retorna
bool CPU::SelectCore(Core* core){
  bool foundCore=false;
  for (int i = 0; i < MultiCore; i++)
  {
    // Ve se o core esta sendo usado, e já trava ele se estiver
    if (pthread_mutex_trylock(&cores->get_lock())==0){
      (*core)=this->cores[i];
      foundCore=true;
    }
  }
  if (!foundCore)
  {
    Error("Nenhum core disponível");
    return;
  }
}

// Escolhe um pedaço de ram pra guardar o processo caso seja a primeira vez executando, se todos estiverem cheios, retorna
bool CPU::SelectRamStorage(PCB* process){
  if (process->get_state()!="blocked"){
    // Busca ram vazia
    for (int i = 0; i < NumRamStorage; i++)
    {
      if (this->Process_RAM[i] == false){
        this->Process_RAM[i] = true;
        process->set_ram(i);
        return true;
      }
    }
    Error("Nenhuma ram disponível");
    return false;
  }
  return true;
}

// Guarda banco de registradores sequencialmente na ram
void CPU::StoreRegisterToRam(Core* selectedCore, int ramToStore){
  int index = 0;
  for (auto &&i : (*selectedCore).get_registerBank().get_registers())
  {
    this->ram.Store(ramToStore,index,i.value);
    index++;
  }
  this->ram.Store(ramToStore,index,selectedCore->get_PC());
}

// Guarda banco de registradores sequencialmente na ram
void CPU::LoadRegisterFromRam(Core* selectedCore, int ramToLoad){
  vector<int> registers;
  for (int i = 0; i < RegisterBankSize+1; i++)
  {
    registers.push_back(this->ram.Load(ramToLoad,i));
  }
  selectedCore->set_registerBank(registers);
}