#include "kondakov_lr3_4_save_module.h"

// Преобразовать список зданий в строку удобную для сохранения в файл
template <typename Iterator>
string SaveModule::parse_buildings_to_save(Iterator begin, Iterator end, const string& separator) {
    if (begin == end) return "";

    string result = begin->get_name() + separator +
        begin->get_height_as_str() + separator +
        begin->get_square_as_str() + separator +
        begin->get_volume_as_str() + separator +
        begin->get_reconstruction_dates_as_str() + separator;

    ++begin;

    while (begin != end) {
        result += "\n" + begin->get_name() + separator +
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
bool SaveModule::save_buildings_to_bin(Iterator begin, Iterator end, const string& filename) {
    string buildings_data = parse_buildings_to_save(begin, end);

    ofstream file(filename, ios::binary);
    if (file.is_open()) {
        try {
            file.write(buildings_data.c_str(), buildings_data.size());
            file.close();
            return true;
        }
        catch (...) { file.close(); }
    }
    return false;
}