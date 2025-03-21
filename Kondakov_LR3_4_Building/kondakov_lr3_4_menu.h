#ifndef KONDAKOV_LR3_4_MENU_H
#define KONDAKOV_LR3_4_MENU_H

#include "kondakov_lr3_4_save_module.h"
#include "kondakov_lr3_4_load_module.h"

class Menu {
private:

public:
    // Вывод информации о зданиях
    template <typename Iterator>
    function<void()> print_buildings(Iterator begin, Iterator end, const string& separator = "\n");

    // Сохранение данных о зданиях
    template <typename Iterator>
    static function<void()> save_buildings(Iterator begin, Iterator end, const string& filename);
};

#endif // !KONDAKOV_LR3_4_MENU_H