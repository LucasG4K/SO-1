#include "Cache.hpp"
#include <iostream>

Cache::Cache() {}
Cache::Cache(RAM* ram) {this->ram=ram;}

bool Cache::read(int address) {
  int cacheAddress = address % CACHE_SIZE;

  if (cacheData.count(address)) {
    return cacheData[cacheAddress].first;
  } else {
    write(address, (*ram).Read(address));
    return (*ram).Read(address);
  }
}

void Cache::write(int address, int data) {
  (*ram).Write_Update(address, data);
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
        else 
          (*ram).Write_Update(fifoQueue.front(), cacheData[cacheAddress].first);
        fifoQueue.pop();
      }
      fifoQueue = ref;
    }
  }

  if (fifoQueue.size() >= CACHE_SIZE) {
    remove();
    cout << "ENDEREÇO CACHE CHEIO: ALOCANDO PARA RAM" << endl;
  }

  fifoQueue.push(address);
  cacheData[cacheAddress] = {data, true};
}



void Cache::remove() {
  if (fifoQueue.empty()) return;

  int ramAddress = fifoQueue.front();
  int cacheAddress = ramAddress % CACHE_SIZE;
  fifoQueue.pop();

  if (cacheData[cacheAddress].second)
    (*ram).Write_Update(ramAddress, cacheData[cacheAddress].first);

  cacheData.erase(cacheAddress);
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