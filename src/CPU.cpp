#include "CPU.hpp"

CPU::CPU(){
  for (auto &&i : this->cores)
    i=Core(&ram);
}

void CPU::ProcessCore(PCB* process){
  Checkpoint("Rodando Processo");
  // Verifica status do processo, se tiver executando por outra thread retorna
  if(process->get_state()=="executing") return;
  else if (process->get_state()=="blocked"){
    if(process->get_state()=="executing") return;
    process->unblock_process();
  }
  else if(process->get_state()=="ready"){
    if(process->get_state()=="executing") return;
    process->start_process();
  }

  // Seleciona core e ramstorage
  Core selectedCore;
  if(!SelectRamStorage(process)) return;
  if(!SelectCore(&selectedCore)) return;

  // Carrega registradores da ram 
  if(process->get_state()=="blocked"){
    Checkpoint("Registradores carregando");
    LoadRegisterFromPCB(&selectedCore, process);
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
    auto lock = selectedCore.get_lock();
    pthread_mutex_unlock(&lock);
  }
  // Caso quantum seja atingido (ao buscar recurso ou por demorar mesmo)
  catch(int quantum){
    Error("Processo bloqueado");
    // Bloqueia o processo
    process->block_process(quantum);
    // Guarda banco de registradores no storage RAM selecionada
    StoreRegisterToPCB(&selectedCore,process);
    // Libera espaços da ram usada
    this->ram.FreeMemory(process->get_memoryUsage());
    // Libera Core
    auto lock = selectedCore.get_lock();
    pthread_mutex_unlock(&lock);
  }  
}

// Escolhe um core pro processo, se todos estiverem cheios, retorna
bool CPU::SelectCore(Core* core){
  bool foundCore=false;
  for (int i = 0; i < MultiCore; i++)
  {
    // Ve se o core esta sendo usado, e já trava ele se estiver
    auto lock =cores->get_lock();
    if (pthread_mutex_trylock(&lock)==0){
      (*core)=this->cores[i];
      foundCore=true;
      return true;
    }
  }
  if (!foundCore)
  {
    Error("Nenhum core disponível");
    return false;
  }
  return false;
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
void CPU::StoreRegisterToPCB(Core* selectedCore, PCB* process){
  process->set_registers(selectedCore->get_registerBank());
}

// Guarda banco de registradores sequencialmente na ram
void CPU::LoadRegisterFromPCB(Core* selectedCore, PCB* process){
  selectedCore->set_registerBank(process->get_registers());
}