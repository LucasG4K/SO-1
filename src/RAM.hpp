#ifndef _RAM_HPP
#define _RAM_HPP

#include <iostream>

using namespace std;

class RAM {
  private:
    int values[32];

  public:
   RAM();  
   int get_value(int address);
   void set_value(int address, int value);  
   void print(); 
};

#endif 
