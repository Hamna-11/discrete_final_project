#ifndef INDUCTIONVERIFIER_H
#define INDUCTIONVERIFIER_H

#include <vector>
#include <string>
#include "Models.h"

using namespace std;

class InductionVerifier {
private:
    vector<Course>& courses;

    Course* findCourse(const string& code);
    bool verifyChainRecursive(const string& courseCode,
        const vector<string>& completed,
        vector<bool>& visited,
        int courseIdx);

public:
    InductionVerifier(vector<Course>& c);
    bool verifyPrerequisiteChain(const string& targetCourse,
        const vector<string>& completedCourses);
    vector<string> getAllPrerequisites(const string& courseCode);
    void verifyStudentEnrollment(const vector<Student>& students);
};

#endif#pragma once
