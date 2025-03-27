#ifndef KONDAKOV_LR3_4_SAVE_MODULE_HPP
#define KONDAKOV_LR3_4_SAVE_MODULE_HPP

#include "kondakov_lr3_4_save_module.h"

// Преобразоване списка зданий в строку удобную для сохранения в файл
template <typename Container>
string SaveModule::parse_buildings_to_save(const Container& buildings,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    if (buildings.empty()) return "";

    const string separator = "\n";

    string result;

    for (const auto& building : buildings) {
        result += building.get_name() + separator +
                  building.get_height_as_str() + separator +
                  building.get_square_as_str() + separator +
                  building.get_volume_as_str() + separator +
                  building.get_reconstruction_dates_as_str(",") + separator;
    }

    return result;
}

// Загрузка данных о зданиях в бинарный файл
template <typename Container>
bool SaveModule::save_buildings_to_bin(const Container& buildings, const string& filename,
    enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
    string buildings_data = parse_buildings_to_save(buildings);

    ofstream file(filename, ios::binary | ios::out | ios::trunc);
    if (file.is_open()) {
        try {
            file.write(buildings_data.c_str(), buildings_data.size());
            file.close();
            return true;
        }
        catch (...) { return false; }
    }
    else
        return false;
}

#endif // !KONDAKOV_LR3_4_SAVE_MODULE_HPP