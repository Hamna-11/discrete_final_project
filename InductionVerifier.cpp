#include "InductionVerifier.h"
#include "Utils.h"
#include <iostream>

using namespace std;

InductionVerifier::InductionVerifier(vector<Course>& c) : courses(c) {}

Course* InductionVerifier::findCourse(const string& code) {
    for (auto& c : courses) {
        if (c.code == code) return &c;
    }
    return nullptr;
}

bool InductionVerifier::verifyChainRecursive(const string& courseCode,
    const vector<string>& completed,
    vector<bool>& visited,
    int courseIdx) {
    if (visited[courseIdx]) return true;
    visited[courseIdx] = true;

    Course* course = findCourse(courseCode);
    if (!course) return false;

    if (course->prerequisites.empty()) return true;

    for (const auto& prereq : course->prerequisites) {
        bool isCompleted = false;
        for (const auto& comp : completed) {
            if (comp == prereq) {
                isCompleted = true;
                break;
            }
        }

        if (!isCompleted) return false;

        int prereqIdx = -1;
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i].code == prereq) {
                prereqIdx = i;
                break;
            }
        }

        if (prereqIdx != -1 && !visited[prereqIdx]) {
            if (!verifyChainRecursive(prereq, completed, visited, prereqIdx)) {
                return false;
            }
        }
    }

    return true;
}

bool InductionVerifier::verifyPrerequisiteChain(const string& targetCourse,
    const vector<string>& completedCourses) {
    int targetIdx = -1;
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i].code == targetCourse) {
            targetIdx = i;
            break;
        }
    }

    if (targetIdx == -1) return false;

    vector<bool> visited(courses.size(), false);
    return verifyChainRecursive(targetCourse, completedCourses, visited, targetIdx);
}

vector<string> InductionVerifier::getAllPrerequisites(const string& courseCode) {
    vector<string> allPrereqs;
    vector<string> toProcess = { courseCode };
    vector<string> processed;

    int front = 0;
    while (front < (int)toProcess.size()) {
        string curr = toProcess[front++];

        bool alreadyProcessed = false;
        for (const auto& p : processed) {
            if (p == curr) {
                alreadyProcessed = true;
                break;
            }
        }
        if (alreadyProcessed) continue;

        processed.push_back(curr);

        Course* course = findCourse(curr);
        if (!course) continue;

        for (const auto& prereq : course->prerequisites) {
            bool exists = false;
            for (const auto& ap : allPrereqs) {
                if (ap == prereq) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                allPrereqs.push_back(prereq);
                toProcess.push_back(prereq);
            }
        }
    }

    return allPrereqs;
}

void InductionVerifier::verifyStudentEnrollment(const vector<Student>& students) {
    printHeader("PREREQUISITE VERIFICATION (Mathematical Induction)");

    cin.ignore();
    cout << "Enter Student ID to verify: ";
    string studentId;
    getline(cin, studentId);

    Student* student = nullptr;
    for (const auto& s : students) {
        if (s.id == studentId) {
            student = const_cast<Student*>(&s);
            break;
        }
    }

    if (!student) {
        printError("Student not found!");
        return;
    }

    cout << "Enter Course Code to check enrollment eligibility: ";
    string courseCode;
    getline(cin, courseCode);

    cout << "\n  Target Course: " << courseCode << "\n\n";

    vector<string> allPrereqs = getAllPrerequisites(courseCode);

    if (allPrereqs.empty()) {
        printSuccess("No prerequisites required for " + courseCode);
        return;
    }

    cout << "  All Prerequisites (Direct + Indirect):\n";
    for (const auto& prereq : allPrereqs) {
        cout << "    - " << prereq << "\n";
    }

    cout << "\n  Verification:\n";

    bool allMet = true;
    for (const auto& prereq : allPrereqs) {
        bool met = student->hasCompleted(prereq);

        if (met) {
            cout << "    [OK] " << prereq << " - Completed\n";
        }
        else {
            cout << "    [X] " << prereq << " - NOT Completed\n";
            allMet = false;
        }
    }

    cout << "\n";
    if (allMet) {
        printSuccess("All prerequisites satisfied! Student can enroll in " + courseCode);
    }
    else {
        printError("Prerequisites NOT satisfied! Enrollment in " + courseCode + " denied.");
    }
}