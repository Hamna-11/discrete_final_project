#include "LogicEngine.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool LogicEngine::hasFact(const string& fact) const {
    return find(facts.begin(), facts.end(), fact) != facts.end();
}

void LogicEngine::addRule(const string& premise, const string& conclusion) {
    rules.push_back(LogicRule(premise, conclusion));
}

void LogicEngine::addFact(const string& fact) {
    if (!hasFact(fact)) {
        facts.push_back(fact);
    }
}

bool LogicEngine::infer(const string& query) {
    if (hasFact(query)) return true;

    bool changed = true;
    int iterations = 0;
    const int MAX_ITER = 100;

    while (changed && iterations < MAX_ITER) {
        changed = false;
        iterations++;

        for (const auto& rule : rules) {
            if (hasFact(rule.premise) && !hasFact(rule.conclusion)) {
                facts.push_back(rule.conclusion);
                changed = true;
            }
        }
    }

    return hasFact(query);
}

vector<string> LogicEngine::getAllFacts() const {
    return facts;
}

vector<LogicRule> LogicEngine::getRules() const {
    return rules;
}

void LogicEngine::setRules(const vector<LogicRule>& r) {
    rules = r;
}

vector<string> LogicEngine::detectConflicts() {
    vector<string> conflicts;

    for (size_t i = 0; i < facts.size(); i++) {
        for (size_t j = i + 1; j < facts.size(); j++) {
            if (facts[i].find("NOT_") != string::npos) {
                string positive = facts[i].substr(4);
                if (facts[j] == positive) {
                    conflicts.push_back(facts[i] + " conflicts with " + facts[j]);
                }
            }
        }
    }

    return conflicts;
}

bool LogicEngine::isTautology(const string& formula) {
    vector<string> tempFacts = facts;

    facts.clear();
    facts.push_back(formula);
    bool resultTrue = infer(formula);

    facts.clear();
    facts.push_back("NOT_" + formula);
    bool resultFalse = !infer("NOT_" + formula);

    facts = tempFacts;

    return resultTrue && resultFalse;
}

void LogicEngine::display() {
    printHeader("LOGIC & INFERENCE ENGINE");

    cout << "  Rules:\n";
    for (size_t i = 0; i < rules.size(); i++) {
        cout << "  " << (i + 1) << ". ";
        rules[i].display();
    }

    cout << "\n  Facts:\n";
    for (size_t i = 0; i < facts.size(); i++) {
        cout << "  " << (i + 1) << ". " << facts[i] << "\n";
    }

    vector<string> conflicts = detectConflicts();
    if (!conflicts.empty()) {
        cout << "\n  Conflicts Detected:\n";
        for (const auto& c : conflicts) {
            cout << "  ! " << c << "\n";
        }
    }
}

void LogicEngine::addRuleInteractive() {
    printHeader("ADD LOGIC RULE");

    cin.ignore();
    string premise, conclusion;

    cout << "Enter IF condition (premise): ";
    getline(cin, premise);

    cout << "Enter THEN result (conclusion): ";
    getline(cin, conclusion);

    addRule(premise, conclusion);
    printSuccess("Rule added: IF " + premise + " THEN " + conclusion);
}

void LogicEngine::addFactInteractive() {
    printHeader("ADD FACT");

    cin.ignore();
    string fact;

    cout << "Enter fact: ";
    getline(cin, fact);

    addFact(fact);
    printSuccess("Fact added: " + fact);
}

void LogicEngine::performInference() {
    printHeader("PERFORM INFERENCE");

    cin.ignore();
    string query;

    cout << "Enter query to verify: ";
    getline(cin, query);

    bool result = infer(query);

    cout << "\n  Query: " << query << "\n";
    cout << "  Result: " << (result ? "TRUE" : "FALSE") << "\n\n";

    if (result) {
        printSuccess("Query can be inferred from facts and rules!");
    }
    else {
        printError("Query cannot be inferred from current knowledge.");
    }
}

void LogicEngine::checkTautology() {
    printHeader("TAUTOLOGY CHECKER");

    cin.ignore();
    string formula;

    cout << "Enter formula to check: ";
    getline(cin, formula);

    bool result = isTautology(formula);

    cout << "\n  Formula: " << formula << "\n";
    cout << "  Is Tautology: " << (result ? "YES" : "NO") << "\n\n";

    if (result) {
        printSuccess("Formula is a tautology!");
    }
    else {
        printInfo("Formula is not a tautology.");
    }
}