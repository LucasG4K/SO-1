#ifndef _MMU
#define _MMU
#include "CPU.hpp"
#include <bitset>
#include <unordered_map>

class MMU {
  private:
    vector<int> filaProcessosInt;
    unordered_map<int,bitset<2>> tlb;
    vector<PCB*> filaProcessos;
  public:
    MMU();
    vector<int> getFila();
    vector<PCB*> getProcessos();
    PCB* getProcesso(int index);
    void removeFinishedProcess();
    void changeProcess(int index);
    void sortProcess();
};

#endif