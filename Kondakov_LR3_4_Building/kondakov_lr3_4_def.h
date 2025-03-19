#ifndef KONDAKOV_LR3_4_DEF_H
#define KONDAKOV_LR3_4_DEF_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;

// Переопределение операторов + и += для vector
template <typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
    vector<T> result(a);
    result.insert(result.end(), b.begin(), b.end());
    return result;
}

template <typename T>
vector<T>& operator+=(vector<T>& a, const vector<T>& b) {
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

#endif //!KONDAKOV_LR3_4_DEF_H