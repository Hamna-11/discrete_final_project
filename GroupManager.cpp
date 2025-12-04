#include "GroupManager.h"
#include <algorithm>

using namespace std;

vector<vector<long long>> GroupManager::memo;

long long GroupManager::nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    if (r == 0 || r == n) return 1;

    if ((int)memo.size() <= n) {
        memo.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            memo[i].resize(n + 1, -1);
        }
    }

    if (memo[n][r] != -1) return memo[n][r];

    memo[n][r] = nCr(n - 1, r - 1) + nCr(n - 1, r);
    return memo[n][r];
}

long long GroupManager::nPr(int n, int r) {
    if (r > n || r < 0) return 0;
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result *= (n - i);
    }
    return result;
}

void GroupManager::generateCombinations(const vector<string>& elements, int r,
    vector<vector<string>>& result,
    vector<string>& current, int start) {
    if ((int)current.size() == r) {
        result.push_back(current);
        return;
    }

    for (int i = start; i < (int)elements.size(); i++) {
        current.push_back(elements[i]);
        generateCombinations(elements, r, result, current, i + 1);
        current.pop_back();
    }
}

void GroupManager::generatePermutations(vector<string> elements, int start,
    vector<vector<string>>& result) {
    if (start == (int)elements.size()) {
        result.push_back(elements);
        return;
    }

    for (int i = start; i < (int)elements.size(); i++) {
        swap(elements[start], elements[i]);
        generatePermutations(elements, start + 1, result);
        swap(elements[start], elements[i]);
    }
}

vector<vector<string>> GroupManager::assignToGroups(const vector<string>& students,
    int groupSize) {
    vector<vector<string>> groups;
    vector<string> remaining = students;

    while ((int)remaining.size() >= groupSize) {
        vector<string> group;
        for (int i = 0; i < groupSize; i++) {
            group.push_back(remaining[i]);
        }
        groups.push_back(group);
        remaining.erase(remaining.begin(), remaining.begin() + groupSize);
    }

    if (!remaining.empty()) {
        groups.push_back(remaining);
    }

    return groups;
}