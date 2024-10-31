#include "CPU.hpp"

int ULA(int op1, int op2, char oper) {
  if (oper == '+')
    return op1 + op2;
  else if (oper == '-')
    return op1 - op2;
  else if (oper == '*')
    return op1 * op2;
  else if (oper == '/')
    return op1 / op2;
  return 0;
}

vector<string> split(const string &str) {
  vector<string> result;
  istringstream iss(str);
  string word;

  while (iss >> word) {
    result.push_back(word);
  }

  while (result.size() < 4) {
    result.push_back("!");
  }

  return result;
}

bool CPU::InstructionFetch(vector<string> codigo) {
  if(PC<codigo.size()){
    active_instruction = codigo[PC];
    PC++;

    // dbg(PC);
    // dbg(active_instruction);
    return true;
  }
  else return false;
}

void CPU::InstructionDecode() {
  vector<string> linha = split(active_instruction);

  op = linha[0];

  // for (auto l : linha) dbg(l);

  if (linha[1] != "!") {
    register_bank.set_value(1, stoi(linha[1]));
    register_bank.set_dirty(1);
  }

  if (linha[2] != "!") {
    register_bank.set_value(2, stoi(linha[2]));
    register_bank.set_dirty(2);
  }

  if (linha[3] != "!") {
    register_bank.set_value(3, stoi(linha[3]));
    register_bank.set_dirty(3);
  }
}

void CPU::Execute()  // Unidade de controle
{
  int register1 = register_bank.get_value(1);
  int register2 = register_bank.get_value(2);
  int register3 = register_bank.get_value(3);
  int result = 0;

  if (op == "ADD") {
    result = ULA(register_bank.get_value(register2),
                 register_bank.get_value(register3), '+');
    ValueToWrite.first = true;
  } else if (op == "SUB") {
    result = ULA(register_bank.get_value(register2),
                 register_bank.get_value(register3), '-');
    ValueToWrite.first = true;
  } else if (op == "MUL") {
    result = ULA(register_bank.get_value(register2),
                 register_bank.get_value(register3), '*');
    ValueToWrite.first = true;
  } else if (op == "DIV") {
    result = ULA(register_bank.get_value(register2),
                 register_bank.get_value(register3), '/');
    ValueToWrite.first = true;
  } else if (op == "SLT") {
    ValueToWrite.first = true;
    if (register_bank.get_value(register2) <
        register_bank.get_value(register3)) {
      result = 1;
    } else {
      result = 0;
    }
  } else if (op == "BNE") {
    if (register_bank.get_value(register2) !=
        register_bank.get_value(register1)) {
      PC = register3 - 1;
    }
  } else if (op == "BEQ") {
    if (register_bank.get_value(register2) ==
        register_bank.get_value(register1)) {
      PC = register3 - 1;
    }
  } else if (op == "J") {
    PC = register1 - 1;
  }

  ValueToWrite.second = result;
}

void CPU::MemoryAccess(RAM &ram) {
  // cout << "Memory Access" << endl;

  if (op == "LOAD") {
    ValueToWrite = {true, ram.get_value(register_bank.get_value(2))};
  } else if (op == "ILOAD") {
    ValueToWrite = {true, register_bank.get_value(2)};
  } else if (op == "STORE") {
    ram.set_value(register_bank.get_value(2),
                  register_bank.get_value(register_bank.get_value(1)));
  }

  // ram.print();

}

void CPU::WriteBack() {
  if (ValueToWrite.first == true) {
    register_bank.set_value(register_bank.get_value(1), ValueToWrite.second);
    ValueToWrite.first = false;
  }

  // register_bank.print();
}
