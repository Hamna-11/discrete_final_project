#ifndef MHMUNIVERSITYSYSTEM_H
#define MHMUNIVERSITYSYSTEM_H

#include <vector>
#include "Models.h"
#include "FileManager.h"
#include "LogicEngine.h"
#include "ProofGenerator.h"

using namespace std;

class MHMUniversitySystem {
private:
    vector<Course> courses;
    vector<Student> students;
    vector<Faculty> faculty;
    vector<Room> rooms;
    vector<LogicRule> logicRules;

    FileManager fileManager;
    LogicEngine logicEngine;
    ProofGenerator proofGen;

    void loadAllData();
    void saveAllData();
    void showMainMenu();

public:
    MHMUniversitySystem();
    ~MHMUniversitySystem();
    void run();
};

#endif#pragma once
