#ifndef REGISTERBANK
#define REGISTERBANK
#include <bits/stdc++.h>
#define dbg(x) cout<<#x<<" = "<<x<<'\n';

using namespace std;

class CPU {
    private:
        int PC = 0;
        int registradores[32] = {0}; 
        int ram[32] = {0}; // Na arquitetura de von neumann, é separado, porém não justifica uma unica classe pra isso
        string active_instruction;
        string op;
    public:
        void InstructionFetch(vector<string> rom);
        void InstructionDecode();
        void Execute();
        void MemoryAccess();
};

#endif