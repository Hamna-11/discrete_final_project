#include "Modules.h"
#include "Utils.h"
#include "SetOperations.h"
#include "GroupManager.h"
#include "Relation.h"
#include "Function.h"
#include "LogicEngine.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// SetOperationsModule Implementation
void SetOperationsModule::performSetOperationsInteractive(const vector<Student>& students) {
    printHeader("SET OPERATIONS MODULE");

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

    cout << "\n  Set A: {";
    for (size_t i = 0; i < setA.size(); i++) {
        cout << setA[i];
        if (i < setA.size() - 1) cout << ", ";
    }
    cout << "}\n";

    cout << "  Set B: {";
    for (size_t i = 0; i < setB.size(); i++) {
        cout << setB[i];
        if (i < setB.size() - 1) cout << ", ";
    }
    cout << "}\n\n";

    vector<string> unionSet = SetOperations<string>::setUnion(setA, setB);
    cout << "  A union B: {";
    for (size_t i = 0; i < unionSet.size(); i++) {
        cout << unionSet[i];
        if (i < unionSet.size() - 1) cout << ", ";
    }
    cout << "}\n";

    vector<string> intersectionSet = SetOperations<string>::setIntersection(setA, setB);
    cout << "  A intersect B: {";
    for (size_t i = 0; i < intersectionSet.size(); i++) {
        cout << intersectionSet[i];
        if (i < intersectionSet.size() - 1) cout << ", ";
    }
    cout << "}\n";

    vector<string> differenceSet = SetOperations<string>::setDifference(setA, setB);
    cout << "  A - B: {";
    for (size_t i = 0; i < differenceSet.size(); i++) {
        cout << differenceSet[i];
        if (i < differenceSet.size() - 1) cout << ", ";
    }
    cout << "}\n";

    bool isSubset = SetOperations<string>::isSubset(setA, setB);
    cout << "  A subset of B: " << (isSubset ? "Yes" : "No") << "\n";

    if (setA.size() <= 5) {
        vector<vector<string>> pSet = SetOperations<string>::powerSet(setA);
        cout << "\n  Power Set of A (total: " << pSet.size() << " subsets):\n";
        for (size_t i = 0; i < pSet.size() && i < 10; i++) {
            cout << "    {";
            for (size_t j = 0; j < pSet[i].size(); j++) {
                cout << pSet[i][j];
                if (j < pSet[i].size() - 1) cout << ", ";
            }
            cout << "}\n";
        }
        if (pSet.size() > 10) {
            cout << "    ... and " << (pSet.size() - 10) << " more\n";
        }
    }

    cout << "\n";
    printSuccess("Set operations completed!");
}

// GroupCombinationModule Implementation
void GroupCombinationModule::performGroupOperations(const vector<Student>& students) {
    printHeader("STUDENT GROUP COMBINATION MODULE");

    if (students.empty()) {
        printError("No students in system!");
        return;
    }

    vector<string> studentIds;
    for (const auto& s : students) {
        studentIds.push_back(s.id);
    }

    cout << "  Total students: " << studentIds.size() << "\n";
    cout << "  Students: ";
    for (size_t i = 0; i < studentIds.size(); i++) {
        cout << studentIds[i];
        if (i < studentIds.size() - 1) cout << ", ";
    }
    cout << "\n\n";

    cout << "Enter group size: ";
    int groupSize;
    cin >> groupSize;

    if (groupSize > (int)studentIds.size() || groupSize < 1) {
        printError("Invalid group size!");
        return;
    }

    long long totalCombinations = GroupManager::nCr(studentIds.size(), groupSize);
    long long totalPermutations = GroupManager::nPr(studentIds.size(), groupSize);

    cout << "\n  Total possible combinations C(" << studentIds.size()
        << "," << groupSize << "): " << totalCombinations << "\n";
    cout << "  Total possible permutations P(" << studentIds.size()
        << "," << groupSize << "): " << totalPermutations << "\n\n";

    vector<vector<string>> groups;
    vector<string> current;
    GroupManager::generateCombinations(studentIds, groupSize, groups, current, 0);

    cout << "  All Possible Groups (Combinations):\n";
    int displayLimit = min(10, (int)groups.size());
    for (int i = 0; i < displayLimit; i++) {
        cout << "  Group " << (i + 1) << ": {";
        for (size_t j = 0; j < groups[i].size(); j++) {
            cout << groups[i][j];
            if (j < groups[i].size() - 1) cout << ", ";
        }
        cout << "}\n";
    }

    if ((int)groups.size() > displayLimit) {
        cout << "  ... and " << (groups.size() - displayLimit) << " more groups\n";
    }

    cout << "\n  Sequential Assignment (Fixed Groups):\n";
    vector<vector<string>> fixedGroups = GroupManager::assignToGroups(studentIds, groupSize);
    for (size_t i = 0; i < fixedGroups.size(); i++) {
        cout << "  Group " << (i + 1) << ": {";
        for (size_t j = 0; j < fixedGroups[i].size(); j++) {
            cout << fixedGroups[i][j];
            if (j < fixedGroups[i].size() - 1) cout << ", ";
        }
        cout << "}\n";
    }

    printSuccess("Combinations generated successfully!");
}

// RelationModule Implementation
void RelationModule::performRelationAnalysis(const vector<Student>& students,
    const vector<Course>& courses) {
    printHeader("RELATIONS MODULE");

    Relation<string> studentCourseRelation;

    cout << "  Building Student-Course Relation:\n";
    for (const auto& student : students) {
        for (const auto& course : student.enrolledCourses) {
            studentCourseRelation.addRelation(student.id, course);
            cout << "  " << student.id << " -> " << course << "\n";
        }
    }

    studentCourseRelation.displayMatrix();

    cout << "\n  Relation Properties:\n";
    cout << "  Reflexive: " << (studentCourseRelation.isReflexive() ? "Yes" : "No") << "\n";
    cout << "  Symmetric: " << (studentCourseRelation.isSymmetric() ? "Yes" : "No") << "\n";
    cout << "  Transitive: " << (studentCourseRelation.isTransitive() ? "Yes" : "No") << "\n";
    cout << "  Equivalence: " << (studentCourseRelation.isEquivalence() ? "Yes" : "No") << "\n";
    cout << "  Antisymmetric: " << (studentCourseRelation.isAntisymmetric() ? "Yes" : "No") << "\n";
    cout << "  Partial Order: " << (studentCourseRelation.isPartialOrder() ? "Yes" : "No") << "\n";

    cout << "\n  Relation Composition (Indirect Conflict Detection):\n";
    Relation<string> composed = studentCourseRelation.compose(studentCourseRelation);

    vector<string> domain = studentCourseRelation.getDomain();
    bool foundIndirect = false;
    for (size_t i = 0; i < domain.size(); i++) {
        for (size_t j = 0; j < domain.size(); j++) {
            if (i != j && composed.hasRelation(domain[i], domain[j])) {
                cout << "  Indirect path: " << domain[i] << " -> ... -> " << domain[j] << "\n";
                foundIndirect = true;
            }
        }
    }

    if (!foundIndirect) {
        cout << "  No indirect paths found.\n";
    }

    printSuccess("Relation analysis completed!");
}

// FunctionModule Implementation
void FunctionModule::performFunctionAnalysis(const vector<Course>& courses,
    const vector<Faculty>& faculty) {
    printHeader("FUNCTIONS MODULE");

    Function<string, string> courseToFaculty;

    cout << "  Course -> Faculty Mapping:\n";
    for (const auto& fac : faculty) {
        for (const auto& course : fac.assignedCourses) {
            courseToFaculty.addMapping(course, fac.id);
        }
    }

    courseToFaculty.display();

    if (courseToFaculty.isBijective()) {
        cout << "\n  Function is bijective - inverse exists!\n";
        cout << "  Demonstrating inverse function:\n";

        vector<string> domain = courseToFaculty.getDomain();
        vector<string> mapping = courseToFaculty.getMapping();

        Function<string, string> inverse;
        for (size_t i = 0; i < domain.size(); i++) {
            inverse.addMapping(mapping[i], domain[i]);
        }

        cout << "\n  Inverse Function (Faculty -> Course):\n";
        inverse.display();
    }

    printSuccess("Function analysis completed!");
}

// BenchmarkModule Implementation
void BenchmarkModule::runBenchmarks() {
    printHeader("ALGORITHMIC EFFICIENCY BENCHMARKING");

    cout << "  Testing Combination Calculation Performance:\n\n";

    vector<pair<int, int>> testCases = {
        {10, 5}, {15, 7}, {20, 10}, {25, 12}, {30, 15}
    };

    for (const auto& test : testCases) {
        int n = test.first;
        int r = test.second;

        clock_t start = clock();
        long long result = GroupManager::nCr(n, r);
        clock_t end = clock();

        double elapsed = double(end - start) / CLOCKS_PER_SEC * 1000;

        cout << "  C(" << n << "," << r << ") = " << result << "\n";
        cout << "  Time: " << fixed << setprecision(4) << elapsed << " ms\n";
        cout << "  Algorithm: Dynamic Programming with Memoization\n\n";
    }

    cout << "  Testing Set Operations Performance:\n\n";

    vector<string> largeSetA, largeSetB;
    for (int i = 0; i < 100; i++) {
        largeSetA.push_back("S" + to_string(i));
    }
    for (int i = 50; i < 150; i++) {
        largeSetB.push_back("S" + to_string(i));
    }

    clock_t start = clock();
    vector<string> unionResult = SetOperations<string>::setUnion(largeSetA, largeSetB);
    clock_t end = clock();
    double unionTime = double(end - start) / CLOCKS_PER_SEC * 1000;

    start = clock();
    vector<string> intersectResult = SetOperations<string>::setIntersection(largeSetA, largeSetB);
    end = clock();
    double intersectTime = double(end - start) / CLOCKS_PER_SEC * 1000;

    cout << "  Union of sets (100 + 100 elements):\n";
    cout << "  Result size: " << unionResult.size() << "\n";
    cout << "  Time: " << fixed << setprecision(4) << unionTime << " ms\n\n";

    cout << "  Intersection of sets (100 + 100 elements):\n";
    cout << "  Result size: " << intersectResult.size() << "\n";
    cout << "  Time: " << fixed << setprecision(4) << intersectTime << " ms\n\n";

    cout << "  Bitset Optimization Demonstration:\n";
    const int MAX_N = 20;
    vector<bool> bitset(MAX_N, false);

    start = clock();
    for (int mask = 0; mask < (1 << MAX_N); mask++) {
        int count = 0;
        for (int i = 0; i < MAX_N; i++) {
            if (mask & (1 << i)) count++;
        }
    }
    end = clock();
    double bitsetTime = double(end - start) / CLOCKS_PER_SEC * 1000;

    cout << "  Generated " << (1 << MAX_N) << " subsets using bitmasking\n";
    cout << "  Time: " << fixed << setprecision(4) << bitsetTime << " ms\n";
    cout << "  Space complexity: O(1) using bit manipulation\n\n";

    printSuccess("Benchmarking completed!");
}

// UnitTestModule Implementation
void UnitTestModule::assertEqual(bool condition, const string& testName) {
    totalTests++;
    if (condition) {
        passedTests++;
        cout << "  [PASS] " << testName << "\n";
    }
    else {
        cout << "  [FAIL] " << testName << "\n";
    }
}

void UnitTestModule::testSetOperations() {
    vector<string> a = { "A", "B", "C" };
    vector<string> b = { "B", "C", "D" };

    vector<string> unionSet = SetOperations<string>::setUnion(a, b);
    assertEqual(unionSet.size() == 4, "Union size correct");

    vector<string> intersect = SetOperations<string>::setIntersection(a, b);
    assertEqual(intersect.size() == 2, "Intersection size correct");

    vector<string> diff = SetOperations<string>::setDifference(a, b);
    assertEqual(diff.size() == 1, "Difference size correct");

    bool subset = SetOperations<string>::isSubset(a, unionSet);
    assertEqual(subset == true, "Subset check correct");

    vector<string> small = { "X", "Y" };
    vector<vector<string>> pSet = SetOperations<string>::powerSet(small);
    assertEqual(pSet.size() == 4, "Power set size correct (2^n)");
}

void UnitTestModule::testCombinations() {
    long long c_5_2 = GroupManager::nCr(5, 2);
    assertEqual(c_5_2 == 10, "C(5,2) = 10");

    long long c_10_3 = GroupManager::nCr(10, 3);
    assertEqual(c_10_3 == 120, "C(10,3) = 120");

    long long p_5_2 = GroupManager::nPr(5, 2);
    assertEqual(p_5_2 == 20, "P(5,2) = 20");

    long long c_invalid = GroupManager::nCr(3, 5);
    assertEqual(c_invalid == 0, "C(3,5) = 0 (invalid)");
}

void UnitTestModule::testRelations() {
    Relation<int> r;
    r.addRelation(1, 1);
    r.addRelation(2, 2);
    r.addRelation(3, 3);

    assertEqual(r.isReflexive() == true, "Reflexive property detected");

    Relation<int> r2;
    r2.addRelation(1, 2);
    r2.addRelation(2, 1);
    r2.addRelation(1, 1);
    r2.addRelation(2, 2);

    assertEqual(r2.isSymmetric() == true, "Symmetric property detected");

    Relation<int> r3;
    r3.addRelation(1, 2);
    r3.addRelation(2, 3);
    r3.addRelation(1, 3);
    r3.addRelation(1, 1);
    r3.addRelation(2, 2);
    r3.addRelation(3, 3);

    assertEqual(r3.isTransitive() == true, "Transitive property detected");
}

void UnitTestModule::testFunctions() {
    Function<int, int> f;
    f.addMapping(1, 10);
    f.addMapping(2, 20);
    f.addMapping(3, 30);

    assertEqual(f.isInjective() == true, "Injective function detected");

    Function<int, int> f2;
    f2.addMapping(1, 10);
    f2.addMapping(2, 10);

    assertEqual(f2.isInjective() == false, "Non-injective function detected");
}

void UnitTestModule::testLogic() {
    LogicEngine engine;
    engine.addRule("A", "B");
    engine.addRule("B", "C");
    engine.addFact("A");

    bool canInferB = engine.infer("B");
    assertEqual(canInferB == true, "Forward chaining infers B from A");

    bool canInferC = engine.infer("C");
    assertEqual(canInferC == true, "Forward chaining infers C from A->B->C");

    bool canInferD = engine.infer("D");
    assertEqual(canInferD == false, "Cannot infer D (not in knowledge base)");
}

void UnitTestModule::runAllTests() {
    printHeader("UNIT TESTING FRAMEWORK");

    cout << "Running Set Operations Tests:\n";
    testSetOperations();

    cout << "\nRunning Combination Tests:\n";
    testCombinations();

    cout << "\nRunning Relation Tests:\n";
    testRelations();

    cout << "\nRunning Function Tests:\n";
    testFunctions();

    cout << "\nRunning Logic Tests:\n";
    testLogic();

    cout << "\n";
    printSeparator();
    cout << "  Test Summary:\n";
    cout << "  Total Tests: " << totalTests << "\n";
    cout << "  Passed: " << passedTests << "\n";
    cout << "  Failed: " << (totalTests - passedTests) << "\n";
    cout << "  Success Rate: " << fixed << setprecision(2)
        << (100.0 * passedTests / totalTests) << "%\n";
    printSeparator();

    if (passedTests == totalTests) {
        printSuccess("All tests passed!");
    }
    else {
        printError("Some tests failed!");
    }
}