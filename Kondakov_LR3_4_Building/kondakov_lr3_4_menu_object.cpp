#include "kondakov_lr3_4_menu_object.h"

MenuObject::MenuObject(int number,
                       string label,
                       function<void()> action)
                  :  number(number),
                     label(label),
                     action(action) {
}

// Вывод пункта меню
inline void MenuObject::show() const {
    cout << number << ") " << label << endl;
}