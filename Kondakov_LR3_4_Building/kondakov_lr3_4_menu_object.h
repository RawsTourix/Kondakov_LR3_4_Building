#ifndef KONDAKOV_LR3_4_MENU_OBJECT_H
#define KONDAKOV_LR3_4_MENU_OBJECT_H

#include "kondakov_lr3_4_load_module.h"

class MenuObject {
private:
    // ��������� ����
    int number;
    string label;
    function<void()> action;
    vector<MenuObject> submenu {};

public:
    // ����������� �� ���������
    MenuObject() = delete;

    // ����������� � ����������� ��� �������
    MenuObject(int number,
               string label,
               function<void()> action);

    // ����������� � ����������� � �������
    MenuObject(int number,
        string label,
        vector<MenuObject> submenu);

    // ����������� � ����������� ������
    MenuObject(int number,
        string label,
        function<void()> action,
        vector<MenuObject> submenu);

    // ����������� �����������
    MenuObject(const MenuObject&) = default;
    MenuObject& operator=(const MenuObject&) = default;

    // ����������� ������������
    MenuObject(MenuObject&& menu_object) noexcept;
    MenuObject& operator=(MenuObject&&) = default;

    // ����������
    ~MenuObject() = default;

    // ����� ������ ����
    inline void show(const string& indentation = "") const;

    // ��������� �������
    inline void act() const;

    // ������ �������� ������
    inline string get_label() const;

    // ������ ������ ������
    inline int get_number() const;

    // ������ ������� �������� ������
    inline string get_full_name() const;

    // ������ �������
    inline const vector<MenuObject>& get_submenu() const;

    // 1. ����� ���������� � �������
    template <typename Container>
    static function<void()> print_buildings(const Container& buildings, const string& separator = "\n\n",
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 2. �������� ������ � �������
    template <typename Container>
    static function<void()> load_buildings(Container& buildings, const string& filename,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 3. ���������� ������
    template <typename Container>
    static function<void()> add_building(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 4. �������� ������
    template <typename Container>
    static function<void()> delete_building (Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 5. ���������� ������ � �������
    template <typename Container>
    static function<void()> save_buildings(const Container& buildings, const string& filename,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 6. ����� �� �������� ������
    template <typename Container>
    static function<void()> find_building_by_name (Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    /* 7. ����������: */
    // 7.1. �� ���������� ���� �������������
    template <typename Container>
    static function<void()> sort_buildings_by_reconstruction_dates(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 7.2. �� ������� ���� �������������
    template <typename Container>
    static function<void()> sort_buildings_by_avg_reconstruction_date(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 7.3. ������������ ������ ������ �� ������
    template <typename Container>
    static function<void()> sort_buildings_by_height(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 7.4. ������������ ������ ������ �� �������
    template <typename Container>
    static function<void()> sort_buildings_by_square(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 7.5. ������������ ������ ������ �� ������
    template <typename Container>
    static function<void()> sort_buildings_by_volume(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 7.6. ������������ ������ ������ �� ���� ����������
    template <typename Container>
    static function<void()> sort_buildings_by_all(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 8. ����������� ���� ������
    template <typename Container>
    static function<void()> combine_two_buildings(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    /* 9. ��������� ���������� ������: */
    // 9.1. ��������
    template <typename Container>
    static function<void()> change_building_name(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    /* 9.2. ������: */
    // 9.2.1. ���������� �� 1
    template <typename Container>
    static function<void()> increase_building_height_by_1(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.2.2. ���������� �� �����
    template <typename Container>
    static function<void()> increase_building_height_by_n(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.2.3. ���������� �� 1
    template <typename Container>
    static function<void()> decrease_building_height_by_1(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.2.4. ���������� �� �����
    template <typename Container>
    static function<void()> decrease_building_height_by_n(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.2.5. ������� ��������������
    template <typename Container>
    static function<void()> change_building_height(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    /* 9.3. �������: */
    // 9.3.1. ���������� �� 1
    template <typename Container>
    static function<void()> increase_building_square_by_1(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.3.2. ���������� �� �����
    template <typename Container>
    static function<void()> increase_building_square_by_n(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.3.3. ���������� �� 1
    template <typename Container>
    static function<void()> decrease_building_square_by_1(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.3.4. ���������� �� �����
    template <typename Container>
    static function<void()> decrease_building_square_by_n(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.3.5. ������� ��������������
    template <typename Container>
    static function<void()> change_building_square(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    /* 9.4. ������ ��� �������������: */
    // 9.4.1. ���������� ����
    template <typename Container>
    static function<void()> add_building_reconstruction_date(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.4.2. ��������� ����
    template <typename Container>
    static function<void()> edit_building_reconstruction_date(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.4.3. �������� ����
    template <typename Container>
    static function<void()> delete_building_reconstruction_date(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.4.4. ���� ������ ������
    template <typename Container>
    static function<void()> change_building_reconstruction_dates(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // ����� ����
    template <typename Container>
    static void show_menu(const Container& menu, int indent,
        enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>* = 0);

    // ��������� �������������� � ����
    template <typename Container>
    static void process(const Container& menu, const string main_label = "", const string exit_label = "", int indent = 0,
        enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>* = 0);
};

#include "kondakov_lr3_4_menu_object.hpp"

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_H