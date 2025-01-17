#include "RAM.hpp"


RAM::RAM() {
  for (int j = 0; j < RamSize; j++){
    this->ram[j].first = 0;

    this->ram[j].second = new pthread_mutex_t;
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE); // Set mutex to recursive
    pthread_mutex_init(this->ram[j].second, &attr);
    pthread_mutexattr_destroy(&attr);
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
    int checkLock = pthread_mutex_timedlock(this->ram[address].second,&timeoutTime);
    if (checkLock == 0) {
      this->ram[address].first = value;
      Checkpoint("Deu lock em "+to_string(address));
    } else if (checkLock == ETIMEDOUT) {
      Error("Deu timeout em "+to_string(address));
      throw exception();
    } else {
      Error("Deu erro em "+to_string(address));
      throw exception();
    }
  }
  else{
    throw exception();
  }
}

void RAM::Delete(int address) {
  if (!(address < 0 || address >= RamSize)) {
    this->ram[address].first = 0;
    pthread_mutex_unlock(this->ram[address].second);
  }
}

void RAM::print(string& instruction) {
  writeRamToFile(instruction, ram);
}

void RAM::FreeMemory(vector<int> addresses){
  for (auto &&i : addresses)
  {
    auto retorno=pthread_mutex_unlock(this->ram[i].second);
    if(retorno==1)
      Error("Thread não contem o recurso "+i);
    while(retorno==0){
      Checkpoint("Deu unlock em "+to_string(i));
      retorno=pthread_mutex_unlock(this->ram[i].second);
    }
  }
}