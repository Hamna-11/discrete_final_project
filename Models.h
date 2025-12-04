#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <vector>

using namespace std;

struct Course {
    string code;
    string name;
    int credits;
    vector<string> prerequisites;
    string faculty;
    string room;
    int capacity;

    Course();
    Course(string c, string n, int cr = 3);
    void display() const;
    string toFileString() const;
    static Course fromFileString(const string& str);
};

struct Student {
    string id;
    string name;
    vector<string> completedCourses;
    vector<string> enrolledCourses;
    int semester;

    Student();
    Student(string i, string n, int sem = 1);
    bool hasCompleted(const string& courseCode) const;
    bool isEnrolled(const string& courseCode) const;
    void display() const;
    string toFileString() const;
    static Student fromFileString(const string& str);
};

struct Faculty {
    string id;
    string name;
    vector<string> assignedCourses;
    int maxLoad;

    Faculty();
    Faculty(string i, string n, int ml = 4);
    bool canAssign() const;
    void display() const;
    string toFileString() const;
    static Faculty fromFileString(const string& str);
};

struct Room {
    string id;
    int capacity;
    bool isLab;
    vector<string> assignedCourses;

    Room();
    Room(string i, int cap, bool lab = false);
    void display() const;
    string toFileString() const;
    static Room fromFileString(const string& str);
};

struct LogicRule {
    string premise;
    string conclusion;

    LogicRule();
    LogicRule(string p, string c);
    void display() const;
    string toFileString() const;
    static LogicRule fromFileString(const string& str);
};

#endif#pragma once
