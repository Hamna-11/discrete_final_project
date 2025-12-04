#include "MHMUniversitySystem.h"
#include "Utils.h"
#include "CourseScheduler.h"
#include "InductionVerifier.h"
#include "ConsistencyChecker.h"
#include "Managers.h"
#include "Modules.h"
#include <iostream>
#include <cstdlib>

using namespace std;

MHMUniversitySystem::MHMUniversitySystem() {
    loadAllData();
}

MHMUniversitySystem::~MHMUniversitySystem() {
    saveAllData();
}

void MHMUniversitySystem::loadAllData() {
    courses = fileManager.loadCourses();
    students = fileManager.loadStudents();
    faculty = fileManager.loadFaculty();
    rooms = fileManager.loadRooms();
    logicRules = fileManager.loadLogicRules();
    logicEngine.setRules(logicRules);
}

void MHMUniversitySystem::saveAllData() {
    fileManager.saveAll(courses, students, faculty, rooms, logicEngine.getRules());
}

void MHMUniversitySystem::showMainMenu() {
    cout << "\n=============================================================\n";
    cout << "          MHM UNIVERSITY MANAGEMENT SYSTEM\n";
    cout << "       Discrete Mathematics Implementation\n";
    cout << "=============================================================\n\n";

    cout << "  DATA MANAGEMENT:\n";
    cout << "  1.  Add Course\n";
    cout << "  2.  Add Student\n";
    cout << "  3.  Add Faculty\n";
    cout << "  4.  Add Room\n";
    cout << "  5.  View All Data\n\n";

    cout << "  DISCRETE MATH MODULES:\n";
    cout << "  6.  Course Scheduling (Topological Sort)\n";
    cout << "  7.  Course Scheduling (Iterative DP)\n";
    cout << "  8.  Student Group Combinations\n";
    cout << "  9.  Prerequisite Verification (Induction)\n";
    cout << "  10. Logic & Inference Engine\n";
    cout << "  11. Set Operations\n";
    cout << "  12. Relations Analysis\n";
    cout << "  13. Functions Analysis\n";
    cout << "  14. Automated Proof Generator\n";
    cout << "  15. Consistency Checker\n";
    cout << "  16. Benchmarking Module\n";
    cout << "  17. Unit Testing Framework\n\n";

    cout << "  OPERATIONS:\n";
    cout << "  18. Enroll Student in Course\n";
    cout << "  19. Mark Course as Completed\n";
    cout << "  20. Assign Course to Faculty\n";
    cout << "  21. Assign Course to Room\n\n";

    cout << "  SYSTEM:\n";
    cout << "  22. Save All Data\n";
    cout << "  23. Load All Data\n";
    cout << "  0.  Exit\n";

    cout << "\n  Enter your choice: ";
}

void MHMUniversitySystem::run() {
    int choice;

    while (true) {
        system("clear || cls");
        showMainMenu();
        cin >> choice;

        if (choice == 0) {
            printHeader("THANK YOU!");
            saveAllData();
            cout << "\n  All data saved successfully!\n";
            cout << "  MHM University Management System\n";
            cout << "  Discrete Mathematics Project\n\n";
            break;
        }

        system("clear || cls");

        switch (choice) {
        case 1: {
            CourseScheduler scheduler(courses);
            scheduler.addCourseInteractive();
            break;
        }
        case 2: {
            StudentManager studentMgr(students);
            studentMgr.addStudentInteractive();
            break;
        }
        case 3: {
            FacultyManager facultyMgr(faculty);
            facultyMgr.addFacultyInteractive();
            break;
        }
        case 4: {
            RoomManager roomMgr(rooms);
            roomMgr.addRoomInteractive();
            break;
        }
        case 5: {
            printHeader("ALL SYSTEM DATA");

            cout << "\nCOURSES (" << courses.size() << "):\n";
            printSeparator();
            for (const auto& c : courses) {
                c.display();
                cout << "\n";
            }

            cout << "\nSTUDENTS (" << students.size() << "):\n";
            printSeparator();
            for (const auto& s : students) {
                s.display();
                cout << "\n";
            }

            cout << "\nFACULTY (" << faculty.size() << "):\n";
            printSeparator();
            for (const auto& f : faculty) {
                f.display();
                cout << "\n";
            }

            cout << "\nROOMS (" << rooms.size() << "):\n";
            printSeparator();
            for (const auto& r : rooms) {
                r.display();
                cout << "\n";
            }
            break;
        }
        case 6: {
            CourseScheduler scheduler(courses);
            scheduler.displaySchedule();
            break;
        }
        case 7: {
            CourseScheduler scheduler(courses);
            scheduler.displayScheduleIterativeDP();
            break;
        }
        case 8: {
            GroupCombinationModule::performGroupOperations(students);
            break;
        }
        case 9: {
            InductionVerifier verifier(courses);
            verifier.verifyStudentEnrollment(students);
            break;
        }
        case 10: {
            cout << "1. Add Logic Rule\n";
            cout << "2. Add Fact\n";
            cout << "3. Perform Inference\n";
            cout << "4. Check Tautology\n";
            cout << "5. Display All Rules & Facts\n";
            cout << "Enter choice: ";
            int logicChoice;
            cin >> logicChoice;

            switch (logicChoice) {
            case 1: logicEngine.addRuleInteractive(); break;
            case 2: logicEngine.addFactInteractive(); break;
            case 3: logicEngine.performInference(); break;
            case 4: logicEngine.checkTautology(); break;
            case 5: logicEngine.display(); break;
            }
            break;
        }
        case 11: {
            SetOperationsModule::performSetOperationsInteractive(students);
            break;
        }
        case 12: {
            RelationModule::performRelationAnalysis(students, courses);
            break;
        }
        case 13: {
            FunctionModule::performFunctionAnalysis(courses, faculty);
            break;
        }
        case 14: {
            proofGen.proveSetEqualityInteractive(students);
            break;
        }
        case 15: {
            ConsistencyChecker checker(students, courses, faculty, rooms);
            checker.displayReport();
            break;
        }
        case 16: {
            BenchmarkModule::runBenchmarks();
            break;
        }
        case 17: {
            UnitTestModule tester;
            tester.runAllTests();
            break;
        }
        case 18: {
            StudentManager studentMgr(students);
            studentMgr.enrollStudentInCourse();
            break;
        }
        case 19: {
            StudentManager studentMgr(students);
            studentMgr.markCourseCompleted();
            break;
        }
        case 20: {
            FacultyManager facultyMgr(faculty);
            facultyMgr.assignCourseToFaculty(courses);
            break;
        }
        case 21: {
            RoomManager roomMgr(rooms);
            roomMgr.assignCourseToRoom(courses);
            break;
        }
        case 22: {
            saveAllData();
            break;
        }
        case 23: {
            loadAllData();
            break;
        }
        default:
            printError("Invalid choice! Please try again.");
        }

        pause();
    }
}