#include "kondakov_lr3_4_menu_object.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    const string filename = "buildings.bin";
    vector<Building> buildings = LoadModule::get_buildings_from_binary_file(filename);
    vector<MenuObject> menu {
        { 1, "Вывести список зданий;", MenuObject::print_buildings(buildings)},
        { 2, "Загрузить данные из бинарного файла;", MenuObject::load_buildings(buildings, filename) },
        { 3, "Добавить здание в список;", MenuObject::add_building(buildings) },
        { 4, "Удалить здание из списка;", MenuObject::delete_building(buildings) },
        { 5, "Сохранить данные в бинарный файл;", MenuObject::save_buildings(buildings, filename) },
        { 6, "Найти здание по названию;", MenuObject::find_building_by_name(buildings) },
        { 7, "Отсортировать список зданий по последнему году их реконструкции;", MenuObject::sort_buildings_by_reconstruction_dates(buildings) },
        { 8, "Объединить два здания.", MenuObject::combine_two_buildings(buildings) }
    };

    int number;
    bool escape = false;
    
    do {
        MenuObject::show_menu(menu);
        InputControl::enter_number(number, escape, "Пункт меню: ", 0, static_cast<int>(menu.size()));
        cout << endl << endl;
        if (escape) { escape = false; continue; }
        try {
            auto it = find_if(menu.begin(), menu.end(), [number](MenuObject m) { return m.get_number() == number; });
            if (it != menu.end())
                (*it).act();
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what();
        }
        cout << endl << endl << endl;
    } while (number);

    cout << "© 2025 Fedor Kondakov" << endl;

    return 0;
}