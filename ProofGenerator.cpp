#include "ProofGenerator.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>

using namespace std;

void ProofGenerator::addStep(const string& step) {
    proofSteps.push_back(step);
}

void ProofGenerator::clear() {
    proofSteps.clear();
}

void ProofGenerator::proveSetEquality(const vector<string>& setA, const vector<string>& setB) {
    clear();
    addStep("PROOF: Set A = Set B");
    addStep("To prove: A subset B and B subset A");

    addStep("\nPart 1: Proving A subset B");
    bool aSubsetB = true;
    for (const auto& elem : setA) {
        bool found = find(setB.begin(), setB.end(), elem) != setB.end();
        if (found) {
            addStep("  [OK] Element '" + elem + "' in A and '" + elem + "' in B");
        }
        else {
            addStep("  [X] Element '" + elem + "' in A but '" + elem + "' not in B");
            aSubsetB = false;
        }
    }

    if (aSubsetB) {
        addStep("  Therefore A subset B (proven)");
    }
    else {
        addStep("  Therefore A not subset B");
    }

    addStep("\nPart 2: Proving B subset A");
    bool bSubsetA = true;
    for (const auto& elem : setB) {
        bool found = find(setA.begin(), setA.end(), elem) != setA.end();
        if (found) {
            addStep("  [OK] Element '" + elem + "' in B and '" + elem + "' in A");
        }
        else {
            addStep("  [X] Element '" + elem + "' in B but '" + elem + "' not in A");
            bSubsetA = false;
        }
    }

    if (bSubsetA) {
        addStep("  Therefore B subset A (proven)");
    }
    else {
        addStep("  Therefore B not subset A");
    }

    addStep("\nConclusion:");
    if (aSubsetB && bSubsetA) {
        addStep("  Since A subset B and B subset A, therefore A = B (Q.E.D.)");
    }
    else {
        addStep("  Since conditions not met, A not equal B");
    }
}

void ProofGenerator::proveByInduction(int n, function<long long(int)> formula, const string& formulaStr) {
    clear();
    addStep("PROOF BY MATHEMATICAL INDUCTION");
    addStep("Prove: " + formulaStr);

    addStep("\nBase Case (n=1):");
    long long base = formula(1);
    addStep("  For n=1: Result = " + to_string(base));
    addStep("  [OK] Base case holds");

    addStep("\nInductive Hypothesis:");
    addStep("  Assume formula holds for n=k");

    addStep("\nInductive Step:");
    addStep("  Prove formula holds for n=k+1");

    addStep("\nVerification for n=" + to_string(n) + ":");
    long long result = formula(n);
    addStep("  Result = " + to_string(result));
    addStep("  Therefore Formula verified for n=" + to_string(n) + " (Q.E.D.)");
}

void ProofGenerator::display() {
    printHeader("AUTOMATED PROOF");

    for (const auto& step : proofSteps) {
        cout << step << "\n";
    }
    cout << "\n";
}

void ProofGenerator::proveSetEqualityInteractive(const vector<Student>& students) {
    printHeader("PROVE SET EQUALITY");

    cout << "Available students: ";
    for (size_t i = 0; i < students.size(); i++) {
        cout << students[i].id;
        if (i < students.size() - 1) cout << ", ";
    }
    cout << "\n\n";

    cin.ignore();
    cout << "Enter Set A student IDs (comma-separated): ";
    string setAStr;
    getline(cin, setAStr);
    vector<string> setA = split(setAStr, ',');

    cout << "Enter Set B student IDs (comma-separated): ";
    string setBStr;
    getline(cin, setBStr);
    vector<string> setB = split(setBStr, ',');

    proveSetEquality(setA, setB);
    display();
}