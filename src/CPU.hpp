#ifndef REGISTERBANK
#define REGISTERBANK

#include "RAM.hpp"

#include <bits/stdc++.h>

#define dbg(x) cout<<#x<<" = "<<x<<'\n';

using namespace std;

typedef struct Register {
    int value;
    bool dirty;
} Register;

class CPU {
    private:
        int PC = 0;
        Register registers[32]; 
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