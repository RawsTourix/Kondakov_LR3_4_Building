#ifndef KONDAKOV_LR3_4_DEF_H
#define KONDAKOV_LR3_4_DEF_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <functional>
#include <sstream>
#include <fstream>

using namespace std;

// Переопределение операторов + и += для последовательных контейнеров
template <template <typename...> class Container, typename T>
Container<T> operator+(const Container<T>& a, const Container<T>& b) {
    Container<T> result(a);
    result.insert(result.end(), b.begin(), b.end());
    return result;
}

template <template <typename...> class Container, typename T>
Container<T>& operator+=(Container<T>& a, const Container<T>& b) {
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

#endif //!KONDAKOV_LR3_4_DEF_H