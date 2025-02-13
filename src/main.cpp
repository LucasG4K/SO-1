#include "MMU.hpp"
#include <unistd.h>

PCB* initProcess = nullptr;
bool changeInitProcess=true;
CPU cpu;
MMU mmu;

void* callCore(void* arguments){
  // Como não se usa join, damos detach na thread para que quando ela acabar os recursos sejam
  pthread_detach(pthread_self()); // == 0?Success("Thread separada"):error("Erro ao separar thread"); 
  while (!mmu.getFila().empty())
  {
    if(initProcess!=nullptr) {
      changeInitProcess=true;
      cpu.ProcessCore(initProcess);
    }
    usleep(50);
  }
  return nullptr;
}

void resumo(int escalonador, chrono::_V2::system_clock::time_point start){
  // Abrir arquivo
  string filename = "output/output" + to_string(escalonador) + to_string(MultiCore) + to_string(UseCache) + ".csv";
  ifstream fileCheck(filename);
  bool fileExists = fileCheck.good();
  fileCheck.close();
  ofstream outFile(filename, ios::out | ios::app);
  if (!outFile) {
      throw ios_base::failure("Failed to create the file");
  }

  // Se o arquivo não existia coloca o header
  if (!fileExists) outFile << "Escalonador;QtdCores;UsaCache;QtdUla;QtdPipeline;Duração (us)\n";
  // Insere dados em csv
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
}


int main() {
  int escalonador;
  int indexThread=0;

  escalonador=2;

  auto start = chrono::high_resolution_clock::now();

  for (auto &&i : mmu.getProcessos()) {
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

  auto temp=mmu.getProcessos();
  
  if(escalonador==2) {
    mmu.sortProcess();
  }

  pthread_t threads[mmu.getProcessos().size()];

  // Cria thread dos cores
  for (int i = 0; i < MultiCore; i++) {
    auto rc = pthread_create(&threads[indexThread], NULL, callCore, NULL);
    //rc==0?Success("Thread criada com sucesso"): error("Erro "+to_string(rc)+" ao criar a thread");
    indexThread++;
  }

  // Monitora a lista de processos
  while (!mmu.getFila().empty()) {
    if (changeInitProcess) {
      int initProcessIndex=mmu.getFila().front();
      initProcess = mmu.getProcesso(initProcessIndex); 
      usleep(100);

      // Tira da frente, e coloca no final,
      mmu.changeProcess(initProcessIndex);
      changeInitProcess=false;
    }
    
    // Checa quantidade de processos finalizados
    mmu.removeFinishedProcess();
  }

  resumo(escalonador,start);

  return 0;
}