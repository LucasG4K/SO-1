#ifndef _RAM_HPP
#define _RAM_HPP

#include <iostream>
#include <stdexcept>
#include "SO.hpp"

using namespace std;

class RAM {
  private:
    pair<int,pthread_mutex_t> ram[RamSize];
    vector<PCB*> filaProcessos;

  public:
   RAM();  
   int Read(int address);
   void Write_Update(int address, int value, int quantumLeft);  
   void Delete(int address);  
   void FreeMemory(vector<int> addresses);
   void print(string& instruction); 
};

#endif 
