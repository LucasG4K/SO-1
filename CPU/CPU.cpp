#include "CPU.hpp"

void printRegisters(int* reg){
    for (int i = 0; i < 32; i++)
    {
        cout<<reg[i]<<" ";
    }
    cout<<'\n';
}

int ULA(int op1, int op2, char oper){
    if(oper=='+')
        return op1+op2;
    else if(oper=='-')
        return op1-op2;
    return 0;
}

vector<string> splitString(const string& str) {
    vector<string> result;
    istringstream iss(str);
    string word;

    while (iss >> word) {
        result.push_back(word);
    }

    return result;
}

void CPU::InstructionFetch(vector<string> codigo)
{
    this->active_instruction=codigo[this->PC];
    this->PC++;
    dbg(this->active_instruction);
}

void CPU::InstructionDecode()
{
    vector<string> linha = splitString(this->active_instruction);
    this->op=linha[0];
    dbg(this->op);
    
    if(linha[1]!="!")
        this->registradores[1] = stoi(linha[1]); // write_register
    if(linha[2]!="!")
        this->registradores[2] = stoi(linha[2]); // read_register_1
    if(linha[3]!="!")
        this->registradores[3] = stoi(linha[3]); // read_register_2
    cout<<"Decode: ";
    printRegisters(this->registradores);
}

void CPU::Execute() // Unidade de controle
{
    // ADD 8  9 10 -- Salva no registrador 8, a soma dos valores presentes no registrador 9 e 10
    if (this->op=="ADD")
        this->registradores[this->registradores[1]]= ULA(this->registradores[this->registradores[2]],this->registradores[this->registradores[3]],'+');
    // SUB 8  9 10 -- Salva no registrador 8, a subtração dos valores presentes no registrador 9 e 10
    else if(this->op=="SUB")
        this->registradores[this->registradores[1]]= ULA(this->registradores[this->registradores[2]],this->registradores[this->registradores[3]],'-');
    cout<<"Execute: ";
    printRegisters(this->registradores);
}

void CPU::MemoryAccess()
{ 
    // LW 8 57 -- Carrega no registrador 8 o valor presente na posição 57 da ram
    if(this->op=="LW")
        this->registradores[this->registradores[2]]=this->ram[this->registradores[3]];
    // LI 8 57 -- Carrega no registrador 8 o valor 57
    if(this->op=="LI")
        this->registradores[this->registradores[2]]=this->registradores[3];
    // SW 8 57 -- Carrega na posição 57 da ram o valor do registrador 8
    else if(this->op=="SW")
        this->ram[this->registradores[3]]=this->registradores[this->registradores[2]];
    cout<<"RAM: ";
    printRegisters(this->ram);
}