#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include <vector>
#include <string>

using namespace std;

class GroupManager {
private:
    static vector<vector<long long>> memo;

public:
    static long long nCr(int n, int r);
    static long long nPr(int n, int r);
    static void generateCombinations(const vector<string>& elements, int r,
        vector<vector<string>>& result,
        vector<string>& current, int start);
    static void generatePermutations(vector<string> elements, int start,
        vector<vector<string>>& result);
    static vector<vector<string>> assignToGroups(const vector<string>& students,
        int groupSize);
};

#endif#pragma once
