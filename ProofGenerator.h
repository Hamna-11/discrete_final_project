#ifndef PROOFGENERATOR_H
#define PROOFGENERATOR_H

#include <vector>
#include <string>
#include <functional>
#include "Models.h"

using namespace std;

class ProofGenerator {
private:
    vector<string> proofSteps;

public:
    void addStep(const string& step);
    void clear();
    void proveSetEquality(const vector<string>& setA, const vector<string>& setB);
    void proveByInduction(int n, function<long long(int)> formula, const string& formulaStr);
    void display();
    void proveSetEqualityInteractive(const vector<Student>& students);
};

#endif#pragma once
