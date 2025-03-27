#ifndef KONDAKOV_LR3_4_MENU_OBJECT_HPP
#define KONDAKOV_LR3_4_MENU_OBJECT_HPP

#include "kondakov_lr3_4_menu_object.h"


// ����� ������ ����
inline void MenuObject::show() const {
    cout << number << ". " << label << endl;
}

// ��������� �������
inline void MenuObject::act() const {
    action();
}

// ������ ������ ������
inline int MenuObject::get_number() const {
    return number;
}

// 1. ����� ���������� � �������
template <typename Container>
function<void()> MenuObject::print_buildings(const Container& buildings, const string& separator,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [=, &buildings]() {
        try {
            string buildings_str = Building::buildings_to_string(buildings, separator);
            if (buildings_str.empty())
                cout << "� ������ ��� �� ������ ������.";
            else
                cout << buildings_str << endl << endl << "������ ������� ��������.";
        }
        catch (...) { cerr << "������ ������ ������!"; }
    };
}

// 2. �������� ������ � �������
template <typename Container>
function<void()> MenuObject::load_buildings(Container& buildings, const string& filename,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings, &filename]() {
        try {
            vector<Building> buildings_data = LoadModule::get_buildings_from_binary_file(filename);

            if (buildings_data.empty())
                cout << "������ �� ���������.";
            else {
                if (buildings == buildings_data)
                    cout << "������ ���������.";
                else {
                    buildings = buildings_data;
                    cout << "������ � ������� ������� ���������.";
                }
            }
        }
        catch (...) { cerr << "������ �������� ������!"; }
    };
}

// 3. ���������� ������
template <typename Container>
function<void()> MenuObject::add_building(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        try {
            unique_ptr<Building> building_ptr(Building::new_building(buildings));
            if (building_ptr) {
                buildings.push_back(move(*building_ptr));
                cout << "������ \"" << building_ptr->get_name() << "\" ������� ���������.";
            }
            else
                cout << endl << "������ �� ���������, ��� ��� �������� ���� ��������.";
        }
        catch (...) { cerr << "������ ���������� ������!"; }
    };
}

// 4. �������� ������
template <typename Container>
function<void()> MenuObject::delete_building(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        string name;
        bool escape;

        cout << "������� �������� ������, ������� ����� �������." << endl << endl;
        InputControl::enter_string(name, escape, "��������: "); if (escape) return;
        cout << endl;

        if (Building::name_exists(name, buildings)) {
            if (Building::delete_by_name(name, buildings))
                cout << "������ \"" << name << "\" ������� ������� �� ������.";
            else
                cout << "������ \"" << name << "\" �� ���� ������� �� ������.";
        }
        else
            cout << "������ \"" << name << "\" ��� � ������.";
    };
}

// 5. ���������� ������ � �������
template <typename Container>
function<void()> MenuObject::save_buildings(const Container& buildings, const string& filename,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    auto save = [&buildings, &filename]() {
        try {
            if (SaveModule::save_buildings_to_bin(buildings, filename))
                cout << "������ � ������� ������� ���������.";
            else
                cout << "������ ���������� ������ � �������� ����!";
        }
        catch (const exception& e) { cerr << "������ ����������: " << e.what(); }
    };

    return [=, &buildings]() {
        if (buildings.empty()) {
            cout << "� ������ ��� ������." << endl << endl;
            if (InputControl::yes_or_no("�� �������, ��� ������ ���������?")) {
                save();
            }
            else {
                cout << "������ ������ ��������.";
            }
        }
        else { save(); }
    };
}

// 6. ����� �� �������� ������
template <typename Container>
function<void()> MenuObject::find_building_by_name(Container& buildings, // �� const, ������ ��� � get_building_by_name ����� �������� ������������� ������
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        string search;
        bool escape;

        cout << "������� �������� ������, ������� ����� �����." << endl << endl;
        InputControl::enter_string(search, escape, "����� �� ��������: "); if (escape) return;
        cout << endl;

        if (Building::name_exists(search, buildings)) {

            Building* building_ptr = Building::get_building_by_name(search, buildings);
            if (building_ptr)
                cout << static_cast<string>(*building_ptr) << endl << endl << "������ � ��������� \"" << search << "\" �������.";
            else
                cout << "�� ������� \"" << search << "\" ������ �� �������.";
        }
        else {
            vector<Building> found_buildings = Building::get_buildings_by_name_substr(search, buildings);
            if (found_buildings.empty())
                cout << "�� ������� \"" << search << "\" ������ �� �������.";
            else
                cout << Building::buildings_to_string(found_buildings) << endl << endl << "��������� ������ �� ������� \"" << search << "\".";
        }
    };
}

// 7. ���������� �� ���������� ���� �������������
template <typename Container>
function<void()> MenuObject::sort_buildings_by_reconstruction_dates(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        if (Building::sort_buildings_by_reconstruction_dates(buildings))
            cout << "������ ������ ������� ������������.";
        else
            cout << "������ ������ �� ��� ������������. ��������, �� ������ ��� ������� �� ������, �� ������� ��� �������������.";
    };
}

// 8. ����������� ���� ������
template <typename Container>
function<void()> MenuObject::combine_two_buildings(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        try {
            string name1, name2;
            Building building1, building2;
            bool escape;

            cout << "������� �������� ���� ������." << endl << endl;

            InputControl::enter_string(name1, escape, "�������� �������: ");	    if (escape) return;
            while (!Building::name_exists(name1, buildings)) {
                cout << endl << "������ � ����� ��������� �� ����������!" << endl << endl;
                InputControl::enter_string(name1, escape, "�������� �������: ");	if (escape) return;
            }
            building1 = *Building::get_building_by_name(name1, buildings);

            InputControl::enter_string(name2, escape, "�������� �������: ");	    if (escape) return;
            while (!Building::name_exists(name2, buildings)) {
                cout << endl << "������ � ����� ��������� �� ����������!" << endl << endl;
                InputControl::enter_string(name2, escape, "�������� �������: ");	if (escape) return;
            }
            building2 = *Building::get_building_by_name(name2, buildings);
            cout << endl;

            Building combined_building = building1 + building2;

            Building::delete_by_name(name1, buildings);
            Building::delete_by_name(name2, buildings);

            buildings.push_back(move(combined_building));

            cout << "������ ������� ����������.";
        }
        catch (...) { cerr << "�������� ������ ��� ����������� ������."; }
    };
}

// ����� ����
template <typename Container>
void MenuObject::show_menu(const Container& menu,
    enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>*) {
    for (const auto& item : menu)
        item.show();

    cout << "0. �����." << endl << endl << endl;
}

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_HPP