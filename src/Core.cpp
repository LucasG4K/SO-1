#include "Core.hpp"

int GetDuration(chrono::_V2::system_clock::time_point baseTime){
  auto now = chrono::system_clock::now();
  return chrono::duration_cast<chrono::milliseconds>(now - baseTime).count();
}

Core::Core() {}
Core::Core(RAM* ram) : lock(new pthread_mutex_t) {
  pthread_mutex_init(lock, NULL);
  this->ram = ram;
  this->cache = Cache();
  this->ula_counter=0;
  this->active_LSH=0;
}

map<string, InstructionType> instruction_map = {
    {"ILOAD", ILOAD}, {"ADD", ADD}, {"STORE", STORE}, {"BEQ", BEQ},
    {"J", J},         {"SUB", SUB}, {"MUL", MUL}};

int Core::ula(int op1, int op2, char oper) {
  ula_counter++;

  Checkpoint("ULA = " + to_string(op1) + " : " + to_string(op2) + " : " + to_string(oper));

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

pthread_mutex_t* Core::get_lock() { return this->lock; }
int Core::getUlaCounter() { return this->ula_counter; }
int Core::get_register(int address) { return register_bank.get_value(address); }
int Core::get_PC() { return this->PC; }

void Core::set_register(int address, int value) {
  register_bank.set_value(address, value);
}

void Core::set_process(PCB* process) {
  this->process = process;
  this->quantumStartTime = chrono::system_clock::now();
}

vector<int> Core::get_registerBank() {
  vector<int> registers;
  for (auto&& i : this->register_bank.get_registers()) {
    registers.push_back(i.value);
  }
  registers.push_back(this->PC);
  return registers;
}

void Core::set_registerBank(vector<int> registers) {
  this->register_bank.set_registers(registers);
  this->PC = registers.back();
}

bool Core::InstructionFetch() {
  vector<string> codigo = this->process->get_instruction();
  if (PC >= codigo.size()) return false;

  active_instruction = codigo[PC];

  Checkpoint("Instrução: " + active_instruction);

  PC++;

  return true;
}

uint32_t Core::generateLSH(int op, int reg1, int reg2) {
  // Combina o opcode e os valores dos registradores para gerar o LSH
  uint32_t lsh = static_cast<uint32_t>(op) * 100000; // operation type    ADD  kjdasdkjad   12    15   100000+12*1000+15*100=
  lsh += reg1 * 1000; // reg1
  lsh += reg2 * 100; // reg2
  return lsh;
}

void Core::InstructionDecode() {
  vector<string> linha = split(active_instruction);

  op = instruction_map[linha[0]];

  int reg1 = linha[1] != "!" ? stoi(linha[1]) : 0;
  int reg2 = linha[2] != "!" ? stoi(linha[2]) : 0;
  int reg3 = linha[3] != "!" ? stoi(linha[3]) : 0;

  set_register(1, reg1);
  set_register(2, reg2);
  set_register(3, reg3);

  register_bank.set_dirty(1);
  register_bank.set_dirty(2);
  register_bank.set_dirty(3);

  // Gera o LSH com base na instrução decodificada
  active_LSH = generateLSH(op, get_register(reg2), get_register(reg3));
}


void Core::Execute() {
  int data;
  if (cache.read(active_LSH, data)) { // Cache hit
    write_value = data;
    write_data = true;
    cache.printCache();
    return;
  }

  // Cache miss
  int reg2 = get_register(get_register(2));
  int reg3 = get_register(get_register(3));

  switch (op) {
    case ADD:
      write_value = ula(reg2, reg3, '+');
      cache.writeInCache(active_LSH, write_value);
      break;
    case SUB:
      write_value = ula(reg2, reg3, '-');
      cache.writeInCache(active_LSH, write_value);
      break;
    case MUL:
      write_value = ula(reg2, reg3, '*');
      cache.writeInCache(active_LSH, write_value);
      break;
    case DIV:
      write_value = ula(reg2, reg3, '/');
      cache.writeInCache(active_LSH, write_value);
      break;
    case SLT:
      write_value = reg2 < reg3;
      break;
    case BNE:
      if (reg2 != get_register(1))
        PC = reg3 - 1;
      break;
    case BEQ:
      if (reg2 == get_register(1))
        PC = reg3 - 1;
      break;
    case J:
      PC = get_register(1) - 1;
      break;
  }

  write_data = true;
}


void Core::MemoryAccess() {
  // Descobre quanto de quantum tem ainda para fazer a busca de recursos com time limit
  int quantumDuration = GetDuration(this->quantumStartTime);
  int quantumLeft = this->process->get_quantum() - quantumDuration;
  try {
    switch (op) {
      case LOAD: {
        int holder;
        write_value = cache.read(get_register(2), holder);
        write_data = true;
        break;
      }

      case ILOAD: {
        write_value = get_register(2);
        write_data = true;
        break;
      }

      case STORE: {
        (*ram).Write_Update(get_register(2), get_register(get_register(1)), quantumLeft);  // escreve na cache e na ram
        process->add_memory(get_register(2));  // caso funcione adiciona posicao de memoria no processo pra dar unblock
        break;
      }
    }
  } catch (const exception& e) {
    // Caso recurso não seja usado volta uma instrução e retorna
    PC -= 1;
    Error("ENDEREÇO DE RAM SENDO USADO POR OUTRO PROCESSO");
    throw GetDuration(this->quantumStartTime);
  }
}

void Core::WriteBack() {
  if (!write_data) return;

  set_register(get_register(1), write_value);
  write_data = false;
}

int Core::CheckQuantum() {
  auto quantumDuration = GetDuration(this->quantumStartTime);
  if (quantumDuration > this->process->get_quantum()) {
    Error("QUANTUM ATINGIDO");
    throw(quantumDuration);
  }
  return this->process->get_quantum() - quantumDuration;
}
