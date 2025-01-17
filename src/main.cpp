#include "CPU.hpp"
#include <unistd.h>

PCB* initProcess = nullptr;
bool changeInitProcess=true;
vector<PCB*> filaProcessos = getFilaProcessos();
CPU cpu;

void* callCore(void* arguments){
  // Como não se usa join, damos detach na thread para que quando ela acabar os recursos sejam
  pthread_detach(pthread_self()) == 0?Success("Thread separada"):Error("Erro ao separar thread"); 
  while (!filaProcessos.empty())
  {
    if(initProcess!=nullptr){
      changeInitProcess=true;
      cpu.ProcessCore(initProcess);
    }
    Checkpoint("Saiu");
    sleep(2);
  }
  return nullptr;
}

int main() {
  pthread_t threads[filaProcessos.size()];
  int indexThread=0;

  // Cria thread dos cores
  for (int i = 0; i < MultiCore+1; i++)
  {
    auto rc = pthread_create(&threads[indexThread], NULL, callCore, NULL);
    rc==0?Success("Thread criada com sucesso"):Error("Erro "+to_string(rc)+" ao criar a thread");
    indexThread++;
  }

  // Monitora a lista de processos
  while (!filaProcessos.empty())
  {    
    if (changeInitProcess)
    {
      // Mantem o processo para executar por 5 segundos
      initProcess = filaProcessos.front(); 
      sleep(0.05);

      // Tira da frente, e coloca no final,
      filaProcessos.erase(filaProcessos.begin());
      filaProcessos.push_back(initProcess);
      changeInitProcess=false;
    }
    
    // Checa quantidade de processos finalizados
    for (int i = 0; i < filaProcessos.size(); i++)
    {
      if(filaProcessos[i]->get_state()=="finished"){
        filaProcessos.erase(filaProcessos.begin()+i);
      };
    }
  }
  cout << "Processos Finalizados" << '\n';
}