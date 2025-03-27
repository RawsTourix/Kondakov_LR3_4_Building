#ifndef KONDAKOV_LR3_4_SAVE_MODULE_H
#define KONDAKOV_LR3_4_SAVE_MODULE_H

#include "kondakov_lr3_4_building.h"

class SaveModule {
public:
    // Преобразовать список зданий в строку удобную для сохранения в файл
    template <typename Container>
    static string parse_buildings_to_save(const Container& buildings,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

    // Загрузка данных о зданиях в бинарный файл
    template <typename Container>
    static bool save_buildings_to_bin(const Container& buildings, const string& filename,
        enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);
};

#include "kondakov_lr3_4_save_module.hpp"

#endif // !KONDAKOV_LR3_4_SAVE_MODULE_H