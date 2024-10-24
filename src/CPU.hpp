#ifndef _CPU
#define _CPU

#include <bits/stdc++.h>

#include "RAM.hpp"
#include "RegisterBank.hpp"

#define dbg(x) cout << #x << " = " << x << '\n';

using namespace std;

class CPU {
 private:
  int PC = 0;
  RegisterBank register_bank;
  string active_instruction;
  string op;

 public:
  void InstructionFetch(vector<string> rom);
  void InstructionDecode();
  void Execute();
  void MemoryAccess(RAM& ram);
  void WriteBack();
};

#endif