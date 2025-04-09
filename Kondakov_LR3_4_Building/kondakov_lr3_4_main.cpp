#include "kondakov_lr3_4_menu_object.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    const string filename = "buildings.bin";
    vector<Building> buildings = LoadModule::get_buildings_from_binary_file(filename);
    vector<MenuObject> menu {
        { 1, "Вывести список зданий;", MenuObject::print_buildings(buildings) },
        { 2, "Загрузить данные из бинарного файла;", MenuObject::load_buildings(buildings, filename) },
        { 3, "Добавить здание в список;", MenuObject::add_building(buildings) },
        { 4, "Удалить здание из списка;", MenuObject::delete_building(buildings) },
        { 5, "Сохранить данные в бинарный файл;", MenuObject::save_buildings(buildings, filename) },
        { 6, "Найти здание по названию;", MenuObject::find_building_by_name(buildings) },
        { 7, "Отсортировать список зданий:", {
            { 1, "Отсортировать по последнему году их реконструкции;", MenuObject::sort_buildings_by_reconstruction_dates(buildings) },
            { 2, "Отсортировать по средней дате реконструкции;", MenuObject::sort_buildings_by_avg_reconstruction_date(buildings) },
            { 3, "Отсортировать по высоте;", MenuObject::sort_buildings_by_height(buildings) },
            { 4, "Отсортировать по площади;", MenuObject::sort_buildings_by_square(buildings) },
            { 5, "Отсортировать по объёму;", MenuObject::sort_buildings_by_volume(buildings) },
            { 6, "Отсортировать по всем параметрам.", MenuObject::sort_buildings_by_all(buildings) } }
        },
        { 8, "Объединить два здания;", MenuObject::combine_two_buildings(buildings) },
        { 9, "Изменить параметры здания:", {
            { 1, "Изменить название;", MenuObject::change_building_name(buildings) },
            { 2, "Изменить высоту:", {
                { 1, "Увеличить на 1;", MenuObject::increase_building_height_by_1(buildings) },
                { 2, "Увеличить на число;", MenuObject::increase_building_height_by_n(buildings) },
                { 3, "Уменьшить на 1;", MenuObject::decrease_building_height_by_1(buildings) },
                { 4, "Уменьшить на число;", MenuObject::decrease_building_height_by_n(buildings) },
                { 5, "Задать самостоятельно.", MenuObject::change_building_height(buildings) } }
            },
            { 3, "Изменить площадь:", {
                { 1, "Увеличить на 1;", MenuObject::increase_building_square_by_1(buildings) },
                { 2, "Увеличить на число;", MenuObject::increase_building_square_by_n(buildings) },
                { 3, "Уменьшить на 1;", MenuObject::decrease_building_square_by_1(buildings) },
                { 4, "Уменьшить на число;", MenuObject::decrease_building_square_by_n(buildings) },
                { 5, "Задать самостоятельно.", MenuObject::change_building_square(buildings) } }
            },
            { 4, "Изменить список дат реконструкции:", {
                { 1, "Добавить дату;", MenuObject::add_building_reconstruction_date(buildings) },
                { 2, "Изменить дату;", MenuObject::edit_building_reconstruction_date(buildings) },
                { 3, "Удалить дату;", MenuObject::delete_building_reconstruction_date(buildings) },
                { 4, "Ввести даты заново.", MenuObject::change_building_reconstruction_dates(buildings) } }
            } }
        }
    };

    MenuObject::process(menu, "Главное меню:", "Выход.");

    cout << "© 2025 Fedor Kondakov" << endl;

    return 0;
}