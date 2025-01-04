#ifndef _RAM_HPP
#define _RAM_HPP

#include <iostream>
#include <stdexcept>
#include "SO.hpp"

using namespace std;

class RAM {
  private:
    pair<int,pthread_mutex_t> ram[RamSize];
    int ram_store[NumRamStorage][RamSize];

  public:
   RAM();  
   int Read(int address);
   void Write_Update(int address, int value, int quantumLeft);  
   void Delete(int address);  
   void print(string& instruction); 
};

#endif 
