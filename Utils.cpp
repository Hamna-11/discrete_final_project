#include "Utils.h"
#include <iostream>
#include <sstream>

using namespace std;

void printHeader(const string& title) {
    cout << "\n=============================================================\n";
    cout << "  " << title << "\n";
    cout << "=============================================================\n\n";
}

void printSeparator() {
    cout << "-------------------------------------------------------------\n";
}

void printSuccess(const string& msg) {
    cout << "[SUCCESS] " << msg << "\n";
}

void printError(const string& msg) {
    cout << "[ERROR] " << msg << "\n";
}

void printInfo(const string& msg) {
    cout << "[INFO] " << msg << "\n";
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        token = trim(token);
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}