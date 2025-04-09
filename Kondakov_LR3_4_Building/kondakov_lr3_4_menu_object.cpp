#include "kondakov_lr3_4_menu_object.h"

// Конструктор с параметрами без подменю
MenuObject::MenuObject(int number,
                       string label,
                       function<void()> action)
                   : MenuObject(number, label, action, {}) {
}

// Конструктор с параметрами с подменю
MenuObject::MenuObject(int number,
                       string label,
                       vector<MenuObject> submenu)
                   : MenuObject(number, label, nullptr, submenu) {
}

// Конструктор с параметрами полный
MenuObject::MenuObject(int number,
                       string label,
                       function<void()> action,
                       vector<MenuObject> submenu)
                   : number(number),
                     label(label),
                     action(action),
                     submenu(submenu) {
}

// Конструктор перемещения
MenuObject::MenuObject(MenuObject&& other) noexcept
                   : number(exchange(other.number, 0)),
                     label(move(other.label)),
                     action(move(other.action)) {
}

// Получение даты из контейнера по номеру даты из списка
int* Building::choose_reconstruction_date_by_year_number(Building& building) {
	vector<int>& reconstruction_dates = building.get_reconstruction_dates_link();
	map<int, int> years_map = get_numbered_map(reconstruction_dates);
	cout << years_map << endl << endl;

	int choice;
	int* year_ptr = nullptr;

	cout << "Выберите год из списка." << endl << endl;
	if (InputControl::input(choice, "Номер года: ", 1, static_cast<int>(years_map.size()))) return year_ptr;
	cout << endl;

	auto it = years_map.find(choice);
	if (it == years_map.end()) {
		cout << "Года с таким номером не найдено.";
		return year_ptr;
	}
	else {
		try {
			year_ptr = &reconstruction_dates[choice - 1];
			cout << "Год: \"" << *year_ptr << "\"" << endl << endl;
			return year_ptr;
		}
		catch (...) {
			cout << "Ошибка при получении года по номеру.";
			return year_ptr;
		}
	}
}