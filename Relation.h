#ifndef RELATION_H
#define RELATION_H

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

template<typename T>
class Relation {
private:
    vector<vector<bool>> matrix;
    vector<T> domain;

    int getIndex(const T& elem) const {
        for (size_t i = 0; i < domain.size(); i++) {
            if (domain[i] == elem) return i;
        }
        return -1;
    }

public:
    Relation() {}

    void addElement(const T& elem) {
        if (getIndex(elem) == -1) {
            domain.push_back(elem);
            int n = domain.size();
            matrix.resize(n);
            for (int i = 0; i < n; i++) {
                matrix[i].resize(n, false);
            }
        }
    }

    void addRelation(const T& from, const T& to) {
        addElement(from);
        addElement(to);
        int i = getIndex(from);
        int j = getIndex(to);
        if (i != -1 && j != -1) {
            matrix[i][j] = true;
        }
    }

    bool hasRelation(const T& from, const T& to) const {
        int i = getIndex(from);
        int j = getIndex(to);
        if (i == -1 || j == -1) return false;
        return matrix[i][j];
    }

    bool isReflexive() const {
        for (size_t i = 0; i < domain.size(); i++) {
            if (!matrix[i][i]) return false;
        }
        return true;
    }

    bool isSymmetric() const {
        for (size_t i = 0; i < domain.size(); i++) {
            for (size_t j = 0; j < domain.size(); j++) {
                if (matrix[i][j] != matrix[j][i]) return false;
            }
        }
        return true;
    }

    bool isTransitive() const {
        for (size_t i = 0; i < domain.size(); i++) {
            for (size_t j = 0; j < domain.size(); j++) {
                if (matrix[i][j]) {
                    for (size_t k = 0; k < domain.size(); k++) {
                        if (matrix[j][k] && !matrix[i][k]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    bool isEquivalence() const {
        return isReflexive() && isSymmetric() && isTransitive();
    }

    bool isPartialOrder() const {
        return isReflexive() && isTransitive() && isAntisymmetric();
    }

    bool isAntisymmetric() const {
        for (size_t i = 0; i < domain.size(); i++) {
            for (size_t j = 0; j < domain.size(); j++) {
                if (i != j && matrix[i][j] && matrix[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    Relation<T> compose(const Relation<T>& other) const {
        Relation<T> result;
        for (const auto& elem : domain) {
            result.addElement(elem);
        }
        for (const auto& elem : other.domain) {
            result.addElement(elem);
        }

        for (size_t i = 0; i < domain.size(); i++) {
            for (size_t j = 0; j < domain.size(); j++) {
                if (matrix[i][j]) {
                    for (size_t k = 0; k < domain.size(); k++) {
                        if (other.hasRelation(domain[j], domain[k])) {
                            result.addRelation(domain[i], domain[k]);
                        }
                    }
                }
            }
        }

        return result;
    }

    void displayMatrix() const {
        cout << "\n  Relation Matrix:\n";
        cout << "     ";
        for (const auto& elem : domain) {
            cout << setw(8) << elem;
        }
        cout << "\n";

        for (size_t i = 0; i < domain.size(); i++) {
            cout << setw(6) << domain[i];
            for (size_t j = 0; j < domain.size(); j++) {
                cout << setw(8) << (matrix[i][j] ? "1" : "0");
            }
            cout << "\n";
        }
    }

    vector<T> getDomain() const {
        return domain;
    }
};

#endif#pragma once
#pragma once
