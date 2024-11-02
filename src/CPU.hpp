#ifndef _CPU
#define _CPU

#include <bits/stdc++.h>

#include "RAM.hpp"
#include "RegisterBank.hpp"
#include "Cache.hpp"

#define dbg(x) cout << #x << " = " << x << '\n';

using namespace std;

class CPU {
 private:
  int PC = 0;
  pair<bool,int> ValueToWrite;
  Cache cache;
  RegisterBank register_bank;
  string active_instruction;
  string op;

 public:
  bool InstructionFetch(vector<string> rom);
  void InstructionDecode();
  void Execute();
  void MemoryAccess(RAM& ram);
  void WriteBack();
};

#endif