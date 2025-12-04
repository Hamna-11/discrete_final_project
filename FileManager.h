#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Models.h"
#include <vector>
#include <string>

using namespace std;

class FileManager {
private:
    string coursesFile = "courses.txt";
    string studentsFile = "students.txt";
    string facultyFile = "faculty.txt";
    string roomsFile = "rooms.txt";
    string rulesFile = "logic_rules.txt";

public:
    void saveCourses(const vector<Course>& courses);
    vector<Course> loadCourses();
    void saveStudents(const vector<Student>& students);
    vector<Student> loadStudents();
    void saveFaculty(const vector<Faculty>& faculty);
    vector<Faculty> loadFaculty();
    void saveRooms(const vector<Room>& rooms);
    vector<Room> loadRooms();
    void saveLogicRules(const vector<LogicRule>& rules);
    vector<LogicRule> loadLogicRules();
    void saveAll(const vector<Course>& courses, const vector<Student>& students,
        const vector<Faculty>& faculty, const vector<Room>& rooms,
        const vector<LogicRule>& rules);
    void loadAll(vector<Course>& courses, vector<Student>& students,
        vector<Faculty>& faculty, vector<Room>& rooms,
        vector<LogicRule>& rules);
};

#endif#pragma once
