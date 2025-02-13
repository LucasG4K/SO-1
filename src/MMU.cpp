#include "MMU.hpp"
#include <algorithm>

MMU::MMU(){
  filaProcessos=getFilaProcessos(&filaProcessosInt);
  for (int i = 0; i < filaProcessos.size(); i++){
    auto temp=bitset<2>(i);
    tlb[i]=temp;
  }
}

vector<int> MMU::getFila(){return this->filaProcessosInt;}
vector<PCB*> MMU::getProcessos(){return this->filaProcessos;}
PCB* MMU::getProcesso(int i){
  return this->filaProcessos[tlb[i].to_ulong()];
}

void MMU::removeFinishedProcess(){
  for (int i = 0; i < filaProcessosInt.size(); i++) {
    if(getProcesso(i)->get_state()=="finished") {
      filaProcessosInt.erase(filaProcessosInt.begin()+i);
    };
  }
}

void MMU::changeProcess(int index){
  filaProcessosInt.erase(filaProcessosInt.begin());
  filaProcessosInt.push_back(index);
}


void MMU::sortProcess(){
  sort(filaProcessosInt.begin(), filaProcessosInt.end(),
      [this](int const & a, int const & b) -> bool {
        return getProcesso(a)->get_et() < getProcesso(b)->get_et();
      });
}
