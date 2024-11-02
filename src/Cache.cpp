#include "Cache.hpp"
#include <iostream>

Cache::Cache() {
  for (int i=0; i<CACHE_SIZE; ++i)
    cacheData[i] = {-1, false}; // address, {value, dirty}
}

bool Cache::read(int address, int& data, RAM &ram) {
  if (cacheData.count(address)) {
    data = cacheData[address].first;
    return true; // cache hit
  } else {
    data = ram.get_value(address);
    write(address, data, ram);
    return false; // cache miss
  }
}

void Cache::write(int address, int data, RAM &ram) {
  if (cacheData.size() >= CACHE_SIZE && cacheData.count(address)==false) // full cache && address not in cacheData 
    remove(ram);
  
  cacheData[address] = {data, true};
  fifoQueue.push(address);
}

void Cache::remove(RAM &ram) {
  if (fifoQueue.empty()) return;

  int removeAddress = fifoQueue.front();
  fifoQueue.pop();

  if (cacheData[removeAddress].second) {
    int value = cacheData[removeAddress].first;
    ram.set_value(removeAddress, value);
  }

  cacheData.erase(removeAddress);
}