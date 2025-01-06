#ifndef _SO
#define _SO
#define endl '\n'

#define MultiCore 2
#define RamSize 32
#define NumRamStorage 32
#define RegisterBankSize 32
#define CACHE_SIZE 64

#include <string>
#include <queue>
#include <filesystem>
#include "PCB.hpp"

using namespace std;

vector<string> read_ROM(string nameFile);
void writeRamToFile(string& instruction, pair<int,pthread_mutex_t>* ram);
vector<string> split(const string& str);
vector<PCB*> getFilaProcessos();
void Success(string print);
void Checkpoint(string print);
void Error(string print);

#endif