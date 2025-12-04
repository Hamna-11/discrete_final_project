#include "Models.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// Course implementation
Course::Course() : code(""), name(""), credits(3), faculty(""), room(""), capacity(40) {}

Course::Course(string c, string n, int cr)
    : code(c), name(n), credits(cr), faculty(""), room(""), capacity(40) {
}

void Course::display() const {
    cout << "  Course: " << code << " - " << name << "\n";
    cout << "  Credits: " << credits << " | Faculty: "
        << (faculty.empty() ? "Unassigned" : faculty) << " | Room: "
        << (room.empty() ? "Unassigned" : room) << " | Capacity: " << capacity << "\n";
    if (!prerequisites.empty()) {
        cout << "  Prerequisites: ";
        for (size_t i = 0; i < prerequisites.size(); i++) {
            cout << prerequisites[i];
            if (i < prerequisites.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
}

string Course::toFileString() const {
    stringstream ss;
    ss << code << "|" << name << "|" << credits << "|";
    for (size_t i = 0; i < prerequisites.size(); i++) {
        ss << prerequisites[i];
        if (i < prerequisites.size() - 1) ss << ",";
    }
    ss << "|" << faculty << "|" << room << "|" << capacity;
    return ss.str();
}

Course Course::fromFileString(const string& str) {
    vector<string> parts = split(str, '|');
    Course c;
    if (parts.size() >= 7) {
        c.code = parts[0];
        c.name = parts[1];
        c.credits = stoi(parts[2]);
        if (!parts[3].empty()) {
            c.prerequisites = split(parts[3], ',');
        }
        c.faculty = parts[4];
        c.room = parts[5];
        c.capacity = stoi(parts[6]);
    }
    return c;
}

// Student implementation
Student::Student() : id(""), name(""), semester(1) {}

Student::Student(string i, string n, int sem)
    : id(i), name(n), semester(sem) {
}

bool Student::hasCompleted(const string& courseCode) const {
    return find(completedCourses.begin(), completedCourses.end(), courseCode)
        != completedCourses.end();
}

bool Student::isEnrolled(const string& courseCode) const {
    return find(enrolledCourses.begin(), enrolledCourses.end(), courseCode)
        != enrolledCourses.end();
}

void Student::display() const {
    cout << "  Student: " << id << " - " << name << " (Semester " << semester << ")\n";
    if (!completedCourses.empty()) {
        cout << "  Completed: ";
        for (size_t i = 0; i < completedCourses.size(); i++) {
            cout << completedCourses[i];
            if (i < completedCourses.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
    if (!enrolledCourses.empty()) {
        cout << "  Enrolled: ";
        for (size_t i = 0; i < enrolledCourses.size(); i++) {
            cout << enrolledCourses[i];
            if (i < enrolledCourses.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
}

string Student::toFileString() const {
    stringstream ss;
    ss << id << "|" << name << "|" << semester << "|";
    for (size_t i = 0; i < completedCourses.size(); i++) {
        ss << completedCourses[i];
        if (i < completedCourses.size() - 1) ss << ",";
    }
    ss << "|";
    for (size_t i = 0; i < enrolledCourses.size(); i++) {
        ss << enrolledCourses[i];
        if (i < enrolledCourses.size() - 1) ss << ",";
    }
    return ss.str();
}

Student Student::fromFileString(const string& str) {
    vector<string> parts = split(str, '|');
    Student s;
    if (parts.size() >= 5) {
        s.id = parts[0];
        s.name = parts[1];
        s.semester = stoi(parts[2]);
        if (!parts[3].empty()) {
            s.completedCourses = split(parts[3], ',');
        }
        if (!parts[4].empty()) {
            s.enrolledCourses = split(parts[4], ',');
        }
    }
    return s;
}

// Faculty implementation
Faculty::Faculty() : id(""), name(""), maxLoad(4) {}

Faculty::Faculty(string i, string n, int ml)
    : id(i), name(n), maxLoad(ml) {
}

bool Faculty::canAssign() const {
    return (int)assignedCourses.size() < maxLoad;
}

void Faculty::display() const {
    cout << "  Faculty: " << id << " - " << name << " (Load: "
        << assignedCourses.size() << "/" << maxLoad << ")\n";
    if (!assignedCourses.empty()) {
        cout << "  Teaching: ";
        for (size_t i = 0; i < assignedCourses.size(); i++) {
            cout << assignedCourses[i];
            if (i < assignedCourses.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
}

string Faculty::toFileString() const {
    stringstream ss;
    ss << id << "|" << name << "|" << maxLoad << "|";
    for (size_t i = 0; i < assignedCourses.size(); i++) {
        ss << assignedCourses[i];
        if (i < assignedCourses.size() - 1) ss << ",";
    }
    return ss.str();
}

Faculty Faculty::fromFileString(const string& str) {
    vector<string> parts = split(str, '|');
    Faculty f;
    if (parts.size() >= 4) {
        f.id = parts[0];
        f.name = parts[1];
        f.maxLoad = stoi(parts[2]);
        if (!parts[3].empty()) {
            f.assignedCourses = split(parts[3], ',');
        }
    }
    return f;
}

// Room implementation
Room::Room() : id(""), capacity(40), isLab(false) {}

Room::Room(string i, int cap, bool lab)
    : id(i), capacity(cap), isLab(lab) {
}

void Room::display() const {
    cout << "  Room: " << id << " (Capacity: " << capacity << ", "
        << (isLab ? "Lab" : "Lecture Hall") << ")\n";
    if (!assignedCourses.empty()) {
        cout << "  Assigned to: ";
        for (size_t i = 0; i < assignedCourses.size(); i++) {
            cout << assignedCourses[i];
            if (i < assignedCourses.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
}

string Room::toFileString() const {
    stringstream ss;
    ss << id << "|" << capacity << "|" << (isLab ? "1" : "0") << "|";
    for (size_t i = 0; i < assignedCourses.size(); i++) {
        ss << assignedCourses[i];
        if (i < assignedCourses.size() - 1) ss << ",";
    }
    return ss.str();
}

Room Room::fromFileString(const string& str) {
    vector<string> parts = split(str, '|');
    Room r;
    if (parts.size() >= 4) {
        r.id = parts[0];
        r.capacity = stoi(parts[1]);
        r.isLab = (parts[2] == "1");
        if (!parts[3].empty()) {
            r.assignedCourses = split(parts[3], ',');
        }
    }
    return r;
}

// LogicRule implementation
LogicRule::LogicRule() : premise(""), conclusion("") {}

LogicRule::LogicRule(string p, string c) : premise(p), conclusion(c) {}

void LogicRule::display() const {
    cout << "  IF " << premise << " THEN " << conclusion << "\n";
}

string LogicRule::toFileString() const {
    return premise + "|" + conclusion;
}

LogicRule LogicRule::fromFileString(const string& str) {
    vector<string> parts = split(str, '|');
    LogicRule r;
    if (parts.size() >= 2) {
        r.premise = parts[0];
        r.conclusion = parts[1];
    }
    return r;
}