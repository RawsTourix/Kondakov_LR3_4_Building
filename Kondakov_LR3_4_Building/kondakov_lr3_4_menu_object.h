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

    // ����� ���������� � �������
    template <typename Iterator>
    static function<void()> print_buildings(Iterator begin, Iterator end, const string& separator = "\n",
        enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>* = 0);

    // �������� ������ � �������
    template <typename Container>
    static function<void()> load_buildings(Container& buildings, const string& filename,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // ���������� ������
    template <typename Container>
    static function<void()> add_building(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // ���������� ������ � �������
    template <typename Iterator>
    static function<void()> save_buildings(Iterator begin, Iterator end, const string& filename,
        enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>* = 0);
};

#include "kondakov_lr3_4_menu_object.hpp"

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_H