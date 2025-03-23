#ifndef KONDAKOV_LR3_4_SAVE_MODULE_HPP
#define KONDAKOV_LR3_4_SAVE_MODULE_HPP

#include "kondakov_lr3_4_save_module.h"

// Преобразовать список зданий в строку удобную для сохранения в файл
template <typename Iterator>
string SaveModule::parse_buildings_to_save(Iterator begin, Iterator end,
    enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
    if (begin == end) return "";

    const string separator = "\n";

    string result;

    while (begin != end) {
        result += begin->get_name() + separator +
            begin->get_height_as_str() + separator +
            begin->get_square_as_str() + separator +
            begin->get_volume_as_str() + separator +
            begin->get_reconstruction_dates_as_str() + separator;

        ++begin;
    }

    return result;
}

// Загрузка данных о зданиях в бинарный файл
template <typename Iterator>
bool SaveModule::save_buildings_to_bin(Iterator begin, Iterator end, const string& filename,
    enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
    string buildings_data = parse_buildings_to_save(begin, end);

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