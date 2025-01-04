#ifndef _Core
#define _Core

#include <map>

#include "Cache.hpp"
#include "RegisterBank.hpp"
#include <stdexcept>
#include <chrono>

using namespace std;

enum InstructionType {LOAD,ILOAD,ADD,STORE,BEQ,J,SUB,MUL,DIV,SLT,BNE};

class Core {
 private:
  int PC = 0;

  // Usado no writeback
  bool write_data;
  int write_value;

  Cache cache;
  RegisterBank register_bank;

  // Processo associado
  PCB* process;
  chrono::_V2::system_clock::time_point quantumStartTime;
  
  // Usados entre fases de pipeline para simular os impulsos da MIPS
  string active_instruction;
  int op;

  // Usado para garatir o core pra cada thread
  pthread_mutex_t lock;
 public:
  Core();
  Core(RAM* ram);
  bool InstructionFetch();
  void InstructionDecode();
  void Execute();
  void MemoryAccess();
  void WriteBack();

  int ula(int op1, int op2, char oper);

  pthread_mutex_t get_lock();

  int get_register(int address);
  void set_register(int address, int value);

  void set_process(PCB* process);
  int CheckQuantum();
};

#endif