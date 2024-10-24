#include "CPU.hpp"

#define dbg(x) cout << #x << " = " << x << '\n';

void printRegisters(Register *reg)
{
    for (int i = 0; i < 32; i++)
    {
        cout << reg[i].value << " ";
    }
    cout << '\n';
}

int ULA(int op1, int op2, char oper)
{
    if (oper == '+')
        return op1 + op2;
    else if (oper == '-')
        return op1 - op2;
    return 0;
}

vector<string> splitString(const string &str)
{
    vector<string> result;
    istringstream iss(str);
    string word;

    while (iss >> word)
    {
        result.push_back(word);
    }

    while(result.size() < 4) {
        result.push_back("!");
    }

    return result;
}

void CPU::InstructionFetch(vector<string> codigo)
{
    this->active_instruction = codigo[this->PC];
    this->PC++;

    dbg(this->active_instruction);
}

void CPU::InstructionDecode()
{
    vector<string> linha = splitString(this->active_instruction);

    this->op = linha[0];

    // register[1] -> write_register
    // register[2] -> 

    for (auto l : linha) dbg(l);

    if (linha[1] != "!")
    {
        this->registers[1].value = stoi(linha[1]);
        this->registers[1].dirty = true;
    } 

    if (linha[2] != "!") {
         this->registers[2].value = stoi(linha[2]);
         this->registers[2].dirty = true; 
    }

    if (linha[3] != "!") 
    {
        this->registers[3].value = stoi(linha[3]);
        this->registers[3].dirty = true;
    } 

    cout << "Decode: ";
    printRegisters(this->registers);
}

void CPU::Execute() // Unidade de controle
{
    // ADD 8  9 10 -- Salva no registrador 8, a soma dos valores presentes no registrador 9 e 10
    if (this->op == "ADD")
        this->registers[this->registers[1].value].value = ULA(this->registers[this->registers[2].value].value, this->registers[this->registers[3].value].value, '+');
    else if (this->op == "SUB")
        this->registers[this->registers[1].value].value = ULA(this->registers[this->registers[2].value].value, this->registers[this->registers[3].value].value, '-');

    cout << "Execute: ";
    printRegisters(this->registers);
}

void CPU::MemoryAccess(RAM& ram)
{
    // LW 8 57 -- Carrega no registrador 8 o valor presente na posição 57 da ram
    if (this->op == "LOAD")
        this->registers[this->registers[2].value].value = ram.get_value(this->registers[3].value);
    // LI 8 57 -- Carrega no registrador 8 o valor 57
    if (this->op == "ILOAD")
        this->registers[this->registers[2].value].value = this->registers[3].value;
    // SW 8 57 -- Carrega na posição 57 da ram o valor do registrador 8
    else if (this->op == "STORE")
        ram.set_value(this->registers[3].value, this->registers[this->registers[2].value].value);
    
    ram.print();
}