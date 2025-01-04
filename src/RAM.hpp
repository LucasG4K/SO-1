#ifndef _RAM_HPP
#define _RAM_HPP
#define RamSize 32
#define NumRam 32

#include <iostream>
#include <stdexcept>
#include "utils.hpp"

using namespace std;

class RAM {
  private:
    pair<int,bool> ram[RamSize];
    int ram_store[NumRam][RamSize];

  public:
   RAM();  
   int Read(int address);
   void Write_Update(int address, int value);  
   void Delete(int address);  
   void print(string& instruction); 
};

#endif 
