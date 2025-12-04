#include "FileManager.h"
#include "Utils.h"
#include <fstream>

using namespace std;

void FileManager::saveCourses(const vector<Course>& courses) {
    ofstream file(coursesFile);
    if (file.is_open()) {
        for (const auto& c : courses) {
            file << c.toFileString() << "\n";
        }
        file.close();
        printSuccess("Courses saved to " + coursesFile);
    }
    else {
        printError("Could not open " + coursesFile);
    }
}

vector<Course> FileManager::loadCourses() {
    vector<Course> courses;
    ifstream file(coursesFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                courses.push_back(Course::fromFileString(line));
            }
        }
        file.close();
        printSuccess("Loaded " + to_string(courses.size()) + " courses from " + coursesFile);
    }
    else {
        printInfo("No existing courses file found. Starting fresh.");
    }
    return courses;
}

void FileManager::saveStudents(const vector<Student>& students) {
    ofstream file(studentsFile);
    if (file.is_open()) {
        for (const auto& s : students) {
            file << s.toFileString() << "\n";
        }
        file.close();
        printSuccess("Students saved to " + studentsFile);
    }
    else {
        printError("Could not open " + studentsFile);
    }
}

vector<Student> FileManager::loadStudents() {
    vector<Student> students;
    ifstream file(studentsFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                students.push_back(Student::fromFileString(line));
            }
        }
        file.close();
        printSuccess("Loaded " + to_string(students.size()) + " students from " + studentsFile);
    }
    else {
        printInfo("No existing students file found. Starting fresh.");
    }
    return students;
}

void FileManager::saveFaculty(const vector<Faculty>& faculty) {
    ofstream file(facultyFile);
    if (file.is_open()) {
        for (const auto& f : faculty) {
            file << f.toFileString() << "\n";
        }
        file.close();
        printSuccess("Faculty saved to " + facultyFile);
    }
    else {
        printError("Could not open " + facultyFile);
    }
}

vector<Faculty> FileManager::loadFaculty() {
    vector<Faculty> faculty;
    ifstream file(facultyFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                faculty.push_back(Faculty::fromFileString(line));
            }
        }
        file.close();
        printSuccess("Loaded " + to_string(faculty.size()) + " faculty from " + facultyFile);
    }
    else {
        printInfo("No existing faculty file found. Starting fresh.");
    }
    return faculty;
}

void FileManager::saveRooms(const vector<Room>& rooms) {
    ofstream file(roomsFile);
    if (file.is_open()) {
        for (const auto& r : rooms) {
            file << r.toFileString() << "\n";
        }
        file.close();
        printSuccess("Rooms saved to " + roomsFile);
    }
    else {
        printError("Could not open " + roomsFile);
    }
}

vector<Room> FileManager::loadRooms() {
    vector<Room> rooms;
    ifstream file(roomsFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                rooms.push_back(Room::fromFileString(line));
            }
        }
        file.close();
        printSuccess("Loaded " + to_string(rooms.size()) + " rooms from " + roomsFile);
    }
    else {
        printInfo("No existing rooms file found. Starting fresh.");
    }
    return rooms;
}

void FileManager::saveLogicRules(const vector<LogicRule>& rules) {
    ofstream file(rulesFile);
    if (file.is_open()) {
        for (const auto& r : rules) {
            file << r.toFileString() << "\n";
        }
        file.close();
        printSuccess("Logic rules saved to " + rulesFile);
    }
    else {
        printError("Could not open " + rulesFile);
    }
}

vector<LogicRule> FileManager::loadLogicRules() {
    vector<LogicRule> rules;
    ifstream file(rulesFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                rules.push_back(LogicRule::fromFileString(line));
            }
        }
        file.close();
        printSuccess("Loaded " + to_string(rules.size()) + " logic rules from " + rulesFile);
    }
    else {
        printInfo("No existing rules file found. Starting fresh.");
    }
    return rules;
}

void FileManager::saveAll(const vector<Course>& courses, const vector<Student>& students,
    const vector<Faculty>& faculty, const vector<Room>& rooms,
    const vector<LogicRule>& rules) {
    printHeader("SAVING ALL DATA");
    saveCourses(courses);
    saveStudents(students);
    saveFaculty(faculty);
    saveRooms(rooms);
    saveLogicRules(rules);
    printSuccess("All data saved successfully!");
}

void FileManager::loadAll(vector<Course>& courses, vector<Student>& students,
    vector<Faculty>& faculty, vector<Room>& rooms,
    vector<LogicRule>& rules) {
    printHeader("LOADING ALL DATA");
    courses = loadCourses();
    students = loadStudents();
    faculty = loadFaculty();
    rooms = loadRooms();
    rules = loadLogicRules();
    printSuccess("All data loaded successfully!");
}