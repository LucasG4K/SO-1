#include "CPU.hpp"
#include <unistd.h>

PCB* initProcess = nullptr;
vector<PCB*> filaProcessos = getFilaProcessos();

struct arg_struct{
  CPU* cpu;
  arg_struct(CPU* cpu){ this->cpu=cpu; };
};

void* callCore(void* arguments){
  // Como não se usa join, damos detach na thread para que quando ela acabar os recursos sejam
  pthread_detach(pthread_self()) == 0?Success("Thread separada"):Error("Erro ao separar thread"); 
  struct arg_struct *args = (struct arg_struct *)arguments;
  while (!filaProcessos.empty())
  {
    if(initProcess!=nullptr)
      args->cpu->ProcessCore(initProcess);
  }
  return nullptr;
}

int main() {
  CPU cpu;
  pthread_t threads[filaProcessos.size()];
  int indexThread=0;

  // Cria thread dos cores
  for (int i = 0; i < MultiCore; i++)
  {
    auto args=arg_struct(&cpu);
    auto rc = pthread_create(&threads[indexThread], NULL, callCore, (void*)&args);
    rc==0?Success("Thread criada com sucesso"):Error("Erro "+to_string(rc)+" ao cirar a thread");
    indexThread++;
  }

  // Monitora a lista de processos
  while (!filaProcessos.empty())
  {    
    // Coloca processo para ser iniciado
    if (filaProcessos.front()->get_state()!="finished")
    {
      // Mantem o processo para executar por 5 segundos
      initProcess = filaProcessos.front(); 
      sleep(0.05);
    }    

    // Tira da frente, e coloca no final,
    filaProcessos.erase(filaProcessos.begin());
    filaProcessos.push_back(initProcess);
    
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