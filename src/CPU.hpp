#ifndef _CPU
#define _CPU

// #include <bits/stdc++.h>

#include <map>

#include "Cache.hpp"
#include "RAM.hpp"
#include "RegisterBank.hpp"

#define dbg(x) cout << #x << " = " << x << '\n';

using namespace std;

enum InstructionType {
  LOAD,
  ILOAD,
  ADD,
  STORE,
  BEQ,
  J,
  SUB,
  MUL,
  DIV,
  SLT,
  BNE,
};

class CPU {
 private:
  int clock = 0;
  int PC = 0;

  bool write_data;
  int write_value;

  Cache cache;
  RegisterBank register_bank;
  string active_instruction;
  int op;

 public:
  bool InstructionFetch(vector<string> rom);
  void InstructionDecode();
  void Execute();
  void MemoryAccess(RAM& ram);
  void WriteBack();

  int ula(int op1, int op2, char oper);

  int get_register(int address);
  void set_register(int address, int value);

  void print_clock();
};

#endif