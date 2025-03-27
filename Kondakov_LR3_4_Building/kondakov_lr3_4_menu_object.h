#ifndef KONDAKOV_LR3_4_MENU_OBJECT_H
#define KONDAKOV_LR3_4_MENU_OBJECT_H

#include "kondakov_lr3_4_load_module.h"

class MenuObject {
private:
    // Структура меню
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

    // Вывод пункта меню
    inline void show() const;

    // Выполнить функцию
    inline void act() const;

    // Геттер номера пункта
    inline int get_number() const;

    // Вывод информации о зданиях
    template <typename Container>
    static function<void()> print_buildings(const Container& buildings, const string& separator = "\n",
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // Загрузка данных о зданиях
    template <typename Container>
    static function<void()> load_buildings(Container& buildings, const string& filename,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // Добавление здания
    template <typename Container>
    static function<void()> add_building(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // Удаление здания
    template <typename Container>
    static function<void()> delete_building (Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // Сохранение данных о зданиях
    template <typename Container>
    static function<void()> save_buildings(const Container& buildings, const string& filename,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // Поиск по названию здания
    template <typename Container>
    static function<void()> find_building_by_name (Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // Сортировка по последнему году реконструкции
    template <typename Container>
    static function<void()> sort_buildings_by_reconstruction_dates(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // Объединение двух зданий
    template <typename Container>
    static function<void()> combine_two_buildings(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // Вывод меню
    template <typename Container>
    static void show_menu(const Container& menu,
        enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>* = 0);
};

#include "kondakov_lr3_4_menu_object.hpp"

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_H