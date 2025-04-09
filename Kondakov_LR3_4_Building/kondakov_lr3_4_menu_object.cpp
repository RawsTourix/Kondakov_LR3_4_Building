#include "kondakov_lr3_4_menu_object.h"

// ����������� � ����������� ��� �������
MenuObject::MenuObject(int number,
                       string label,
                       function<void()> action)
                   : MenuObject(number, label, action, {}) {
}

// ����������� � ����������� � �������
MenuObject::MenuObject(int number,
                       string label,
                       vector<MenuObject> submenu)
                   : MenuObject(number, label, nullptr, submenu) {
}

// ����������� � ����������� ������
MenuObject::MenuObject(int number,
                       string label,
                       function<void()> action,
                       vector<MenuObject> submenu)
                   : number(number),
                     label(label),
                     action(action),
                     submenu(submenu) {
}

// ����������� �����������
MenuObject::MenuObject(MenuObject&& other) noexcept
                   : number(exchange(other.number, 0)),
                     label(move(other.label)),
                     action(move(other.action)) {
}

// ��������� ���� �� ���������� �� ������ ���� �� ������
int* Building::choose_reconstruction_date_by_year_number(Building& building) {
	vector<int>& reconstruction_dates = building.get_reconstruction_dates_link();
	map<int, int> years_map = get_numbered_map(reconstruction_dates);
	cout << years_map << endl << endl;

	int choice;
	int* year_ptr = nullptr;

	cout << "�������� ��� �� ������." << endl << endl;
	if (InputControl::input(choice, "����� ����: ", 1, static_cast<int>(years_map.size()))) return year_ptr;
	cout << endl;

	auto it = years_map.find(choice);
	if (it == years_map.end()) {
		cout << "���� � ����� ������� �� �������.";
		return year_ptr;
	}
	else {
		try {
			year_ptr = &reconstruction_dates[choice - 1];
			cout << "���: \"" << *year_ptr << "\"" << endl << endl;
			return year_ptr;
		}
		catch (...) {
			cout << "������ ��� ��������� ���� �� ������.";
			return year_ptr;
		}
	}
}