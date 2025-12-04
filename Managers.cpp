#include "Managers.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>

using namespace std;

// StudentManager Implementation
StudentManager::StudentManager(vector<Student>& s) : students(s) {}

void StudentManager::addStudentInteractive() {
    printHeader("ADD NEW STUDENT");

    Student s;
    cin.ignore();

    cout << "Enter Student ID: ";
    getline(cin, s.id);

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    cout << "Enter Semester: ";
    cin >> s.semester;
    cin.ignore();

    cout << "Enter Completed Courses (comma-separated, or press Enter for none): ";
    string completedStr;
    getline(cin, completedStr);
    if (!completedStr.empty()) {
        s.completedCourses = split(completedStr, ',');
    }

    cout << "Enter Enrolled Courses (comma-separated, or press Enter for none): ";
    string enrolledStr;
    getline(cin, enrolledStr);
    if (!enrolledStr.empty()) {
        s.enrolledCourses = split(enrolledStr, ',');
    }

    students.push_back(s);
    printSuccess("Student " + s.id + " added successfully!");
}

void StudentManager::enrollStudentInCourse() {
    printHeader("ENROLL STUDENT IN COURSE");

    if (students.empty()) {
        printError("No students in system!");
        return;
    }

    cin.ignore();
    cout << "Enter Student ID: ";
    string studentId;
    getline(cin, studentId);

    Student* student = nullptr;
    for (auto& s : students) {
        if (s.id == studentId) {
            student = &s;
            break;
        }
    }

    if (!student) {
        printError("Student not found!");
        return;
    }

    cout << "Enter Course Code to enroll: ";
    string courseCode;
    getline(cin, courseCode);

    if (student->isEnrolled(courseCode)) {
        printError("Student already enrolled in " + courseCode);
        return;
    }

    student->enrolledCourses.push_back(courseCode);
    printSuccess("Student " + studentId + " enrolled in " + courseCode);
}

void StudentManager::markCourseCompleted() {
    printHeader("MARK COURSE AS COMPLETED");

    if (students.empty()) {
        printError("No students in system!");
        return;
    }

    cin.ignore();
    cout << "Enter Student ID: ";
    string studentId;
    getline(cin, studentId);

    Student* student = nullptr;
    for (auto& s : students) {
        if (s.id == studentId) {
            student = &s;
            break;
        }
    }

    if (!student) {
        printError("Student not found!");
        return;
    }

    cout << "Enter Course Code to mark as completed: ";
    string courseCode;
    getline(cin, courseCode);

    auto it = find(student->enrolledCourses.begin(),
        student->enrolledCourses.end(), courseCode);
    if (it != student->enrolledCourses.end()) {
        student->enrolledCourses.erase(it);
    }

    if (!student->hasCompleted(courseCode)) {
        student->completedCourses.push_back(courseCode);
        printSuccess("Course " + courseCode + " marked as completed for " + studentId);
    }
    else {
        printError("Course already marked as completed!");
    }
}

void StudentManager::displayAllStudents() {
    printHeader("ALL STUDENTS");

    if (students.empty()) {
        printInfo("No students in system.");
        return;
    }

    for (const auto& s : students) {
        s.display();
        cout << "\n";
    }
}

// FacultyManager Implementation
FacultyManager::FacultyManager(vector<Faculty>& f) : faculty(f) {}

void FacultyManager::addFacultyInteractive() {
    printHeader("ADD NEW FACULTY");

    Faculty f;
    cin.ignore();

    cout << "Enter Faculty ID: ";
    getline(cin, f.id);

    cout << "Enter Faculty Name: ";
    getline(cin, f.name);

    cout << "Enter Maximum Course Load: ";
    cin >> f.maxLoad;
    cin.ignore();

    cout << "Enter Assigned Courses (comma-separated, or press Enter for none): ";
    string coursesStr;
    getline(cin, coursesStr);
    if (!coursesStr.empty()) {
        f.assignedCourses = split(coursesStr, ',');
    }

    faculty.push_back(f);
    printSuccess("Faculty " + f.id + " added successfully!");
}

void FacultyManager::assignCourseToFaculty(vector<Course>& courses) {
    printHeader("ASSIGN COURSE TO FACULTY");

    if (faculty.empty()) {
        printError("No faculty in system!");
        return;
    }

    cin.ignore();
    cout << "Enter Faculty ID: ";
    string facultyId;
    getline(cin, facultyId);

    Faculty* fac = nullptr;
    for (auto& f : faculty) {
        if (f.id == facultyId) {
            fac = &f;
            break;
        }
    }

    if (!fac) {
        printError("Faculty not found!");
        return;
    }

    if (!fac->canAssign()) {
        printError("Faculty has reached maximum course load!");
        return;
    }

    cout << "Enter Course Code to assign: ";
    string courseCode;
    getline(cin, courseCode);

    Course* course = nullptr;
    for (auto& c : courses) {
        if (c.code == courseCode) {
            course = &c;
            break;
        }
    }

    if (!course) {
        printError("Course not found!");
        return;
    }

    if (find(fac->assignedCourses.begin(), fac->assignedCourses.end(),
        courseCode) != fac->assignedCourses.end()) {
        printError("Course already assigned to this faculty!");
        return;
    }

    fac->assignedCourses.push_back(courseCode);
    course->faculty = facultyId;

    printSuccess("Course " + courseCode + " assigned to faculty " + facultyId);
}

void FacultyManager::displayAllFaculty() {
    printHeader("ALL FACULTY");

    if (faculty.empty()) {
        printInfo("No faculty in system.");
        return;
    }

    for (const auto& f : faculty) {
        f.display();
        cout << "\n";
    }
}

// RoomManager Implementation
RoomManager::RoomManager(vector<Room>& r) : rooms(r) {}

void RoomManager::addRoomInteractive() {
    printHeader("ADD NEW ROOM");

    Room r;
    cin.ignore();

    cout << "Enter Room ID: ";
    getline(cin, r.id);

    cout << "Enter Room Capacity: ";
    cin >> r.capacity;

    char labChoice;
    cout << "Is this a lab? (y/n): ";
    cin >> labChoice;
    r.isLab = (labChoice == 'y' || labChoice == 'Y');
    cin.ignore();

    cout << "Enter Assigned Courses (comma-separated, or press Enter for none): ";
    string coursesStr;
    getline(cin, coursesStr);
    if (!coursesStr.empty()) {
        r.assignedCourses = split(coursesStr, ',');
    }

    rooms.push_back(r);
    printSuccess("Room " + r.id + " added successfully!");
}

void RoomManager::assignCourseToRoom(vector<Course>& courses) {
    printHeader("ASSIGN COURSE TO ROOM");

    if (rooms.empty()) {
        printError("No rooms in system!");
        return;
    }

    cin.ignore();
    cout << "Enter Room ID: ";
    string roomId;
    getline(cin, roomId);

    Room* room = nullptr;
    for (auto& r : rooms) {
        if (r.id == roomId) {
            room = &r;
            break;
        }
    }

    if (!room) {
        printError("Room not found!");
        return;
    }

    cout << "Enter Course Code to assign: ";
    string courseCode;
    getline(cin, courseCode);

    Course* course = nullptr;
    for (auto& c : courses) {
        if (c.code == courseCode) {
            course = &c;
            break;
        }
    }

    if (!course) {
        printError("Course not found!");
        return;
    }

    if (find(room->assignedCourses.begin(), room->assignedCourses.end(),
        courseCode) != room->assignedCourses.end()) {
        printError("Course already assigned to this room!");
        return;
    }

    room->assignedCourses.push_back(courseCode);
    course->room = roomId;

    printSuccess("Course " + courseCode + " assigned to room " + roomId);
}

void RoomManager::displayAllRooms() {
    printHeader("ALL ROOMS");

    if (rooms.empty()) {
        printInfo("No rooms in system.");
        return;
    }

    for (const auto& r : rooms) {
        r.display();
        cout << "\n";
    }
}