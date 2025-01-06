#include "RAM.hpp"


RAM::RAM() {
  for (int j = 0; j < RamSize; j++){
    this->ram[j].first = 0;
  }
}

int RAM::Read(int address) {
  if (!(address < 0 || address >= RamSize)) {
    return ram[address].first;
  }
  return 0;
}

void RAM::Write_Update(int address, int value, int quantumLeft) {
  if (!(address < 0 || address >= RamSize)) {
    struct timespec timeoutTime;
    timeoutTime.tv_sec = quantumLeft;
    int checkLock = pthread_mutex_timedlock(&this->ram[address].second,&timeoutTime);
    checkLock==0 ? this->ram[address].first = value : throw exception();
  }
  else{
    throw exception();
  }
}

void RAM::Delete(int address) {
  if (!(address < 0 || address >= RamSize)) {
    this->ram[address].first = 0;
    pthread_mutex_unlock(&this->ram[address].second);
  }
}

void RAM::print(string& instruction) {
  writeRamToFile(instruction, ram);
}

void RAM::Store(int ramToStore,int address, int value){
  this->ram_store[ramToStore][address]=value;
}
int RAM::Load(int ramToLoad,int address){
  return this->ram_store[ramToLoad][address];
}