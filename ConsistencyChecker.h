#ifndef CONSISTENCYCHECKER_H
#define CONSISTENCYCHECKER_H

#include <vector>
#include <string>
#include "Models.h"

using namespace std;

class ConsistencyChecker {
private:
    vector<Student>& students;
    vector<Course>& courses;
    vector<Faculty>& faculty;
    vector<Room>& rooms;

public:
    ConsistencyChecker(vector<Student>& s, vector<Course>& c,
        vector<Faculty>& f, vector<Room>& r);
    vector<string> checkAll();
    void displayReport();
};

#endif