#include "CPU/CPU.hpp"

vector<string> read_ROM(){

}

int main(){
    int clock=0;
    read_ROM();
    CPU cpu;
    
    while (clock>=0)
    {
        cpu.InstructionFetch();
        cpu.InstructionDecode();
        cpu.Execute();
    }
    
}