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

// Удаление здания
template <typename Container>
function<void()> MenuObject::delete_building(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&]() {
        string name;
        bool escape;

        cout << "Введите название здания, которое нужно удалить." << endl << endl;
        InputControl::enter_string(name, escape, "Название: "); if (escape) return;

        if (Building::name_exists(name)) {
            if (Building::delete_by_name(name))
                cout << "Здание \"" << name << "\" успешно удалено из списка.";
            else
                cout << "Здание \"" << name << "\" не было удалено из списка.";
        }
        else
            cout << "Здания \"" << name << "\" нет в списке.";
    };
}

// Сохранение данных о зданиях
template <typename Iterator>
function<void()> MenuObject::save_buildings(Iterator begin, Iterator end, const string& filename,
    enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
    return [&]() {
        if (SaveModule::save_buildings_to_bin(begin, end, filename))
            cout << "Данные о зданиях успешно записаны.";
        else
            cout << "Ошибка записи данных о зданиях в файл!";
    };
}

// Поиск по названию здания
template <typename Container>
function<void()> MenuObject::find_building_by_name(const Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&]() {
        string name;
        bool escape;

        cout << "Введите название здания, которое нужно найти." << endl << endl;
        InputControl::enter_string(name, escape, "Название: "); if (escape) return;

        if (Building::name_exists(name)) {
            Building* building_ptr = Building::get_building_by_name(name, buildings);
            if (building_ptr)
                cout << "Здание найдено." << endl << endl << static_cast<string>(*building_ptr);
            else
                cout << "Здания \"" << name << "\" нет в списке.";
        }
        else
            cout << "Здания \"" << name << "\" нет в списке.";
    };
}

// Сортировка по последнему году реконструкции
template <typename Iterator>
function<void()> MenuObject::sort_buildings_by_reconstruction_dates(Iterator begin, Iterator end,
    enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
    return [&]() {
        if (Building::sort_buildings_by_reconstruction_dates(begin, end))
            cout << "Список зданий успешно отсортирован.";
        else
            cout << "Список зданий не был отсортирован. Вероятно, он пустой или состоит из зданий, не имеющих дат реконструкции.";
    };
}

// Объединение двух зданий
template <typename Container>
void MenuObject::combine_two_buildings(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&]() {
        try {
            string name1, name2;
            Building building1, building2;
            bool escape;

            cout << "Введите названия двух зданий." << endl << endl;

            InputControl::enter_string(name1, escape, "Название первого: ");	    if (escape) return;
            while (!name_exists(name1, buildings)) {
                cout << endl << "Здания с таким названием не существует!" << endl << endl;
                InputControl::enter_string(name1, escape, "Название первого: ");	if (escape) return;
            }
            building1 = *Building::get_building_by_name(name1, buildings);

            InputControl::enter_string(name2, escape, "Название второго: ");	    if (escape) return;
            while (!name_exists(name2, buildings)) {
                cout << endl << "Здания с таким названием не существует!" << endl << endl;
                InputControl::enter_string(name2, escape, "Название второго: ");	if (escape) return;
            }
            building2 = *Building::get_building_by_name(name2, buildings);

            Building combined_building = building1 + building2;

            Building::delete_by_name(name1, buildings);
            Building::delete_by_name(name2, buildings);

            buildings.push_back(combined_building);

            cout << "Здания успешно объединены.";
        }
        catch (...) { cerr << "Возникла ошибка при объединении зданий."; }
    };
}

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_HPP