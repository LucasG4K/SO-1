#ifndef CACHE_HPP
#define CACHE_HPP

#include <unordered_map>
#include <queue>
#include "RAM.hpp"

using namespace std;

class Cache {
 private:
  static const int CACHE_SIZE = 8;
  unordered_map<int, pair<int, bool>> cacheData; // address, {value, dirty}
  queue<int> fifoQueue;
  void remove(RAM &ram);

 public:
  Cache();
  bool read(int address, RAM &ram);
  void write(int address, int data, RAM &ram);
  void printCache();
};

#endif  