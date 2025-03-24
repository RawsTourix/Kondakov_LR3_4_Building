#ifndef KONDAKOV_LR3_4_MENU_OBJECT_HPP
#define KONDAKOV_LR3_4_MENU_OBJECT_HPP

#include "kondakov_lr3_4_menu_object.h"

// ����� ���������� � �������
template <typename Iterator>
function<void()> MenuObject::print_buildings(Iterator begin, Iterator end, const string& separator,
    enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
    return [&]() {
        try {
            cout << Building::buildings_to_string(begin, end, separator) << endl;
            cout << "������ ������� ��������.";
        }
        catch (...) { cerr << "������ ������ ������!"; }
    };
}

// �������� ������ � �������
template <typename Container>
function<void()> MenuObject::load_buildings(Container& buildings, const string& filename,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&]() {
        try {
            buildings = LoadModule::get_buildings_from_binary_file(filename);
            cout << "������ � ������� ������� ���������.";
        }
        catch (...) { cerr << "������ �������� ������!"; }
    };
}

// ���������� ������
template <typename Container>
function<void()> MenuObject::add_building(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&]() {
        try {
            Building* building_ptr = Building::new_building();
            if (building_ptr == nullptr)
                cout << "������ �� ���������, ��� ��� �������� ���� ��������.";
            else {
                buildings.emplace_back(*building_ptr);
                cout << "������ \"" << building_ptr->get_name() << "\" ������� ���������.";
                delete building_ptr;
            }
        }
        catch (...) { cerr << "������ ���������� ������!"; }
    };
}

// �������� ������
template <typename Container>
function<void()> MenuObject::delete_building(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&]() {
        string name;
        bool escape;

        cout << "������� �������� ������, ������� ����� �������." << endl << endl;
        InputControl::enter_string(name, escape, "��������: "); if (escape) return;

        if (Building::name_exists(name)) {
            if (Building::delete_by_name(name))
                cout << "������ \"" << name << "\" ������� ������� �� ������.";
            else
                cout << "������ \"" << name << "\" �� ���� ������� �� ������.";
        }
        else
            cout << "������ \"" << name << "\" ��� � ������.";
    };
}

// ���������� ������ � �������
template <typename Iterator>
function<void()> MenuObject::save_buildings(Iterator begin, Iterator end, const string& filename,
    enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
    return [&]() {
        if (SaveModule::save_buildings_to_bin(begin, end, filename))
            cout << "������ � ������� ������� ��������.";
        else
            cout << "������ ������ ������ � ������� � ����!";
    };
}

// ����� �� �������� ������
template <typename Container>
function<void()> MenuObject::find_building_by_name(const Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&]() {
        string name;
        bool escape;

        cout << "������� �������� ������, ������� ����� �����." << endl << endl;
        InputControl::enter_string(name, escape, "��������: "); if (escape) return;

        if (Building::name_exists(name)) {
            Building* building_ptr = Building::get_building_by_name(name, buildings);
            if (building_ptr)
                cout << "������ �������." << endl << endl << static_cast<string>(*building_ptr);
            else
                cout << "������ \"" << name << "\" ��� � ������.";
        }
        else
            cout << "������ \"" << name << "\" ��� � ������.";
    };
}

// ���������� �� ���������� ���� �������������
template <typename Iterator>
function<void()> MenuObject::sort_buildings_by_reconstruction_dates(Iterator begin, Iterator end,
    enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
    return [&]() {
        if (Building::sort_buildings_by_reconstruction_dates(begin, end))
            cout << "������ ������ ������� ������������.";
        else
            cout << "������ ������ �� ��� ������������. ��������, �� ������ ��� ������� �� ������, �� ������� ��� �������������.";
    };
}

// ����������� ���� ������
template <typename Container>
void MenuObject::combine_two_buildings(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&]() {
        try {
            string name1, name2;
            Building building1, building2;
            bool escape;

            cout << "������� �������� ���� ������." << endl << endl;

            InputControl::enter_string(name1, escape, "�������� �������: ");	    if (escape) return;
            while (!name_exists(name1, buildings)) {
                cout << endl << "������ � ����� ��������� �� ����������!" << endl << endl;
                InputControl::enter_string(name1, escape, "�������� �������: ");	if (escape) return;
            }
            building1 = *Building::get_building_by_name(name1, buildings);

            InputControl::enter_string(name2, escape, "�������� �������: ");	    if (escape) return;
            while (!name_exists(name2, buildings)) {
                cout << endl << "������ � ����� ��������� �� ����������!" << endl << endl;
                InputControl::enter_string(name2, escape, "�������� �������: ");	if (escape) return;
            }
            building2 = *Building::get_building_by_name(name2, buildings);

            Building combined_building = building1 + building2;

            Building::delete_by_name(name1, buildings);
            Building::delete_by_name(name2, buildings);

            buildings.push_back(combined_building);

            cout << "������ ������� ����������.";
        }
        catch (...) { cerr << "�������� ������ ��� ����������� ������."; }
    };
}

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_HPP