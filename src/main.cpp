#include "CPU.hpp"

struct arg_struct{
  CPU cpu;
  PCB* process;
  arg_struct(CPU cpu, PCB* pcb){ this->cpu=cpu; this->process=pcb; };
};

void* callProcess(void* arguments){
  // Como não se usa join, damos detach na thread para que quando ela acabar os recursos sejam
  pthread_detach(pthread_self()) == 0?Success("Thread separada"):Error("Erro ao separar thread"); 
  struct arg_struct *args = (struct arg_struct *)arguments;
  args->cpu.ProcessCore(args->process);
}

int main() {
  CPU cpu;
  vector<PCB*> filaProcessos = getFilaProcessos();
  pthread_t threads[filaProcessos.size()];

  int indexThread=0;
  int processFinished=0;
  while (processFinished<filaProcessos.size())
  {
    processFinished=0;
    
    // Tira da frente, starta, e coloca no final,
    PCB* initProcess = filaProcessos.front(); // 1-b, 2-e, 3-r,
    filaProcessos.erase(filaProcessos.begin());
    initProcess->start_process();
    filaProcessos.push_back(initProcess);

    // Começa thread do processo se ele não estiver finalizado
    if (initProcess->get_state()!="finished")
    {
      auto rc = pthread_create(&threads[indexThread], NULL, callProcess, (void*)&arg_struct(cpu,initProcess));
    }    
    
    // Checa quantidade de processos finalizados
    for (auto &&i : filaProcessos)
      processFinished += i->get_state()=="finished";
  }
  cout << "Processos Finalizados" << endl;
}