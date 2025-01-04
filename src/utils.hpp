#ifndef UTILS
#define UTILS
#define endl '\n'

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> read_ROM(string nameFile);
void writeRamToFile(string& instruction, pair<int,bool>* ram);
vector<string> split(const string& str);

#endif