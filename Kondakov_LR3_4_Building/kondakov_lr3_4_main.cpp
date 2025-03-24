#include "kondakov_lr3_4_menu_object.h"

int main()
{
    const string filename = "buildings.bin";
    vector<Building> buildings = LoadModule::get_buildings_from_binary_file(filename);
    vector<MenuObject> menu = {
        { 1, "Вывести список зданий;", MenuObject::print_buildings(buildings.begin(), buildings.end()) },
        { 2, "Загрузить данные из бинарного файла", MenuObject::load_buildings(buildings, filename) },
        { 3, "Добавить здание в список;", MenuObject::add_building(buildings) },
        { 4, "Удалить здание из списка;", MenuObject::delete_building(buildings) },
        { 5, "Сохранить данные в бинарный файл;", MenuObject::save_buildings(buildings.begin(), buildings.end(), filename) },
        { 6, "Найти здание по названию;", MenuObject::find_building_by_name(buildings) },
        { 7, "Отсортировать список зданий по последнему году их реконструкции;", MenuObject::sort_buildings_by_reconstruction_dates(buildings.begin(), buildings.end()) },
        { 8, "Объединить два здания.", MenuObject::combine_two_buildings(buildings) }
    };

    return 0;
}