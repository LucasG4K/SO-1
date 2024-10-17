#ifndef REGISTERBANK
#define REGISTERBANK
#include <bits/stdc++.h>

using namespace std;

class CPU {
    private:
        int PC = 0;
        bool mem_read;
        int register1;
        int register2;
        int write_register;
        vector<float> ram[32]; // Na arquitetura de von neumann, é separado, porém não justifica uma unica classe pra isso
        string active_instruction;
    public:
        void InstructionFetch(vector<string> rom);
        void InstructionDecode();   
        // Recebe uma string ex.: "ADD 0x60 0x20 0x40", splita, salva valor dos endereços nos registradores 0x60-write, 0x20-reg1, 0x40-reg2;
        // Se for operação de memória, decide se salva ou lê (simula parte da instrução de memoria com um if) [salva, no mem_read]
        void Execute();             // 
};


class CPUdoManel {
    private:
    
    vector<string>ram;
 
    int PC = 0;

    string instruction;

    int op;
    int val1;
    int val2;
    int val3;

    int r_mem;

    public:
        void InstructionFetch() {
            instruction = ram[PC];
            PC += 4;
        };

        void InstructionDecode() {

            op = instruction[0];
            val1 = instruction[0];
            val2 = instruction[0];
           
        }; // Ler a instrução, com switch, vai interpretar os argumentos, e encaminhar pra ula
        
        void Execute() {

            switch(op) {
                case 1: {
                    val3 = val1 + val2;
                }

            }

        }

         void MemoryAccess() {
            
        };

         void WriteBack() {
            r_mem = val3;
        };


};

#endif