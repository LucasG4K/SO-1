#ifndef CACHE_HPP
#define CACHE_HPP

#include <unordered_map>
#include <queue>
#include "RAM.hpp"

using namespace std;

class Cache {
 private:
  RAM* ram;
  unordered_map<int, int> cacheData; // address, value
  queue<int> fifoQueue;
  
 public:
  Cache();
  Cache(RAM* ram);
  void writeInCache(int address, int data);
  bool read(int address, int &data);
  void write(int address, int data, int quantumLeft);
  void printCache();
};

#endif  