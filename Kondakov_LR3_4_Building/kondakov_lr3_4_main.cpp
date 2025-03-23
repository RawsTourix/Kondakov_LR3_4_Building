#include "kondakov_lr3_4_menu_object.h"

int main()
{
    const string filename = "buildings.bin";
    vector<Building> buildings = LoadModule::get_buildings_from_binary_file(filename);
    vector<MenuObject> menu = {
        { 1, "Вывести список зданий;", MenuObject::print_buildings(buildings.begin(), buildings.end()) },
        { 2, "Загрузить данные из бинарного файла", MenuObject::load_buildings(buildings, filename) },
        { 3, "Добавить здание;", MenuObject::add_building(buildings) },
    };

    return 0;
}