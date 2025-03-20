#ifndef KONDAKOV_LR3_4_DEF_H
#define KONDAKOV_LR3_4_DEF_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <functional>

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

// Преобразование контейнеров, хранящих экземпляры класса Здание, в строку
template <typename Iterator>
string buildings_to_string(Iterator begin, Iterator end, const string& separator = "\n") {
    if (begin == end) return "";

    string result = *begin;
    ++begin;

    while (begin != end) {
        result += separator + *begin;
        ++begin;
    }

    return result;
}

// Вывод информации о зданиях
template <typename Iterator>
function<void()> print_buildings(Iterator begin, Iterator end, const string& separator = "\n") {
    cout << buildings_to_string(begin, end, separator);
}

#endif //!KONDAKOV_LR3_4_DEF_H