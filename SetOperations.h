#ifndef SETOPERATIONS_H
#define SETOPERATIONS_H

#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class SetOperations {
public:
    static vector<T> setUnion(const vector<T>& a, const vector<T>& b) {
        vector<T> result = a;
        for (const auto& elem : b) {
            if (find(result.begin(), result.end(), elem) == result.end()) {
                result.push_back(elem);
            }
        }
        return result;
    }

    static vector<T> setIntersection(const vector<T>& a, const vector<T>& b) {
        vector<T> result;
        for (const auto& elem : a) {
            if (find(b.begin(), b.end(), elem) != b.end()) {
                result.push_back(elem);
            }
        }
        return result;
    }

    static vector<T> setDifference(const vector<T>& a, const vector<T>& b) {
        vector<T> result;
        for (const auto& elem : a) {
            if (find(b.begin(), b.end(), elem) == b.end()) {
                result.push_back(elem);
            }
        }
        return result;
    }

    static bool isSubset(const vector<T>& a, const vector<T>& b) {
        for (const auto& elem : a) {
            if (find(b.begin(), b.end(), elem) == b.end()) {
                return false;
            }
        }
        return true;
    }

    static vector<vector<T>> powerSet(const vector<T>& s) {
        vector<vector<T>> result;
        int n = s.size();
        int totalSubsets = (1 << n);

        for (int mask = 0; mask < totalSubsets; mask++) {
            vector<T> subset;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    subset.push_back(s[i]);
                }
            }
            result.push_back(subset);
        }
        return result;
    }

    static vector<vector<T>> cartesianProduct(const vector<T>& a, const vector<T>& b) {
        vector<vector<T>> result;
        for (const auto& elemA : a) {
            for (const auto& elemB : b) {
                vector<T> pair = { elemA, elemB };
                result.push_back(pair);
            }
        }
        return result;
    }
};

#endif#pragma once
#pragma once
