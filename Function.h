#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

template<typename T, typename U>
class Function {
private:
    vector<T> domain;
    vector<U> codomain;
    vector<U> mapping;

    int getDomainIndex(const T& elem) const {
        for (size_t i = 0; i < domain.size(); i++) {
            if (domain[i] == elem) return i;
        }
        return -1;
    }

public:
    void addMapping(const T& from, const U& to) {
        int idx = getDomainIndex(from);
        if (idx == -1) {
            domain.push_back(from);
            mapping.push_back(to);
        }
        else {
            mapping[idx] = to;
        }

        if (find(codomain.begin(), codomain.end(), to) == codomain.end()) {
            codomain.push_back(to);
        }
    }

    U apply(const T& elem) const {
        int idx = getDomainIndex(elem);
        if (idx != -1) {
            return mapping[idx];
        }
        throw runtime_error("Element not in domain");
    }

    bool isInjective() const {
        for (size_t i = 0; i < mapping.size(); i++) {
            for (size_t j = i + 1; j < mapping.size(); j++) {
                if (mapping[i] == mapping[j]) return false;
            }
        }
        return true;
    }

    bool isSurjective() const {
        for (const auto& elem : codomain) {
            bool found = false;
            for (const auto& img : mapping) {
                if (img == elem) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    }

    bool isBijective() const {
        return isInjective() && isSurjective();
    }

    template<typename W>
    Function<T, W> compose(const Function<U, W>& g) const {
        Function<T, W> result;
        for (size_t i = 0; i < domain.size(); i++) {
            try {
                W output = g.apply(mapping[i]);
                result.addMapping(domain[i], output);
            }
            catch (...) {
            }
        }
        return result;
    }

    void display() const {
        cout << "\n  Function Mapping:\n";
        for (size_t i = 0; i < domain.size(); i++) {
            cout << "  " << domain[i] << " -> " << mapping[i] << "\n";
        }

        cout << "\n  Properties:\n";
        cout << "  Injective (One-to-One): " << (isInjective() ? "Yes" : "No") << "\n";
        cout << "  Surjective (Onto): " << (isSurjective() ? "Yes" : "No") << "\n";
        cout << "  Bijective: " << (isBijective() ? "Yes" : "No") << "\n";
    }

    vector<T> getDomain() const {
        return domain;
    }

    vector<U> getMapping() const {
        return mapping;
    }
};

#endif#pragma once
