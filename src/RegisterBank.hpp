#ifndef REGISTER_BANK
#define REGISTER_BANK

#include <vector>
#include <iostream>
#include "SO.hpp"

using namespace std;

typedef struct Register {
  int value;
  bool dirty;
} Register;

class RegisterBank {
 private:
  vector<Register> registers;

 public:
  RegisterBank();

  int get_value(int address);
  void set_value(int address, int value);
  void set_dirty(int address);
  void set_clean(int address);

  vector<Register> get_registers();
  void set_registers(vector<int> registers);

  void print();
};

#endif