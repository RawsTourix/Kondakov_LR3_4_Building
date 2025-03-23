#ifndef KONDAKOV_LR3_4_SAVE_MODULE_H
#define KONDAKOV_LR3_4_SAVE_MODULE_H

#include "kondakov_lr3_4_building.h"

class SaveModule {
public:
    // Преобразовать список зданий в строку удобную для сохранения в файл
    template <typename Iterator>
    static string parse_buildings_to_save(Iterator begin, Iterator end,
        enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>* = 0);

    // Загрузка данных о зданиях в бинарный файл
    template <typename Iterator>
    static bool save_buildings_to_bin(Iterator begin, Iterator end, const string& filename,
        enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>* = 0);
};

#include "kondakov_lr3_4_save_module.hpp"

#endif // !KONDAKOV_LR3_4_SAVE_MODULE_H