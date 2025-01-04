#include "Core.hpp"

Core::Core(){}
Core::Core(RAM* ram){
  this->cache=Cache(ram);
  this->inUse=true;
}

map<string, InstructionType> instruction_map = {
    {"ILOAD", ILOAD}, {"ADD", ADD}, {"STORE", STORE}, {"BEQ", BEQ},
    {"J", J},         {"SUB", SUB}, {"MUL", MUL}};

int Core::ula(int op1, int op2, char oper) {
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

int Core::get_inUse(){return this->inUse;}
void Core::switch_inUse(){this->inUse=!this->inUse;}

int Core::get_register(int address) { return register_bank.get_value(address); }

void Core::set_register(int address, int value) {
  register_bank.set_value(address, value);
}

bool Core::InstructionFetch(vector<string> codigo) {
  if (PC >= codigo.size()) return false;

  active_instruction = codigo[PC];

  cout << active_instruction << endl;

  PC++;

  return true;
}

void Core::InstructionDecode() {
  vector<string> linha = split(active_instruction);

  op = instruction_map[linha[0]];

  if (linha[1] != "!") {
    set_register(1, stoi(linha[1]));
    register_bank.set_dirty(1);
  }

  if (linha[2] != "!") {
    set_register(2, stoi(linha[2]));
    register_bank.set_dirty(2);
  }

  if (linha[3] != "!") {
    set_register(3, stoi(linha[3]));
    register_bank.set_dirty(3);
  }

}

void Core::Execute()  // Unidade de controle
{
  switch (op) {
    case ADD: {
      write_value = ula(get_register(get_register(2)),
                        get_register(get_register(3)), '+');

      write_data = true;
      break;
    }
    case SUB: {
      write_value = ula(get_register(get_register(2)),
                        get_register(get_register(3)), '-');

      write_data = true;
      break;
    }
    case MUL: {
      write_value = ula(get_register(get_register(2)),
                        get_register(get_register(3)), '*');

      write_data = true;
      break;
    }
    case DIV: {
      write_value = ula(get_register(get_register(2)),
                        get_register(get_register(3)), '/');

      write_data = true;
      break;
    }
    case SLT: {
      write_value =
          get_register(get_register(2)) < get_register(get_register(3));

      write_data = true;
      break;
    }
    case BNE: {
      if (get_register(get_register(2)) != get_register(get_register(1))) {
        PC = get_register(3) - 1;
      }
      break;
    }
    case BEQ: {
      if (get_register(get_register(2)) == get_register(get_register(1))) {
        PC = get_register(3) - 1;
      }
      break;
    }
    case J: {
      PC = get_register(1) - 1;
      break;
    }
  }

}

void Core::MemoryAccess(int ramProcess) {
  try
  {
    switch (op) {
      case LOAD: {      
        write_value = cache.read(get_register(2));
        write_data = true;
        break;
      }

      case ILOAD: {
        write_value = get_register(2);
        write_data = true;
        break;
      }

      case STORE: {
        cache.write(get_register(2), get_register(get_register(1))); // escreve na cache e na ram
        //ram.print(ramProcess, active_instruction);
        break;
      }
    }
  }
  catch(const exception& e)
  {
    cout << "ENDEREÇO DE RAM SENDO USADO POR OUTRO PROCESSO" << endl;
    //BloquearProcesso
  }
}

void Core::WriteBack() {
  if (!write_data) return;

  set_register(get_register(1), write_value);
  write_data = false;
}