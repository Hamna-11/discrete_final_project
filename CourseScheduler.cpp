#include "CourseScheduler.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

CourseScheduler::CourseScheduler(vector<Course>& c) : courses(c) {}

vector<vector<int>> CourseScheduler::buildPrereqGraph() {
    int n = courses.size();
    vector<vector<int>> adjList(n);

    for (int i = 0; i < n; i++) {
        for (const auto& prereq : courses[i].prerequisites) {
            for (int j = 0; j < n; j++) {
                if (courses[j].code == prereq) {
                    adjList[j].push_back(i);
                    break;
                }
            }
        }
    }
    return adjList;
}

bool CourseScheduler::hasCycleDFS(int node, vector<int>& color, const vector<vector<int>>& adj) {
    color[node] = 1; 

    for (int neighbor : adj[node]) {
        if (color[neighbor] == 1) {
            return true;
        }
        if (color[neighbor] == 0 && hasCycleDFS(neighbor, color, adj)) {
            return true;
        }
    }

    color[node] = 2; 
    return false;
}

bool CourseScheduler::hasCyclicPrerequisites() {
    vector<vector<int>> adj = buildPrereqGraph();
    int n = courses.size();
    vector<int> color(n, 0);

    for (int i = 0; i < n; i++) {
        if (color[i] == 0) {
            if (hasCycleDFS(i, color, adj)) {
                return true;
            }
        }
    }
    return false;
}

vector<string> CourseScheduler::topologicalSort() {
    int n = courses.size();
    vector<vector<int>> adj = buildPrereqGraph();
    vector<int> inDegree(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            inDegree[j]++;
        }
    }

    vector<int> q;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push_back(i);
        }
    }

    vector<string> result;
    int front = 0;

    while (front < (int)q.size()) {
        int curr = q[front++];
        result.push_back(courses[curr].code);

        for (int next : adj[curr]) {
            inDegree[next]--;
            if (inDegree[next] == 0) {
                q.push_back(next);
            }
        }
    }

    return result;
}


vector<string> CourseScheduler::topologicalSortIterativeDP() {
    int n = courses.size();
    vector<vector<int>> adj = buildPrereqGraph();
    vector<int> dp(n, -1); 
    vector<string> result;

    for (int i = 0; i < n; i++) {
        if (dp[i] == -1) {
            vector<int> stack;
            stack.push_back(i);

            while (!stack.empty()) {
                int curr = stack.back();

                if (dp[curr] != -1) {
                    stack.pop_back();
                    continue;
                }

                bool allProcessed = true;
                for (int prereq : adj[curr]) {
                    if (dp[prereq] == -1) {
                        stack.push_back(prereq);
                        allProcessed = false;
                    }
                }

                if (allProcessed) {
                    int maxDepth = 0;
                    for (int prereq : adj[curr]) {
                        maxDepth = max(maxDepth, dp[prereq] + 1);
                    }
                    dp[curr] = maxDepth;
                    stack.pop_back();
                }
            }
        }
    }

    vector<pair<int, int>> depthIndex;
    for (int i = 0; i < n; i++) {
        depthIndex.push_back({ dp[i], i });
    }
    sort(depthIndex.begin(), depthIndex.end());

    for (const auto& p : depthIndex) {
        result.push_back(courses[p.second].code);
    }

    return result;
}

void CourseScheduler::displaySchedule() {
    printHeader("VALID COURSE SEQUENCE (Topological Sort)");

    if (hasCyclicPrerequisites()) {
        printError("Cyclic prerequisites detected! Cannot generate valid sequence.");
        return;
    }

    vector<string> sequence = topologicalSort();

    cout << "  Recommended Course Order:\n";
    for (size_t i = 0; i < sequence.size(); i++) {
        cout << "  " << (i + 1) << ". " << sequence[i] << "\n";
    }

    cout << "\n";
    printSuccess("Total courses in sequence: " + to_string(sequence.size()));
}

void CourseScheduler::displayScheduleIterativeDP() {
    printHeader("COURSE SEQUENCE (Iterative DP Method)");

    if (hasCyclicPrerequisites()) {
        printError("Cyclic prerequisites detected! Cannot generate valid sequence.");
        return;
    }

    vector<string> sequence = topologicalSortIterativeDP();

    cout << "  Recommended Course Order (by depth):\n";
    for (size_t i = 0; i < sequence.size(); i++) {
        cout << "  " << (i + 1) << ". " << sequence[i] << "\n";
    }

    cout << "\n";
    printSuccess("Total courses in sequence: " + to_string(sequence.size()));
}

void CourseScheduler::addCourseInteractive() {
    printHeader("ADD NEW COURSE");

    Course c;
    cin.ignore();

    cout << "Enter Course Code: ";
    getline(cin, c.code);

    cout << "Enter Course Name: ";
    getline(cin, c.name);

    cout << "Enter Credits: ";
    cin >> c.credits;

    cout << "Enter Capacity: ";
    cin >> c.capacity;
    cin.ignore();

    cout << "Enter Prerequisites (comma-separated, or press Enter for none): ";
    string prereqStr;
    getline(cin, prereqStr);
    if (!prereqStr.empty()) {
        c.prerequisites = split(prereqStr, ',');
    }

    cout << "Enter Faculty ID (or press Enter to skip): ";
    getline(cin, c.faculty);

    cout << "Enter Room ID (or press Enter to skip): ";
    getline(cin, c.room);

    courses.push_back(c);
    printSuccess("Course " + c.code + " added successfully!");
}