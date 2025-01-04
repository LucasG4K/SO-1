#ifndef _Core
#define _Core

#include <map>

#include "Cache.hpp"
#include "RAM.hpp"
#include "PCB.hpp"
#include "RegisterBank.hpp"

using namespace std;

enum InstructionType {LOAD,ILOAD,ADD,STORE,BEQ,J,SUB,MUL,DIV,SLT,BNE};

class Core {
 private:
  int clock = 0;
  int PC = 0;

  bool write_data;
  int write_value;

  Cache cache;
  PCB* process;
  RegisterBank register_bank;
  string active_instruction;
  int op;

  bool inUse;

 public:
  Core();
  Core(RAM* ram);
  bool InstructionFetch(vector<string> rom);
  void InstructionDecode();
  void Execute();
  void MemoryAccess(int ramProcess);
  void WriteBack();

  int ula(int op1, int op2, char oper);

  int get_inUse();
  void switch_inUse();

  int get_register(int address);
  void set_register(int address, int value);

};

#endif