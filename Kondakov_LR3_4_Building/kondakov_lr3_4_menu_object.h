#ifndef KONDAKOV_LR3_4_MENU_OBJECT_H
#define KONDAKOV_LR3_4_MENU_OBJECT_H

#include "kondakov_lr3_4_load_module.h"

class MenuObject {
private:
    // Структура меню
    int number;
    string label;
    function<void()> action;
    vector<MenuObject> submenu {};

public:
    // Конструктор по умолчанию
    MenuObject() = delete;

    // Конструктор с параметрами без подменю
    MenuObject(int number,
               string label,
               function<void()> action);

    // Конструктор с параметрами с подменю
    MenuObject(int number,
        string label,
        vector<MenuObject> submenu);

    // Конструктор с параметрами полный
    MenuObject(int number,
        string label,
        function<void()> action,
        vector<MenuObject> submenu);

    // Конструктор копирования
    MenuObject(const MenuObject&) = default;
    MenuObject& operator=(const MenuObject&) = default;

    // Конструктор пепремещения
    MenuObject(MenuObject&& menu_object) noexcept;
    MenuObject& operator=(MenuObject&&) = default;

    // Деструктор
    ~MenuObject() = default;

    // Вывод пункта меню
    inline void show(const string& indentation = "") const;

    // Выполнить функцию
    inline void act() const;

    // Геттер названия пункта
    inline string get_label() const;

    // Геттер номера пункта
    inline int get_number() const;

    // Геттер полного названия пункта
    inline string get_full_name() const;

    // Геттер подменю
    inline const vector<MenuObject>& get_submenu() const;

    // 1. Вывод информации о зданиях
    template <typename Container>
    static function<void()> print_buildings(const Container& buildings, const string& separator = "\n\n",
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 2. Загрузка данных о зданиях
    template <typename Container>
    static function<void()> load_buildings(Container& buildings, const string& filename,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 3. Добавление здания
    template <typename Container>
    static function<void()> add_building(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 4. Удаление здания
    template <typename Container>
    static function<void()> delete_building (Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 5. Сохранение данных о зданиях
    template <typename Container>
    static function<void()> save_buildings(const Container& buildings, const string& filename,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 6. Поиск по названию здания
    template <typename Container>
    static function<void()> find_building_by_name (Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    /* 7. Сортировка: */
    // 7.1. По последнему году реконструкции
    template <typename Container>
    static function<void()> sort_buildings_by_reconstruction_dates(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 7.2. По средней дате реконструкции
    template <typename Container>
    static function<void()> sort_buildings_by_avg_reconstruction_date(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 7.3. Отсортировка списка зданий по высоте
    template <typename Container>
    static function<void()> sort_buildings_by_height(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 7.4. Отсортировка списка зданий по площади
    template <typename Container>
    static function<void()> sort_buildings_by_square(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 7.5. Отсортировка списка зданий по объёму
    template <typename Container>
    static function<void()> sort_buildings_by_volume(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 7.6. Отсортировка списка зданий по всем параметрам
    template <typename Container>
    static function<void()> sort_buildings_by_all(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 8. Объединение двух зданий
    template <typename Container>
    static function<void()> combine_two_buildings(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    /* 9. Изменение параметров здания: */
    // 9.1. Названия
    template <typename Container>
    static function<void()> change_building_name(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    /* 9.2. Высоты: */
    // 9.2.1. Увеличение на 1
    template <typename Container>
    static function<void()> increase_building_height_by_1(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.2.2. Увеличение на число
    template <typename Container>
    static function<void()> increase_building_height_by_n(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.2.3. Уменьшение на 1
    template <typename Container>
    static function<void()> decrease_building_height_by_1(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.2.4. Уменьшение на число
    template <typename Container>
    static function<void()> decrease_building_height_by_n(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.2.5. Задание самостоятельно
    template <typename Container>
    static function<void()> change_building_height(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    /* 9.3. Площади: */
    // 9.3.1. Увеличение на 1
    template <typename Container>
    static function<void()> increase_building_square_by_1(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.3.2. Увеличение на число
    template <typename Container>
    static function<void()> increase_building_square_by_n(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.3.3. Уменьшение на 1
    template <typename Container>
    static function<void()> decrease_building_square_by_1(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.3.4. Уменьшение на число
    template <typename Container>
    static function<void()> decrease_building_square_by_n(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.3.5. Задание самостоятельно
    template <typename Container>
    static function<void()> change_building_square(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    /* 9.4. Списка дат реконструкции: */
    // 9.4.1. Добавление даты
    template <typename Container>
    static function<void()> add_building_reconstruction_date(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.4.2. Изменение даты
    template <typename Container>
    static function<void()> edit_building_reconstruction_date(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.4.3. Удаление даты
    template <typename Container>
    static function<void()> delete_building_reconstruction_date(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // 9.4.4. Ввод списка заново
    template <typename Container>
    static function<void()> change_building_reconstruction_dates(Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // Вывод меню
    template <typename Container>
    static void show_menu(const Container& menu, int indent,
        enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>* = 0);

    // Обработка взаимодействия с меню
    template <typename Container>
    static void process(const Container& menu, const string main_label = "", const string exit_label = "", int indent = 0,
        enable_if_t<is_same_v<typename Container::value_type, MenuObject>, int>* = 0);
};

#include "kondakov_lr3_4_menu_object.hpp"

#endif // !KONDAKOV_LR3_4_MENU_OBJECT_H