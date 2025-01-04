#include "Core.hpp"

Core::Core(){}
Core::Core(RAM* ram){
  this->cache=Cache(ram);  
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

pthread_mutex_t Core::get_lock(){return this->lock;}

int Core::get_register(int address) { return register_bank.get_value(address); }

void Core::set_register(int address, int value) {
  register_bank.set_value(address, value);
}

void Core::set_process(PCB* process) {
  this->process=process;
  this->process->unblock_process();
  this->quantumStartTime=chrono::system_clock::now();
}

bool Core::InstructionFetch() {
  vector<string> codigo = this->process->get_instruction();
  if (PC >= codigo.size()) return false;

  active_instruction = codigo[PC];

  cout << active_instruction << endl;

  PC++;

  return true;
  CheckQuantum();
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
  CheckQuantum();
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
  CheckQuantum();
}

void Core::MemoryAccess() {
  int quantumLeft = CheckQuantum();
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
        cache.write(get_register(2), get_register(get_register(1)),quantumLeft); // escreve na cache e na ram
        break;
      }
    }
  }
  catch(const exception& e)
  {
    cout << "ENDEREÇO DE RAM SENDO USADO POR OUTRO PROCESSO" << endl;
  }
  CheckQuantum();
}

void Core::WriteBack() {
  if (!write_data) return;

  set_register(get_register(1), write_value);
  write_data = false;
  CheckQuantum();
}

int Core::CheckQuantum(){
  auto now = chrono::system_clock::now();
  auto quantumDuration = chrono::duration_cast<chrono::milliseconds>(now - this->quantumStartTime).count();
  if(quantumDuration>this->process->get_quantum()){
    cout << "QUANTUM ATINGIDO" << endl;
    this->process->block_process(quantumDuration);
    throw exception();
  }
  return this->process->get_quantum()-quantumDuration;
}