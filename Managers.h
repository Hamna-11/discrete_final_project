#pragma once
#ifndef MANAGERS_H
#define MANAGERS_H

#include <vector>
#include <string>
#include "Models.h"

using namespace std;

class StudentManager {
private:
    vector<Student>& students;

public:
    StudentManager(vector<Student>& s);
    void addStudentInteractive();
    void enrollStudentInCourse();
    void markCourseCompleted();
    void displayAllStudents();
};

class FacultyManager {
private:
    vector<Faculty>& faculty;

public:
    FacultyManager(vector<Faculty>& f);
    void addFacultyInteractive();
    void assignCourseToFaculty(vector<Course>& courses);
    void displayAllFaculty();
};

class RoomManager {
private:
    vector<Room>& rooms;

public:
    RoomManager(vector<Room>& r);
    void addRoomInteractive();
    void assignCourseToRoom(vector<Course>& courses);
    void displayAllRooms();
};

#endif#pragma once
