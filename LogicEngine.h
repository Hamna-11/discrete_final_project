#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include <vector>
#include <string>
#include "Models.h"

using namespace std;

class LogicEngine {
private:
    vector<LogicRule> rules;
    vector<string> facts;

    bool hasFact(const string& fact) const;

public:
    void addRule(const string& premise, const string& conclusion);
    void addFact(const string& fact);
    bool infer(const string& query);
    vector<string> getAllFacts() const;
    vector<LogicRule> getRules() const;
    void setRules(const vector<LogicRule>& r);
    vector<string> detectConflicts();
    bool isTautology(const string& formula);
    void display();
    void addRuleInteractive();
    void addFactInteractive();
    void performInference();
    void checkTautology();
};

#endif#pragma once
