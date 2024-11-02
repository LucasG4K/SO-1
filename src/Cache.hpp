#ifndef CACHE_HPP
#define CACHE_HPP

#include <unordered_map>
#include <queue>

using namespace std;

class Cache {
 private:
  static const int CACHE_SIZE = 32;
  unordered_map<int, pair<int, bool>> cacheData; 
  queue<int> fifoQueue;
  void remove();

 public:
  Cache();
  void read(int address, int& data);
  void write(int address, int data); 
};

#endif  