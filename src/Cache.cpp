#include "Cache.hpp"
#include <iostream>

Cache::Cache() {}
Cache::Cache(RAM* ram) {this->ram=ram;}

bool Cache::read(int address) {
  int cacheAddress = address % CACHE_SIZE;

  if (cacheData.count(address)) {
    return cacheData[cacheAddress].first;
  } else {
    writeInCache(address, (*ram).Read(address));
    return (*ram).Read(address);
  }
}

void Cache::writeInCache(int address, int data){
  int cacheAddress = address % CACHE_SIZE;

  if (cacheData.count(cacheAddress)) {
    if (cacheData[cacheAddress].second) {
      
      cout << "ENDEREÇO CACHE OCUPADO: ALOCANDO PARA RAM" << endl;

      int qsize = fifoQueue.size();
      int counter = 0;

      queue<int> ref;
      while (!fifoQueue.empty()) {
        if (fifoQueue.front() % CACHE_SIZE != cacheAddress)
          ref.push(fifoQueue.front());
        fifoQueue.pop();
      }
      fifoQueue = ref;
    }
  }

  fifoQueue.push(address);
  cacheData[cacheAddress] = {data, true};
}

void Cache::write(int address, int data, int quantumLeft) {
  (*ram).Write_Update(address, data, quantumLeft);
  writeInCache(address, data);
}

void Cache::printCache() {
  for (const auto& [address, value_dirty] : cacheData) {
    cout << "CACHE[" << address << "]: " << value_dirty.first << " (dirty: " << value_dirty.second << ")\n";
  }

  queue<int> tempQueue = fifoQueue;
  cout << "FIFO order: ";
  while (!tempQueue.empty()) {
    cout << tempQueue.front()  << ' ';
    tempQueue.pop();
  }
  cout << '\n';
}