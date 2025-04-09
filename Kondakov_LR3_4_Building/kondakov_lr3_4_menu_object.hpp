#ifndef KONDAKOV_LR3_4_MENU_OBJECT_HPP
#define KONDAKOV_LR3_4_MENU_OBJECT_HPP

#include "kondakov_lr3_4_menu_object.h"


// Вывод пункта меню
inline void MenuObject::show(const string& indentation) const {
    cout << indentation << number << ". " << label << endl;
}

// Выполнить функцию
inline void MenuObject::act() const {
    if (action)
        action();
    else
        cout << "Функция не задана для этого пункта..." << endl << endl;
}

// Геттер названия пункта
inline string MenuObject::get_label() const {
    return label;
}

// Геттер номера пункта
inline int MenuObject::get_number() const {
    return number;
}

// Геттер полного названия пункта
inline string MenuObject::get_full_name() const {
    ostringstream oss;
    oss << number << ". " << label;
    return oss.str();
}

// Геттер подменю
inline const vector<MenuObject>& MenuObject::get_submenu() const {
    return submenu;
}

// 1. Вывод информации о зданиях
template <typename Container>
function<void()> MenuObject::print_buildings(const Container& buildings, const string& separator,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [=, &buildings]() {
        cout << "Вывод списка зданий." << endl << endl;
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
        cout << "Загрузка данных из бинарного файла." << endl << endl;
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
        cout << "Добавление здания в список." << endl << endl;
        try {
            unique_ptr<Building> building_ptr(Building::new_building(buildings));
            if (building_ptr) {
                string name = building_ptr->get_name();
                buildings.push_back(move(*building_ptr));
                cout << "Здание \"" << name << "\" успешно добавлено.";
            }
            else
                cout << endl << endl << "Здание не добавлено, так как операция была отменена.";
        }
        catch (...) { cerr << "Ошибка добавления здания!"; }
    };
}

// 4. Удаление здания
template <typename Container>
function<void()> MenuObject::delete_building(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Удаление здания." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            string name = building_ptr->get_name();

            if (Building::name_exists(name, buildings)) {
                if (Building::delete_by_name(name, buildings))
                    cout << "Здание \"" << name << "\" успешно удалено.";
                else
                    cout << "Здание \"" << name << "\" не было удалено.";
            }
            else
                cout << "Здания \"" << name << "\" нет в списке.";
        }
        catch (...) { cerr << "Ошибка удаления здания!"; }
    };
}

// 5. Сохранение данных о зданиях
template <typename Container>
function<void()> MenuObject::save_buildings(const Container& buildings, const string& filename,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    auto save = [&buildings, &filename]() {
        cout << "Сохранение данных в бинарный файл." << endl << endl;
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
            if (InputControl::yes_or_no("Вы уверены, что хотите сохранить?"))
                save();
            else
                cout << "Запись данных отменена.";
        }
        else { save(); }
    };
}

// 6. Поиск по названию здания
template <typename Container>
function<void()> MenuObject::find_building_by_name(Container& buildings, // не const, потому что в get_building_by_name нужно передать неконстантную ссылку
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Поиск по названию здания." << endl << endl;
        cout << "Введите название, которое нужно найти." << endl << endl;
        try {
            string search;

            if (InputControl::input(search, "Название: ")) return;
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
        }
        catch (...) { cerr << "Ошибка поиска здания!"; }
    };
}

/* 7. Сортировка */
// 7.1. Сортировка по последнему году реконструкции
template <typename Container>
function<void()> MenuObject::sort_buildings_by_reconstruction_dates(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Сортировка по последнему году реконструкции." << endl << endl;
        try {
            if (Building::sort_buildings_by_reconstruction_dates(buildings))
                cout << "Список зданий успешно отсортирован.";
            else
                cout << "Список зданий не был отсортирован. Вероятно, он пустой или состоит из зданий, не имеющих дат реконструкции.";
        }
        catch (...) { cerr << "Ошибка сортировки!"; }
    };
}

// 7.2. Сортировка по средней дате реконструкции
template <typename Container>
function<void()> MenuObject::sort_buildings_by_avg_reconstruction_date(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Сортировка по средней дате реконструкции." << endl << endl;
        try {
            if (Building::sort_buildings_by_avg_reconstruction_date(buildings))
                cout << "Список зданий успешно отсортирован.";
            else
                cout << "Список зданий не был отсортирован. Вероятно, он пустой или состоит из зданий, не имеющих дат реконструкции.";
        }
        catch (...) { cerr << "Ошибка сортировки!"; }
    };
}

// 7.3. Сортировка по высоте
template <typename Container>
function<void()> MenuObject::sort_buildings_by_height(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Сортировка по высоте." << endl << endl;
        try {
            if (Building::sort_buildings_by_height(buildings))
                cout << "Список зданий успешно отсортирован.";
            else
                cout << "Список зданий не был отсортирован. Вероятно, он пустой.";
        }
        catch (...) { cerr << "Ошибка сортировки!"; }
    };
}

// 7.4. Сортировка по площади
template <typename Container>
function<void()> MenuObject::sort_buildings_by_square(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Сортировка по площади." << endl << endl;
        try {
            if (Building::sort_buildings_by_square(buildings))
                cout << "Список зданий успешно отсортирован.";
            else
                cout << "Список зданий не был отсортирован. Вероятно, он пустой.";
        }
        catch (...) { cerr << "Ошибка сортировки!"; }
    };
}

// 7.5. Сортировка по объёму
template <typename Container>
function<void()> MenuObject::sort_buildings_by_volume(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Сортировка по объёму." << endl << endl;
        try {
            if (Building::sort_buildings_by_volume(buildings))
                cout << "Список зданий успешно отсортирован.";
            else
                cout << "Список зданий не был отсортирован. Вероятно, он пустой.";
        }
        catch (...) { cerr << "Ошибка сортировки!"; }
    };
}

// 7.6. Сортировка по всем параметрам
template <typename Container>
function<void()> MenuObject::sort_buildings_by_all(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Сортировка по всем параметрам." << endl << endl;
        try {
            if (Building::sort_buildings_by_all(buildings))
                cout << "Список зданий успешно отсортирован.";
            else
                cout << "Список зданий не был отсортирован. Вероятно, он пустой.";
        }
        catch (...) { cerr << "Ошибка сортировки!"; }
    };
}

// 8. Объединение двух зданий
template <typename Container>
function<void()> MenuObject::combine_two_buildings(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Объединение двух зданий." << endl << endl;
        try {
            Building* building1_ptr = Building::choose_building_by_name_number(buildings, "Выберите первое здание.");
            if (building1_ptr == nullptr) return;
            cout << "Первое здание выбрано." << endl << endl;
            Building building1 = *building1_ptr;

            Building* building2_ptr;
            do {
                building2_ptr = Building::choose_building_by_name_number(buildings, "Выберите второе здание.");
                if (building1_ptr == building2_ptr)
                    cout << "Нельзя объединить одно и то же здание!" << endl << endl;
            } while (building1_ptr == building2_ptr);
            if (building2_ptr == nullptr) return;
            cout << "Второе здание выбрано." << endl << endl;
            Building building2 = *building2_ptr;

            Building combined_building = building1 + building2;

            Building::delete_by_name(building1.get_name(), buildings);
            Building::delete_by_name(building2.get_name(), buildings);

            cout << static_cast<string>(combined_building) << endl << endl;

            buildings.push_back(move(combined_building));

            cout << "Здания успешно объединены.";
        }
        catch (...) { cerr << "Ошибка объединения зданий!"; }
    };
}

/* 9. Изменение параметров здания: */
// 9.1. Названия
template <typename Container>
function<void()> MenuObject::change_building_name(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Изменение названия." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                             return;

            Building& building = *building_ptr;

            cout << "Введите новое название здания." << endl << endl;

            string new_name;
            const string old_name = building.get_name();
            if (InputControl::input(new_name, "Название: "))         return;
            cout << endl;

            while (new_name == old_name) {
                if (InputControl::yes_or_no("Новое название здания совпадает со старым. Продолжить?")) break;
                else {
                    if (InputControl::input(new_name, "Название: ")) return;
                    cout << endl;
                }
            }

            building.set_name(new_name);

            cout << "Название успешно изменено \"" << old_name << "\" -> \"" << new_name << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка измения названия!"; }
    };
}

/* 9.2. Высоты: */
// 9.2.1. Увеличение на 1
template <typename Container>
function<void()> MenuObject::increase_building_height_by_1(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Увеличение высоты на 1." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            Building& building = *building_ptr;

            const int old_height = building.get_height();
            building++;
            const int new_height = building.get_height();

            cout << "Высота здания успешно изменена \"" << old_height << "\" -> \"" << new_height << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка увеличения высоты на 1!"; }
    };
}

// 9.2.2. Увеличение на число
template <typename Container>
function<void()> MenuObject::increase_building_height_by_n(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Увеличение высоты на число." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                             return;

            Building& building = *building_ptr;

            int n;
            do {
                if (InputControl::input(n, "Увеличить высоту на: ")) return;
                cout << endl;
                if (building.get_height() + n < 0) cout << "Высота здания не может быть меньше нуля!" << endl << endl;
            } while (building.get_height() + n < 0);

            const int old_height = building.get_height();
            building += n;
            const int new_height = building.get_height();

            cout << "Высота здания успешно изменена \"" << old_height << "\" -> \"" << new_height << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка увеличения высоты на число!"; }
    };
}

// 9.2.3. Уменьшение на 1
template <typename Container>
function<void()> MenuObject::decrease_building_height_by_1(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Уменьшение высоты на 1." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            Building& building = *building_ptr;

            if (building.get_height() - 1 < 0) {
                cout << "Высота здания не может быть меньше нуля!";
                return;
            }

            const int old_height = building.get_height();
            building--;
            const int new_height = building.get_height();

            cout << "Высота здания успешно изменена \"" << old_height << "\" -> \"" << new_height << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка уменьшения высоты на 1!"; }
    };
}

// 9.2.4. Уменьшение на число
template <typename Container>
function<void()> MenuObject::decrease_building_height_by_n(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Уменьшение высоты на число." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                             return;

            Building& building = *building_ptr;

            int n;
            do {
                if (InputControl::input(n, "Уменьшить высоту на: ")) return;
                cout << endl;
                if (building.get_height() - n < 0) cout << "Высота здания не может быть меньше нуля!" << endl << endl;
            } while (building.get_height() - n < 0);

            const int old_height = building.get_height();
            building -= n;
            const int new_height = building.get_height();

            cout << "Высота здания успешно изменена \"" << old_height << "\" -> \"" << new_height << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка уменьшения высоты на число!"; }
    };
}

// 9.2.5. Задание самостоятельно
template <typename Container>
function<void()> MenuObject::change_building_height(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Задание высоты самостоятельно." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                                         return;

            Building& building = *building_ptr;

            int new_height;
            const int old_height = building.get_height();
            do {
                do {
                    if (InputControl::input(new_height, "Изменить высоту на: ")) return;
                    cout << endl;
                    if (new_height == old_height)
                        if (InputControl::yes_or_no("Новая высота здания совпадает со старой. Продолжить?")) break;
                } while (new_height == old_height);
                if (new_height < 0) cout << "Высота здания не может быть меньше нуля!" << endl << endl;
            } while (new_height < 0);

            building.set_height(new_height);

            cout << "Высота здания успешно изменена \"" << old_height << "\" -> \"" << new_height << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка задания высоты!"; }
    };
}

/* 9.3. Площади: */
// 9.3.1. Увеличение на 1
template <typename Container>
function<void()> MenuObject::increase_building_square_by_1(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Увеличение площади на 1." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            Building& building = *building_ptr;

            const int old_square = building.get_square();
            building.set_square(building.get_square() + 1);
            const int new_square = building.get_square();

            cout << "Площадь здания успешно изменена \"" << old_square << "\" -> \"" << new_square << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка увеличения площади на 1!"; }
    };
}

// 9.3.2. Увеличение на число
template <typename Container>
function<void()> MenuObject::increase_building_square_by_n(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Увеличение площади на число." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                              return;

            Building& building = *building_ptr;

            int n;
            const int old_square = building.get_square();
            do {
                if (InputControl::input(n, "Увеличить площадь на: ")) return;
                cout << endl;
                if (old_square + n < 0) cout << "Площадь здания не может быть меньше нуля!" << endl << endl;
            } while (old_square + n < 0);

            building.set_square(building.get_square() + n);
            const int new_square = building.get_square();

            cout << "Площадь здания успешно изменена \"" << old_square << "\" -> \"" << new_square << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка увеличения площади на число!"; }
    };
}

// 9.3.3. Уменьшение на 1
template <typename Container>
function<void()> MenuObject::decrease_building_square_by_1(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Уменьшение площади на 1." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            Building& building = *building_ptr;

            const int old_square = building.get_square();

            if (old_square - 1 < 0) {
                cout << "Площадь здания не может быть меньше нуля!" << endl << endl;
                return;
            }

            building.set_square(building.get_square() - 1);
            const int new_square = building.get_square();

            cout << "Площадь здания успешно изменена \"" << old_square << "\" -> \"" << new_square << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка уменьшения площади на 1!"; }
    };
}

// 9.3.4. Уменьшение на число
template <typename Container>
function<void()> MenuObject::decrease_building_square_by_n(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Уменьшение площади на число." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                              return;

            Building& building = *building_ptr;

            int n;
            const int old_square = building.get_square();
            do {
                if (InputControl::input(n, "Уменьшить площадь на: ")) return;
                cout << endl;
                if (old_square - n < 0) cout << "Площадь здания не может быть меньше нуля!" << endl << endl;
            } while (old_square - n < 0);
            
            building.set_square(building.get_square() - n);
            const int new_square = building.get_square();

            cout << "Площадь здания успешно изменена \"" << old_square << "\" -> \"" << new_square << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка уменьшение площади на число!"; }
    };
}

// 9.3.5. Задание самостоятельно
template <typename Container>
function<void()> MenuObject::change_building_square(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Задание площади самостоятельно." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                                          return;

            Building& building = *building_ptr;

            int new_square;
            const int old_square = building.get_square();
            do {
                do {
                    if (InputControl::input(new_square, "Изменить площадь на: ")) return;
                    cout << endl;
                    if (new_square == old_square)
                        if (InputControl::yes_or_no("Новая площадь здания совпадает со старой. Продолжить?")) break;
                } while (new_square == old_square);
                if (new_square < 0) cout << "Площадь здания не может быть меньше нуля!" << endl << endl;
            } while (new_square < 0);

            building.set_square(new_square);

            cout << "Площадь здания успешно изменена \"" << old_square << "\" -> \"" << new_square << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка задания площади!"; }
    };
}

/* 9.4. Списка дат реконструкции: */
// 9.4.1. Добавление даты
template <typename Container>
function<void()> MenuObject::add_building_reconstruction_date(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Добавление даты." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                              return;

            Building& building = *building_ptr;
            vector<int>& reconstruction_dates = building.get_reconstruction_dates_link();

            int year;
            if (InputControl::input(year, "Добавить год: ", 0, 2025)) return;
            cout << endl;

            reconstruction_dates.push_back(year);
            sort_container(reconstruction_dates);

            cout << "Год реконструкции успешно добавлен \"" << year << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка добавления даты!"; }
    };
}

// 9.4.2. Изменение даты
template <typename Container>
function<void()> MenuObject::edit_building_reconstruction_date(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Изменение даты." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                         return;

            Building& building = *building_ptr;

            int* current_year_ptr = Building::choose_reconstruction_date_by_year_number(building);
            if (current_year_ptr == nullptr)                     return;

            int& current_year = *current_year_ptr;

            int old_year = current_year;

            int new_year;
            if (InputControl::input(new_year, "Изменить год: ")) return;
            cout << endl;

            current_year = new_year;
            sort_container(building.get_reconstruction_dates_link());

            cout << "Год реконструкции успешно изменён \"" << old_year << "\" -> \"" << current_year << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка изменения даты!"; }
    };
}

// 9.4.3. Удаление даты
template <typename Container>
function<void()> MenuObject::delete_building_reconstruction_date(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Удаление даты." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            Building& building = *building_ptr;
            vector<int>& reconstruction_dates = building.get_reconstruction_dates_link();

            int* year_ptr = Building::choose_reconstruction_date_by_year_number(building);
            if (year_ptr == nullptr)     return;

            int year = *year_ptr;

            reconstruction_dates.erase(find_if(reconstruction_dates.begin(), reconstruction_dates.end(), [&year](int y) { return y == year; }));
            sort_container(reconstruction_dates);

            cout << "Год реконструкции успешно удалён \"" << year << "\" -> \"x\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка удаления даты!"; }
    };
}

// 9.4.4. Ввод списка заново
template <typename Container>
function<void()> MenuObject::change_building_reconstruction_dates(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "Ввод дат заново." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                                        return;

            Building& building = *building_ptr;
            vector<int>& reconstruction_dates = building.get_reconstruction_dates_link();

            if (InputControl::input_reconstruction_dates(reconstruction_dates))	return;

            cout << "Список дат реконструкции успешно изменён:" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "Ошибка задания списка дат реконструкций!"; }
    };
}

// Вывод меню
template <typename Container>
void MenuObject::show_menu(const Container& menu, int indent,
    enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>*) {
    string indentation(indent, '\t');
    for (const auto& item : menu) {
        item.show(indentation);
        if (!item.get_submenu().empty())
            show_menu(item.get_submenu(), indent + 1);
    }
}

// Обработка взаимодействия с меню
template <typename Container>
void MenuObject::process(const Container& menu, const string main_label, const string exit_label, int indent,
    enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>*) {
    int number;
    do {
        if (!main_label.empty()) cout << main_label << endl << endl;
        show_menu(menu, indent);
        cout << "0. " << exit_label << endl << endl << endl;
        if (InputControl::input(number, "Пункт меню: ", 0, static_cast<int>(menu.size()))) { cout << endl << endl << endl; continue; }
        cout << endl << endl;
        if (number == 0) break;
        try {
            auto it = find_if(menu.begin(), menu.end(), [number](MenuObject m) { return m.get_number() == number; });
            if (it != menu.end()) {
                if (it->get_submenu().empty())
                    (*it).act();
                else {
                    vector<MenuObject> submenu = it->get_submenu();
                    process(submenu, it->get_label(), "Назад.", indent);
                    continue;
                }
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what();
        }
        cout << endl << endl << endl;
    } while (number != 0);
}

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_HPP