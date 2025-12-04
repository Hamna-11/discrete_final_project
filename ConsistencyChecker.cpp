#include "ConsistencyChecker.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>

using namespace std;

ConsistencyChecker::ConsistencyChecker(vector<Student>& s, vector<Course>& c,
    vector<Faculty>& f, vector<Room>& r)
    : students(s), courses(c), faculty(f), rooms(r) {
}

vector<string> ConsistencyChecker::checkAll() {
    vector<string> issues;

    for (const auto& student : students) {
        int totalCredits = 0;
        for (const auto& courseCode : student.enrolledCourses) {
            for (const auto& course : courses) {
                if (course.code == courseCode) {
                    totalCredits += course.credits;
                    break;
                }
            }
        }

        if (totalCredits > 18) {
            issues.push_back("Student " + student.id + " is overloaded (" +
                to_string(totalCredits) + " credits)");
        }
    }

    for (const auto& fac : faculty) {
        if ((int)fac.assignedCourses.size() > fac.maxLoad) {
            issues.push_back("Faculty " + fac.id + " exceeds maximum load");
        }
    }

    for (const auto& room : rooms) {
        for (const auto& courseCode : room.assignedCourses) {
            int enrolled = 0;
            for (const auto& student : students) {
                if (find(student.enrolledCourses.begin(),
                    student.enrolledCourses.end(),
                    courseCode) != student.enrolledCourses.end()) {
                    enrolled++;
                }
            }

            if (enrolled > room.capacity) {
                issues.push_back("Room " + room.id + " overcapacity for " +
                    courseCode);
            }
        }
    }

    for (const auto& student : students) {
        for (const auto& enrolled : student.enrolledCourses) {
            for (const auto& course : courses) {
                if (course.code == enrolled) {
                    for (const auto& prereq : course.prerequisites) {
                        bool hasPrereq = find(student.completedCourses.begin(),
                            student.completedCourses.end(),
                            prereq) != student.completedCourses.end();
                        if (!hasPrereq) {
                            issues.push_back("Student " + student.id +
                                " lacks prerequisite " + prereq +
                                " for " + enrolled);
                        }
                    }
                    break;
                }
            }
        }
    }

    for (const auto& course : courses) {
        int facultyCount = 0;
        for (const auto& fac : faculty) {
            if (find(fac.assignedCourses.begin(),
                fac.assignedCourses.end(),
                course.code) != fac.assignedCourses.end()) {
                facultyCount++;
            }
        }

        if (facultyCount > 1) {
            issues.push_back("Course " + course.code +
                " assigned to multiple faculty");
        }
    }

    return issues;
}

void ConsistencyChecker::displayReport() {
    printHeader("CONSISTENCY CHECK REPORT");

    vector<string> issues = checkAll();

    if (issues.empty()) {
        printSuccess("All systems consistent! No issues found.");
    }
    else {
        printError("Found " + to_string(issues.size()) + " issue(s):");
        cout << "\n";
        for (size_t i = 0; i < issues.size(); i++) {
            cout << "  " << (i + 1) << ". " << issues[i] << "\n";
        }
    }
    cout << "\n";
}