#ifndef KONDAKOV_LR3_4_MENU_OBJECT_HPP
#define KONDAKOV_LR3_4_MENU_OBJECT_HPP

#include "kondakov_lr3_4_menu_object.h"

// Вывод информации о зданиях
template <typename Iterator>
function<void()> MenuObject::print_buildings(Iterator begin, Iterator end, const string& separator,
    enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
    return [&]() {
        try {
            cout << Building::buildings_to_string(begin, end, separator) << endl;
            cout << "Данные успешно выведены.";
        }
        catch (...) { cerr << "Ошибка вывода данных!"; }
    };
}

// Загрузка данных о зданиях
template <typename Container>
function<void()> MenuObject::load_buildings(Container& buildings, const string& filename,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&]() {
        try {
            buildings = LoadModule::get_buildings_from_binary_file(filename);
            cout << "Данные о зданиях успешно загружены.";
        }
        catch (...) { cerr << "Ошибка загрузки данных!"; }
    };
}

// Добавление здания
template <typename Container>
function<void()> MenuObject::add_building(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&]() {
        try {
            Building* building_ptr = Building::new_building();
            if (building_ptr == nullptr)
                cout << "Здание не добавлено, так как операция была отменена.";
            else {
                buildings.emplace_back(*building_ptr);
                cout << "Здание \"" << building_ptr->get_name() << "\" успешно добавлено.";
                delete building_ptr;
            }
        }
        catch (...) { cerr << "Ошибка добавления здания!"; }
    };
}

// Сохранение данных о зданиях
template <typename Iterator>
function<void()> MenuObject::save_buildings(Iterator begin, Iterator end, const string& filename,
    enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
    return [&]() {
        bool saved = SaveModule::save_buildings_to_bin(begin, end, filename);
        if (saved)
            cout << "Данные о зданиях успешно записаны.";
        else
            cout << "Ошибка записи данных о зданиях в файл!";
    };
}

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_HPP