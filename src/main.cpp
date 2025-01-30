#include "CPU.hpp"
#include <limits>
#include <algorithm>
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
    if(initProcess!=nullptr) {
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
  int escalonador;
  int indexThread=0;

  cout<<"Escolha um escalonador de processo:"<<endl;
  cout<<"0-RoundRobin"<<endl;
  cout<<"1-First Come"<<endl;
  cout<<"2-Short First"<<endl;
  cin>>escalonador;

  auto start = std::chrono::system_clock::now();

  // Cria thread dos cores
  for (int i = 0; i < MultiCore+1; i++) {
    auto rc = pthread_create(&threads[indexThread], NULL, callCore, NULL);
    rc==0?Success("Thread criada com sucesso"):Error("Erro "+to_string(rc)+" ao criar a thread");
    indexThread++;
  }

  for (auto &&i : filaProcessos) {
    switch (escalonador) {
      case 0: //seta o quantum de cada um
        i->set_quantum(250);
        break;
      case 1: //round robin com qunatum infinito
        i->set_quantum(std::numeric_limits<int>::max());
        break;
      case 2: //seta tempo aleatorio para processos
        unsigned long j;
        srand( (unsigned)time(NULL) );
        int n;
        n = rand();
        i->set_et(n);
        i->set_quantum(std::numeric_limits<int>::max());
        break;
      default:
        break;
    }
  }
  if(escalonador==2) {
    std::sort(filaProcessos.begin(), filaProcessos.end(),
          [](PCB* const & a, PCB* const & b) -> bool
          { return a->get_et() < b->get_et(); } );
  }

  // Monitora a lista de processos
  while (!filaProcessos.empty()) {
    if (changeInitProcess) {
      // Mantem o processo para executar por 5 segundos
      initProcess = filaProcessos.front(); 
      sleep(0.05);

      // Tira da frente, e coloca no final,
      filaProcessos.erase(filaProcessos.begin());
      filaProcessos.push_back(initProcess);
      changeInitProcess=false;
    }
    
    // Checa quantidade de processos finalizados
    for (int i = 0; i < filaProcessos.size(); i++) {
      if(filaProcessos[i]->get_state()=="finished") {
        filaProcessos.erase(filaProcessos.begin()+i);
      };
    }
  }
  cout << "Processos Finalizados" << '\n';
  cout << "ULA: " << cpu.ULAs_counter() << endl;
  auto end = std::chrono::system_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
  std::cout << "Tempo de execução: " << duration << " ms" << std::endl;
  return 0;
}
