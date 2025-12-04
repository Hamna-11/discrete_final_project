#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

void printHeader(const string& title);
void printSeparator();
void printSuccess(const string& msg);
void printError(const string& msg);
void printInfo(const string& msg);
void pause();
string trim(const string& str);
vector<string> split(const string& str, char delimiter);

#endif
