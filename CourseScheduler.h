#ifndef COURSESCHEDULER_H
#define COURSESCHEDULER_H

#include "Models.h"
#include <vector>

using namespace std;

class CourseScheduler {
private:
    vector<Course>& courses;

    vector<vector<int>> buildPrereqGraph();
    bool hasCycleDFS(int node, vector<int>& color, const vector<vector<int>>& adj);

public:
    CourseScheduler(vector<Course>& c);
    bool hasCyclicPrerequisites();
    vector<string> topologicalSort();
    vector<string> topologicalSortIterativeDP();
    void displaySchedule();
    void displayScheduleIterativeDP();
    void addCourseInteractive();
};

#endif#pragma once
