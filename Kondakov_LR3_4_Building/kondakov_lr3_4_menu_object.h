#ifndef KONDAKOV_LR3_4_MENU_OBJECT_H
#define KONDAKOV_LR3_4_MENU_OBJECT_H

#include "kondakov_lr3_4_load_module.h"

class MenuObject {
private:
    // ��������� ����
    int number;
    string label;
    function<void()> action;

public:
    MenuObject() = delete;

    MenuObject(int number,
               string label,
               function<void()> action);

    MenuObject(const MenuObject& menu_object) = default;

    ~MenuObject() = default;

    // ����� ������ ����
    inline void show() const;

    // ��������� �������
    inline void act() const;

    // ������ ������ ������
    inline int get_number() const;

    // ����� ���������� � �������
    template <typename Container>
    static function<void()> print_buildings(const Container& buildings, const string& separator = "\n",
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // �������� ������ � �������
    template <typename Container>
    static function<void()> load_buildings(Container& buildings, const string& filename,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // ���������� ������
    template <typename Container>
    static function<void()> add_building(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // �������� ������
    template <typename Container>
    static function<void()> delete_building (Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // ���������� ������ � �������
    template <typename Container>
    static function<void()> save_buildings(const Container& buildings, const string& filename,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // ����� �� �������� ������
    template <typename Container>
    static function<void()> find_building_by_name (Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // ���������� �� ���������� ���� �������������
    template <typename Container>
    static function<void()> sort_buildings_by_reconstruction_dates(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // ����������� ���� ������
    template <typename Container>
    static function<void()> combine_two_buildings(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // ����� ����
    template <typename Container>
    static void show_menu(const Container& menu,
        enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>* = 0);
};

#include "kondakov_lr3_4_menu_object.hpp"

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_H