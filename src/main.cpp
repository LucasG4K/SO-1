#include "CPU.hpp"

int main() {
  CPU cpu;
  vector<PCB*> filaProcessos = getFilaProcessos();
  int processFinished=0;
  while (processFinished<3)
  {
    processFinished=0;
    
    // Tira da frente, starta, e coloca no final,
    PCB* initProcess = filaProcessos.front();
    filaProcessos.erase(filaProcessos.begin());
    initProcess->start_process();
    filaProcessos.push_back(initProcess);

    // Começa thread do processo se ele não estiver 
    pthread_t ptid;
    if (initProcess->get_state()!="finished")
    {
      cpu.ProcessCore(initProcess);
    }    
    
    // Checa quantidade de processos finalizados
    for (auto &&i : filaProcessos)
      processFinished += i->get_state()=="finished";    
  }
}