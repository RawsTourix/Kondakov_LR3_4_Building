#ifndef KONDAKOV_LR3_4_MENU_OBJECT_HPP
#define KONDAKOV_LR3_4_MENU_OBJECT_HPP

#include "kondakov_lr3_4_menu_object.h"


// ����� ������ ����
inline void MenuObject::show(const string& indentation) const {
    cout << indentation << number << ". " << label << endl;
}

// ��������� �������
inline void MenuObject::act() const {
    if (action)
        action();
    else
        cout << "������� �� ������ ��� ����� ������..." << endl << endl;
}

// ������ �������� ������
inline string MenuObject::get_label() const {
    return label;
}

// ������ ������ ������
inline int MenuObject::get_number() const {
    return number;
}

// ������ ������� �������� ������
inline string MenuObject::get_full_name() const {
    ostringstream oss;
    oss << number << ". " << label;
    return oss.str();
}

// ������ �������
inline const vector<MenuObject>& MenuObject::get_submenu() const {
    return submenu;
}

// 1. ����� ���������� � �������
template <typename Container>
function<void()> MenuObject::print_buildings(const Container& buildings, const string& separator,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [=, &buildings]() {
        cout << "����� ������ ������." << endl << endl;
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
        cout << "�������� ������ �� ��������� �����." << endl << endl;
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
        cout << "���������� ������ � ������." << endl << endl;
        try {
            unique_ptr<Building> building_ptr(Building::new_building(buildings));
            if (building_ptr) {
                string name = building_ptr->get_name();
                buildings.push_back(move(*building_ptr));
                cout << "������ \"" << name << "\" ������� ���������.";
            }
            else
                cout << endl << endl << "������ �� ���������, ��� ��� �������� ���� ��������.";
        }
        catch (...) { cerr << "������ ���������� ������!"; }
    };
}

// 4. �������� ������
template <typename Container>
function<void()> MenuObject::delete_building(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "�������� ������." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            string name = building_ptr->get_name();

            if (Building::name_exists(name, buildings)) {
                if (Building::delete_by_name(name, buildings))
                    cout << "������ \"" << name << "\" ������� �������.";
                else
                    cout << "������ \"" << name << "\" �� ���� �������.";
            }
            else
                cout << "������ \"" << name << "\" ��� � ������.";
        }
        catch (...) { cerr << "������ �������� ������!"; }
    };
}

// 5. ���������� ������ � �������
template <typename Container>
function<void()> MenuObject::save_buildings(const Container& buildings, const string& filename,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    auto save = [&buildings, &filename]() {
        cout << "���������� ������ � �������� ����." << endl << endl;
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
            if (InputControl::yes_or_no("�� �������, ��� ������ ���������?"))
                save();
            else
                cout << "������ ������ ��������.";
        }
        else { save(); }
    };
}

// 6. ����� �� �������� ������
template <typename Container>
function<void()> MenuObject::find_building_by_name(Container& buildings, // �� const, ������ ��� � get_building_by_name ����� �������� ������������� ������
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "����� �� �������� ������." << endl << endl;
        cout << "������� ��������, ������� ����� �����." << endl << endl;
        try {
            string search;

            if (InputControl::input(search, "��������: ")) return;
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
        }
        catch (...) { cerr << "������ ������ ������!"; }
    };
}

/* 7. ���������� */
// 7.1. ���������� �� ���������� ���� �������������
template <typename Container>
function<void()> MenuObject::sort_buildings_by_reconstruction_dates(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� �� ���������� ���� �������������." << endl << endl;
        try {
            if (Building::sort_buildings_by_reconstruction_dates(buildings))
                cout << "������ ������ ������� ������������.";
            else
                cout << "������ ������ �� ��� ������������. ��������, �� ������ ��� ������� �� ������, �� ������� ��� �������������.";
        }
        catch (...) { cerr << "������ ����������!"; }
    };
}

// 7.2. ���������� �� ������� ���� �������������
template <typename Container>
function<void()> MenuObject::sort_buildings_by_avg_reconstruction_date(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� �� ������� ���� �������������." << endl << endl;
        try {
            if (Building::sort_buildings_by_avg_reconstruction_date(buildings))
                cout << "������ ������ ������� ������������.";
            else
                cout << "������ ������ �� ��� ������������. ��������, �� ������ ��� ������� �� ������, �� ������� ��� �������������.";
        }
        catch (...) { cerr << "������ ����������!"; }
    };
}

// 7.3. ���������� �� ������
template <typename Container>
function<void()> MenuObject::sort_buildings_by_height(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� �� ������." << endl << endl;
        try {
            if (Building::sort_buildings_by_height(buildings))
                cout << "������ ������ ������� ������������.";
            else
                cout << "������ ������ �� ��� ������������. ��������, �� ������.";
        }
        catch (...) { cerr << "������ ����������!"; }
    };
}

// 7.4. ���������� �� �������
template <typename Container>
function<void()> MenuObject::sort_buildings_by_square(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� �� �������." << endl << endl;
        try {
            if (Building::sort_buildings_by_square(buildings))
                cout << "������ ������ ������� ������������.";
            else
                cout << "������ ������ �� ��� ������������. ��������, �� ������.";
        }
        catch (...) { cerr << "������ ����������!"; }
    };
}

// 7.5. ���������� �� ������
template <typename Container>
function<void()> MenuObject::sort_buildings_by_volume(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� �� ������." << endl << endl;
        try {
            if (Building::sort_buildings_by_volume(buildings))
                cout << "������ ������ ������� ������������.";
            else
                cout << "������ ������ �� ��� ������������. ��������, �� ������.";
        }
        catch (...) { cerr << "������ ����������!"; }
    };
}

// 7.6. ���������� �� ���� ����������
template <typename Container>
function<void()> MenuObject::sort_buildings_by_all(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� �� ���� ����������." << endl << endl;
        try {
            if (Building::sort_buildings_by_all(buildings))
                cout << "������ ������ ������� ������������.";
            else
                cout << "������ ������ �� ��� ������������. ��������, �� ������.";
        }
        catch (...) { cerr << "������ ����������!"; }
    };
}

// 8. ����������� ���� ������
template <typename Container>
function<void()> MenuObject::combine_two_buildings(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "����������� ���� ������." << endl << endl;
        try {
            Building* building1_ptr = Building::choose_building_by_name_number(buildings, "�������� ������ ������.");
            if (building1_ptr == nullptr) return;
            cout << "������ ������ �������." << endl << endl;
            Building building1 = *building1_ptr;

            Building* building2_ptr;
            do {
                building2_ptr = Building::choose_building_by_name_number(buildings, "�������� ������ ������.");
                if (building1_ptr == building2_ptr)
                    cout << "������ ���������� ���� � �� �� ������!" << endl << endl;
            } while (building1_ptr == building2_ptr);
            if (building2_ptr == nullptr) return;
            cout << "������ ������ �������." << endl << endl;
            Building building2 = *building2_ptr;

            Building combined_building = building1 + building2;

            Building::delete_by_name(building1.get_name(), buildings);
            Building::delete_by_name(building2.get_name(), buildings);

            cout << static_cast<string>(combined_building) << endl << endl;

            buildings.push_back(move(combined_building));

            cout << "������ ������� ����������.";
        }
        catch (...) { cerr << "������ ����������� ������!"; }
    };
}

/* 9. ��������� ���������� ������: */
// 9.1. ��������
template <typename Container>
function<void()> MenuObject::change_building_name(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "��������� ��������." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                             return;

            Building& building = *building_ptr;

            cout << "������� ����� �������� ������." << endl << endl;

            string new_name;
            const string old_name = building.get_name();
            if (InputControl::input(new_name, "��������: "))         return;
            cout << endl;

            while (new_name == old_name) {
                if (InputControl::yes_or_no("����� �������� ������ ��������� �� ������. ����������?")) break;
                else {
                    if (InputControl::input(new_name, "��������: ")) return;
                    cout << endl;
                }
            }

            building.set_name(new_name);

            cout << "�������� ������� �������� \"" << old_name << "\" -> \"" << new_name << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ������� ��������!"; }
    };
}

/* 9.2. ������: */
// 9.2.1. ���������� �� 1
template <typename Container>
function<void()> MenuObject::increase_building_height_by_1(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� ������ �� 1." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            Building& building = *building_ptr;

            const int old_height = building.get_height();
            building++;
            const int new_height = building.get_height();

            cout << "������ ������ ������� �������� \"" << old_height << "\" -> \"" << new_height << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ���������� ������ �� 1!"; }
    };
}

// 9.2.2. ���������� �� �����
template <typename Container>
function<void()> MenuObject::increase_building_height_by_n(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� ������ �� �����." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                             return;

            Building& building = *building_ptr;

            int n;
            do {
                if (InputControl::input(n, "��������� ������ ��: ")) return;
                cout << endl;
                if (building.get_height() + n < 0) cout << "������ ������ �� ����� ���� ������ ����!" << endl << endl;
            } while (building.get_height() + n < 0);

            const int old_height = building.get_height();
            building += n;
            const int new_height = building.get_height();

            cout << "������ ������ ������� �������� \"" << old_height << "\" -> \"" << new_height << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ���������� ������ �� �����!"; }
    };
}

// 9.2.3. ���������� �� 1
template <typename Container>
function<void()> MenuObject::decrease_building_height_by_1(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� ������ �� 1." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            Building& building = *building_ptr;

            if (building.get_height() - 1 < 0) {
                cout << "������ ������ �� ����� ���� ������ ����!";
                return;
            }

            const int old_height = building.get_height();
            building--;
            const int new_height = building.get_height();

            cout << "������ ������ ������� �������� \"" << old_height << "\" -> \"" << new_height << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ���������� ������ �� 1!"; }
    };
}

// 9.2.4. ���������� �� �����
template <typename Container>
function<void()> MenuObject::decrease_building_height_by_n(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� ������ �� �����." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                             return;

            Building& building = *building_ptr;

            int n;
            do {
                if (InputControl::input(n, "��������� ������ ��: ")) return;
                cout << endl;
                if (building.get_height() - n < 0) cout << "������ ������ �� ����� ���� ������ ����!" << endl << endl;
            } while (building.get_height() - n < 0);

            const int old_height = building.get_height();
            building -= n;
            const int new_height = building.get_height();

            cout << "������ ������ ������� �������� \"" << old_height << "\" -> \"" << new_height << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ���������� ������ �� �����!"; }
    };
}

// 9.2.5. ������� ��������������
template <typename Container>
function<void()> MenuObject::change_building_height(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "������� ������ ��������������." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                                         return;

            Building& building = *building_ptr;

            int new_height;
            const int old_height = building.get_height();
            do {
                do {
                    if (InputControl::input(new_height, "�������� ������ ��: ")) return;
                    cout << endl;
                    if (new_height == old_height)
                        if (InputControl::yes_or_no("����� ������ ������ ��������� �� ������. ����������?")) break;
                } while (new_height == old_height);
                if (new_height < 0) cout << "������ ������ �� ����� ���� ������ ����!" << endl << endl;
            } while (new_height < 0);

            building.set_height(new_height);

            cout << "������ ������ ������� �������� \"" << old_height << "\" -> \"" << new_height << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ������� ������!"; }
    };
}

/* 9.3. �������: */
// 9.3.1. ���������� �� 1
template <typename Container>
function<void()> MenuObject::increase_building_square_by_1(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� ������� �� 1." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            Building& building = *building_ptr;

            const int old_square = building.get_square();
            building.set_square(building.get_square() + 1);
            const int new_square = building.get_square();

            cout << "������� ������ ������� �������� \"" << old_square << "\" -> \"" << new_square << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ���������� ������� �� 1!"; }
    };
}

// 9.3.2. ���������� �� �����
template <typename Container>
function<void()> MenuObject::increase_building_square_by_n(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� ������� �� �����." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                              return;

            Building& building = *building_ptr;

            int n;
            const int old_square = building.get_square();
            do {
                if (InputControl::input(n, "��������� ������� ��: ")) return;
                cout << endl;
                if (old_square + n < 0) cout << "������� ������ �� ����� ���� ������ ����!" << endl << endl;
            } while (old_square + n < 0);

            building.set_square(building.get_square() + n);
            const int new_square = building.get_square();

            cout << "������� ������ ������� �������� \"" << old_square << "\" -> \"" << new_square << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ���������� ������� �� �����!"; }
    };
}

// 9.3.3. ���������� �� 1
template <typename Container>
function<void()> MenuObject::decrease_building_square_by_1(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� ������� �� 1." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr) return;

            Building& building = *building_ptr;

            const int old_square = building.get_square();

            if (old_square - 1 < 0) {
                cout << "������� ������ �� ����� ���� ������ ����!" << endl << endl;
                return;
            }

            building.set_square(building.get_square() - 1);
            const int new_square = building.get_square();

            cout << "������� ������ ������� �������� \"" << old_square << "\" -> \"" << new_square << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ���������� ������� �� 1!"; }
    };
}

// 9.3.4. ���������� �� �����
template <typename Container>
function<void()> MenuObject::decrease_building_square_by_n(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� ������� �� �����." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                              return;

            Building& building = *building_ptr;

            int n;
            const int old_square = building.get_square();
            do {
                if (InputControl::input(n, "��������� ������� ��: ")) return;
                cout << endl;
                if (old_square - n < 0) cout << "������� ������ �� ����� ���� ������ ����!" << endl << endl;
            } while (old_square - n < 0);
            
            building.set_square(building.get_square() - n);
            const int new_square = building.get_square();

            cout << "������� ������ ������� �������� \"" << old_square << "\" -> \"" << new_square << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ���������� ������� �� �����!"; }
    };
}

// 9.3.5. ������� ��������������
template <typename Container>
function<void()> MenuObject::change_building_square(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "������� ������� ��������������." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                                          return;

            Building& building = *building_ptr;

            int new_square;
            const int old_square = building.get_square();
            do {
                do {
                    if (InputControl::input(new_square, "�������� ������� ��: ")) return;
                    cout << endl;
                    if (new_square == old_square)
                        if (InputControl::yes_or_no("����� ������� ������ ��������� �� ������. ����������?")) break;
                } while (new_square == old_square);
                if (new_square < 0) cout << "������� ������ �� ����� ���� ������ ����!" << endl << endl;
            } while (new_square < 0);

            building.set_square(new_square);

            cout << "������� ������ ������� �������� \"" << old_square << "\" -> \"" << new_square << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ������� �������!"; }
    };
}

/* 9.4. ������ ��� �������������: */
// 9.4.1. ���������� ����
template <typename Container>
function<void()> MenuObject::add_building_reconstruction_date(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���������� ����." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                              return;

            Building& building = *building_ptr;
            vector<int>& reconstruction_dates = building.get_reconstruction_dates_link();

            int year;
            if (InputControl::input(year, "�������� ���: ", 0, 2025)) return;
            cout << endl;

            reconstruction_dates.push_back(year);
            sort_container(reconstruction_dates);

            cout << "��� ������������� ������� �������� \"" << year << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ���������� ����!"; }
    };
}

// 9.4.2. ��������� ����
template <typename Container>
function<void()> MenuObject::edit_building_reconstruction_date(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "��������� ����." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                         return;

            Building& building = *building_ptr;

            int* current_year_ptr = Building::choose_reconstruction_date_by_year_number(building);
            if (current_year_ptr == nullptr)                     return;

            int& current_year = *current_year_ptr;

            int old_year = current_year;

            int new_year;
            if (InputControl::input(new_year, "�������� ���: ")) return;
            cout << endl;

            current_year = new_year;
            sort_container(building.get_reconstruction_dates_link());

            cout << "��� ������������� ������� ������ \"" << old_year << "\" -> \"" << current_year << "\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ��������� ����!"; }
    };
}

// 9.4.3. �������� ����
template <typename Container>
function<void()> MenuObject::delete_building_reconstruction_date(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "�������� ����." << endl << endl;
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

            cout << "��� ������������� ������� ����� \"" << year << "\" -> \"x\":" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ �������� ����!"; }
    };
}

// 9.4.4. ���� ������ ������
template <typename Container>
function<void()> MenuObject::change_building_reconstruction_dates(Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    return [&buildings]() {
        cout << "���� ��� ������." << endl << endl;
        try {
            Building* building_ptr = Building::choose_building_by_name_number(buildings);
            if (building_ptr == nullptr)                                        return;

            Building& building = *building_ptr;
            vector<int>& reconstruction_dates = building.get_reconstruction_dates_link();

            if (InputControl::input_reconstruction_dates(reconstruction_dates))	return;

            cout << "������ ��� ������������� ������� ������:" << endl << endl;
            cout << static_cast<string>(building);
        }
        catch (...) { cerr << "������ ������� ������ ��� �������������!"; }
    };
}

// ����� ����
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

// ��������� �������������� � ����
template <typename Container>
void MenuObject::process(const Container& menu, const string main_label, const string exit_label, int indent,
    enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>*) {
    int number;
    do {
        if (!main_label.empty()) cout << main_label << endl << endl;
        show_menu(menu, indent);
        cout << "0. " << exit_label << endl << endl << endl;
        if (InputControl::input(number, "����� ����: ", 0, static_cast<int>(menu.size()))) { cout << endl << endl << endl; continue; }
        cout << endl << endl;
        if (number == 0) break;
        try {
            auto it = find_if(menu.begin(), menu.end(), [number](MenuObject m) { return m.get_number() == number; });
            if (it != menu.end()) {
                if (it->get_submenu().empty())
                    (*it).act();
                else {
                    vector<MenuObject> submenu = it->get_submenu();
                    process(submenu, it->get_label(), "�����.", indent);
                    continue;
                }
            }
        }
        catch (const exception& e) {
            cout << "������: " << e.what();
        }
        cout << endl << endl << endl;
    } while (number != 0);
}

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_HPP