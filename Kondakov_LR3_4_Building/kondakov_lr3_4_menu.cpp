#include "kondakov_lr3_4_menu.h"

// Меню
// // Вывод информации о зданиях
template <typename Iterator>
function<void()> Menu::print_buildings(Iterator begin, Iterator end, const string& separator) {
    cout << Building::buildings_to_string(begin, end, separator);
}

// Сохранение данных о зданиях
template <typename Iterator>
function<void()> Menu::save_buildings(Iterator begin, Iterator end, const string& filename) {
    return [&]() {
        bool saved = SaveModule::save_buildings_to_bin(begin, end, filename);
        if (saved)
            cout << "Данные о зданиях успешно записаны.";
        else
            cout << "Ошибка записи данных о зданиях в файл!";
    };
}