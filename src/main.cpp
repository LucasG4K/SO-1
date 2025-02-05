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
  pthread_detach(pthread_self()); // == 0?Success("Thread separada"):error("Erro ao separar thread"); 
  while (!filaProcessos.empty())
  {
    if(initProcess!=nullptr) {
      changeInitProcess=true;
      cpu.ProcessCore(initProcess);
    }
    usleep(50);
  }
  return nullptr;
}

int main() {
  pthread_t threads[filaProcessos.size()];
  int escalonador;
  int indexThread=0;

  escalonador=0;

  auto start = chrono::high_resolution_clock::now();

  // Cria thread dos cores
  for (int i = 0; i < MultiCore; i++) {
    auto rc = pthread_create(&threads[indexThread], NULL, callCore, NULL);
    //rc==0?Success("Thread criada com sucesso"): error("Erro "+to_string(rc)+" ao criar a thread");
    indexThread++;
  }

  for (auto &&i : filaProcessos) {
    switch (escalonador) {
      case 0: //seta o quantum de cada um
        i->set_quantum(5);
        break;
      case 1: //round robin com qunatum infinito
        i->set_quantum(numeric_limits<int>::max());
        break;
      case 2: //seta tempo aleatorio para processos
        unsigned long j;
        srand( (unsigned)time(NULL) );
        int n;
        n = rand();
        i->set_et(n);
        i->set_quantum(numeric_limits<int>::max());
        break;
      default:
        break;
    }
  }
  if(escalonador==2) {
    sort(filaProcessos.begin(), filaProcessos.end(),
          [](PCB* const & a, PCB* const & b) -> bool
          { return a->get_et() < b->get_et(); } );
  }

  // Monitora a lista de processos
  while (!filaProcessos.empty()) {
    if (changeInitProcess) {
      initProcess = filaProcessos.front(); 
      usleep(100);

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

  std::string filename = "output/output" + std::to_string(escalonador) + std::to_string(MultiCore) + std::to_string(UseCache) + ".csv";

  // Check if the file exists
  std::ifstream fileCheck(filename);
  bool fileExists = fileCheck.good();
  fileCheck.close();

  // Open file in append mode
  std::ofstream outFile(filename, std::ios::out | std::ios::app);
  if (!outFile) {
      throw std::ios_base::failure("Failed to create the file");
  }

  // If the file didn't exist, write the header first
  if (!fileExists) {
      outFile << "Escalonador;QtdCores;UsaCache;QtdUla;QtdPipeline;Duração (us)\n";
  }
  switch (escalonador)
  {
  case 0:
    outFile<<"RoundRobin;";
    break;
  case 1:
    outFile<<"First Come;";
    break;
  case 2:
    outFile<<"Short First;";
    break;
  default:
    break;
  }
  outFile << MultiCore<<";";
  outFile << UseCache<<";";
  outFile << cpu.ULAs_counter()<<";";
  outFile << cpu.Pipeline_counter()<<";";
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
  outFile << duration<<";"<<endl;
  outFile.close();
  return 0;
}
