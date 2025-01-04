#ifndef CACHE_HPP
#define CACHE_HPP

#include <unordered_map>
#include <queue>
#include "RAM.hpp"

using namespace std;

class Cache {
 private:
  RAM* ram;
  static const int CACHE_SIZE = 64;
  unordered_map<int, pair<int, bool>> cacheData; // address, {value, dirty}
  queue<int> fifoQueue;
  void remove();

 public:
  Cache();
  Cache(RAM* ram);
  bool read(int address);
  void write(int address, int data);
  void printCache();
};

#endif  