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
int Core::get_PC() { return this->PC; }

void Core::set_register(int address, int value) {
  register_bank.set_value(address, value);
}

void Core::set_process(PCB* process) {
  this->process=process;
  this->process->unblock_process();
  this->quantumStartTime=chrono::system_clock::now();
}

RegisterBank Core::get_registerBank(){ return this->register_bank; }

void Core::set_registerBank(vector<int> registers) {
  this->register_bank.set_registers(registers);
  this->PC=registers.back();
}

bool Core::InstructionFetch() {
  vector<string> codigo = this->process->get_instruction();
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

void Core::MemoryAccess() {
  // Descobre quanto de quantum tem ainda para fazer a busca de recursos com time limit
  int quantumDuration = GetDuration(this->quantumStartTime);
  int quantumLeft = this->process->get_quantum()-quantumDuration;
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
    // Caso recurso não seja usado volta uma instrução e retorna
    PC-=1;
    cout << "ENDEREÇO DE RAM SENDO USADO POR OUTRO PROCESSO" << endl;
    throw GetDuration(this->quantumStartTime);
  }
}

void Core::WriteBack() {
  if (!write_data) return;

  set_register(get_register(1), write_value);
  write_data = false;
}

int Core::CheckQuantum(){
  auto quantumDuration = GetDuration(this->quantumStartTime);
  if(quantumDuration>this->process->get_quantum()){
    cout << "QUANTUM ATINGIDO" << endl;
    throw(quantumDuration);
  }
  return this->process->get_quantum()-quantumDuration;
}

int GetDuration(chrono::_V2::system_clock::time_point baseTime){
  auto now = chrono::system_clock::now();
  return chrono::duration_cast<chrono::milliseconds>(now - baseTime).count();
}