#ifndef KONDAKOV_LR3_4_DEF_H
#define KONDAKOV_LR3_4_DEF_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <numeric>
#include <functional>
#include <sstream>
#include <fstream>
#include <type_traits>
#include <utility>
#include <tuple>

using namespace std;

// Переопределение операторов + и += для последовательных контейнеров

// Объединяет 2 контейнера в 1
template <template <typename...> class Container, typename T>
Container<T> operator+(const Container<T>& a, const Container<T>& b) {
    Container<T> result(a);
    result += b;
    return result;
}

// Добавляет один контейнер в конец другого
template <template <typename...> class Container, typename T>
Container<T>& operator+=(Container<T>& a, const Container<T>& b) {
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

// Переопределение вывода << для Map
template <typename K, typename V>
ostream& operator<<(ostream& os, const map<K, V> m) {
    if (m.empty()) return os;

    auto it = m.begin();
    os << it->first << ". " << it->second;
    ++it;

    while (it != m.end()) {
        os << endl << it->first << ". " << it->second;
        ++it;
    }

    return os;
}

// Сортировка контейнера
template <template <typename ...> class Container, typename T>
void sort_container(Container<T>& container) {
    sort(container.begin(), container.end());
}

// Получение нумерованного списка
template <template <typename ...> class Container, typename T>
map<int, T> get_numbered_map(const Container<T>& container) {
    map<int, T> numbered_map;
    int index = 1;

    for (const auto& elem : container)
        numbered_map[index++] = elem;

    return numbered_map;
}

// Получение нумерованного списка по условию
template <template <typename ...> class Container, typename Obj, typename Func,
    typename T = decltype(declval<Func>()(declval<Obj>()))>
auto get_numbered_map(const Container<Obj>& container, Func&& condition)
-> map<int, T> {
    map<int, T> numbered_map;
    int index = 1;

    for (const auto& elem : container)
        numbered_map[index++] = condition(elem);

    return numbered_map;
}

#endif //!KONDAKOV_LR3_4_DEF_H