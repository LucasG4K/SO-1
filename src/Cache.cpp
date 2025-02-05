#include "Cache.hpp"
#include <iostream>

Cache::Cache() {}
Cache::Cache(RAM* ram) {this->ram=ram;}

bool Cache::read(int address, int &data) { //colocar int &value para retornar o valor se for bool
  if (cacheData.count(address)) { // hit
    data = cacheData[address];
    // cout << "CACHE HIT: Endereço " << address << " encontrado na cache com valor " << data << ".\n";
    return true;
  }
  // miss
  // cout << "CACHE MISS: Endereço " << address << " não encontrado na cache.\n";
  return false;
}

void Cache::writeInCache(int address, int data) { 
  if(UseCache){
    // 1. tenta sobrescrever algum valor
    if (cacheData.count(address)) {
      queue<int> ref;
      while (!fifoQueue.empty()) {
        if (fifoQueue.front() != address)
          ref.push(fifoQueue.front());
        fifoQueue.pop();
      }
      fifoQueue = ref;
    }
    // 2. verifica se a cache está cheia; se estiver remove o primeiro da fila de endereços e coloca o novo endereço no final
    else if (cacheData.size() >= CACHE_SIZE) {
      cacheData.erase(fifoQueue.front());
      fifoQueue.pop();
    }

    fifoQueue.push(address);
    cacheData[address] = data;
  }
}

void Cache::printCache() {
  for (const auto& [address, value] : cacheData) {
    cout << "CACHE[" << address << "]: " << value << endl;
  }

  queue<int> tempQueue = fifoQueue;
  cout << "FIFO order: ";
  while (!tempQueue.empty()) {
    cout << tempQueue.front()  << ' ';
    tempQueue.pop();
  }
  cout << '\n';
}
