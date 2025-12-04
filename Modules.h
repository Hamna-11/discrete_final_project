#ifndef MODULES_H
#define MODULES_H

#include <vector>
#include <string>
#include "Models.h"

using namespace std;

class SetOperationsModule {
public:
    static void performSetOperationsInteractive(const vector<Student>& students);
};

class GroupCombinationModule {
public:
    static void performGroupOperations(const vector<Student>& students);
};

class RelationModule {
public:
    static void performRelationAnalysis(const vector<Student>& students,
        const vector<Course>& courses);
};

class FunctionModule {
public:
    static void performFunctionAnalysis(const vector<Course>& courses,
        const vector<Faculty>& faculty);
};

class BenchmarkModule {
public:
    static void runBenchmarks();
};

class UnitTestModule {
private:
    int totalTests;
    int passedTests;

    void assertEqual(bool condition, const string& testName);
    void testSetOperations();
    void testCombinations();
    void testRelations();
    void testFunctions();
    void testLogic();

public:
    UnitTestModule() : totalTests(0), passedTests(0) {}
    void runAllTests();
};

#endif#pragma once
