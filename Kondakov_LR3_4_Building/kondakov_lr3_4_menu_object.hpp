#ifndef KONDAKOV_LR3_4_MENU_OBJECT_HPP
#define KONDAKOV_LR3_4_MENU_OBJECT_HPP

#include "kondakov_lr3_4_menu_object.h"


// Вывод пункта меню
inline void MenuObject::show() const {
    cout << number << ". " << label << endl;
}

// Выполнить функцию
inline void MenuObject::act() const {
    action();
}

// Геттер номера пункта
inline int MenuObject::get_number() const {
    return number;
}

// 1. Вывод информации о зданиях
template <typename Container>
function<void()> MenuObject::print_buildings(const Container& buildings, const string& separator,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [=, &buildings]() {
        try {
            string buildings_str = Building::buildings_to_string(buildings, separator);
            if (buildings_str.empty())
                cout << "В списке нет ни одного здания.";
            else
                cout << buildings_str << endl << endl << "Данные успешно выведены.";
        }
        catch (...) { cerr << "Ошибка вывода данных!"; }
    };
}

// 2. Загрузка данных о зданиях
template <typename Container>
function<void()> MenuObject::load_buildings(Container& buildings, const string& filename,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings, &filename]() {
        try {
            vector<Building> buildings_data = LoadModule::get_buildings_from_binary_file(filename);

            if (buildings_data.empty())
                cout << "Данные не загружены.";
            else {
                if (buildings == buildings_data)
                    cout << "Данные актуальны.";
                else {
                    buildings = buildings_data;
                    cout << "Данные о зданиях успешно загружены.";
                }
            }
        }
        catch (...) { cerr << "Ошибка загрузки данных!"; }
    };
}

// 3. Добавление здания
template <typename Container>
function<void()> MenuObject::add_building(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        try {
            unique_ptr<Building> building_ptr(Building::new_building(buildings));
            if (building_ptr) {
                buildings.push_back(move(*building_ptr));
                cout << "Здание \"" << building_ptr->get_name() << "\" успешно добавлено.";
            }
            else
                cout << endl << "Здание не добавлено, так как операция была отменена.";
        }
        catch (...) { cerr << "Ошибка добавления здания!"; }
    };
}

// 4. Удаление здания
template <typename Container>
function<void()> MenuObject::delete_building(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        string name;
        bool escape;

        cout << "Введите название здания, которое нужно удалить." << endl << endl;
        InputControl::enter_string(name, escape, "Название: "); if (escape) return;
        cout << endl;

        if (Building::name_exists(name, buildings)) {
            if (Building::delete_by_name(name, buildings))
                cout << "Здание \"" << name << "\" успешно удалено из списка.";
            else
                cout << "Здание \"" << name << "\" не было удалено из списка.";
        }
        else
            cout << "Здания \"" << name << "\" нет в списке.";
    };
}

// 5. Сохранение данных о зданиях
template <typename Container>
function<void()> MenuObject::save_buildings(const Container& buildings, const string& filename,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    auto save = [&buildings, &filename]() {
        try {
            if (SaveModule::save_buildings_to_bin(buildings, filename))
                cout << "Данные о зданиях успешно сохранены.";
            else
                cout << "Ошибка сохранения данных в бинарный файл!";
        }
        catch (const exception& e) { cerr << "Ошибка сохранения: " << e.what(); }
    };

    return [=, &buildings]() {
        if (buildings.empty()) {
            cout << "В списке нет зданий." << endl << endl;
            if (InputControl::yes_or_no("Вы уверены, что хотите сохранить?")) {
                save();
            }
            else {
                cout << "Запись данных отменена.";
            }
        }
        else { save(); }
    };
}

// 6. Поиск по названию здания
template <typename Container>
function<void()> MenuObject::find_building_by_name(Container& buildings, // не const, потому что в get_building_by_name нужно передать неконстантную ссылку
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        string search;
        bool escape;

        cout << "Введите название здания, которое нужно найти." << endl << endl;
        InputControl::enter_string(search, escape, "Поиск по названию: "); if (escape) return;
        cout << endl;

        if (Building::name_exists(search, buildings)) {

            Building* building_ptr = Building::get_building_by_name(search, buildings);
            if (building_ptr)
                cout << static_cast<string>(*building_ptr) << endl << endl << "Здание с названием \"" << search << "\" найдено.";
            else
                cout << "По запросу \"" << search << "\" ничего не найдено.";
        }
        else {
            vector<Building> found_buildings = Building::get_buildings_by_name_substr(search, buildings);
            if (found_buildings.empty())
                cout << "По запросу \"" << search << "\" ничего не найдено.";
            else
                cout << Building::buildings_to_string(found_buildings) << endl << endl << "Приведены здания по запросу \"" << search << "\".";
        }
    };
}

// 7. Сортировка по последнему году реконструкции
template <typename Container>
function<void()> MenuObject::sort_buildings_by_reconstruction_dates(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        if (Building::sort_buildings_by_reconstruction_dates(buildings))
            cout << "Список зданий успешно отсортирован.";
        else
            cout << "Список зданий не был отсортирован. Вероятно, он пустой или состоит из зданий, не имеющих дат реконструкции.";
    };
}

// 8. Объединение двух зданий
template <typename Container>
function<void()> MenuObject::combine_two_buildings(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        try {
            string name1, name2;
            Building building1, building2;
            bool escape;

            cout << "Введите названия двух зданий." << endl << endl;

            InputControl::enter_string(name1, escape, "Название первого: ");	    if (escape) return;
            while (!Building::name_exists(name1, buildings)) {
                cout << endl << "Здания с таким названием не существует!" << endl << endl;
                InputControl::enter_string(name1, escape, "Название первого: ");	if (escape) return;
            }
            building1 = *Building::get_building_by_name(name1, buildings);

            InputControl::enter_string(name2, escape, "Название второго: ");	    if (escape) return;
            while (!Building::name_exists(name2, buildings)) {
                cout << endl << "Здания с таким названием не существует!" << endl << endl;
                InputControl::enter_string(name2, escape, "Название второго: ");	if (escape) return;
            }
            building2 = *Building::get_building_by_name(name2, buildings);
            cout << endl;

            Building combined_building = building1 + building2;

            Building::delete_by_name(name1, buildings);
            Building::delete_by_name(name2, buildings);

            buildings.push_back(move(combined_building));

            cout << "Здания успешно объединены.";
        }
        catch (...) { cerr << "Возникла ошибка при объединении зданий."; }
    };
}

// Вывод меню
template <typename Container>
void MenuObject::show_menu(const Container& menu,
    enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>*) {
    for (const auto& item : menu)
        item.show();

    cout << "0. Выход." << endl << endl << endl;
}

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_HPP