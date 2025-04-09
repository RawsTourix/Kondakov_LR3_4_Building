#ifndef KONDAKOV_LR3_4_INPUT_CONTROL_HPP
#define KONDAKOV_LR3_4_INPUT_CONTROL_HPP

#include "kondakov_lr3_4_input_control.h"

// Ввод для чисел
template <typename T>
bool InputControl::input(T& varLink, const string& label, T min, T max,
	enable_if_t<is_same_v<typename T, int> ||
				is_same_v<typename T, float>, int>*) {
	string raw_input;
	bool constexpr T_int = is_same_v<T, int>;
	bool constexpr T_float = is_same_v<T, float>;

	do {
		cout << label;
		getline(cin, raw_input);
		trim(raw_input);
		if (is_input_empty(raw_input)) return true;  // отмена операции
	} while (T_int ? !is_int(raw_input, min, max) :
			 T_float ? !is_float(raw_input, min, max) : false);

	varLink = T_int ? stoi(raw_input) :
			  T_float ? stof(raw_input) : 0;

	return false;  // продолжение операции
}

// Ввод дат реконструкции
template <typename Container>
bool InputControl::input_reconstruction_dates(Container& reconstruction_dates, int min, int max,
	enable_if_t<is_same_v<typename Container::value_type, int>, int>*) {
	int years;
	vector<int> new_reconstruction_dates {};
	if (input(years, "Количество\nреконструкций: ", min, max))	return true;  // Отмена операции
	cout << endl;

	// Добавление дат реконструкции
	for (int i = 1; i <= years; i++) {
		int year;
		ostringstream label;
		label << i << " год: ";
		if (InputControl::input(year, label.str(), 0, 2025))	return true;  // Отмена операции
		new_reconstruction_dates.push_back(year);
	}
	cout << endl;

	sort_container(new_reconstruction_dates);
	reconstruction_dates.assign(new_reconstruction_dates.begin(), new_reconstruction_dates.end());

	return false;  // Продолжение операции
}

#endif; // !KONDAKOV_LR3_4_INPUT_CONTROL_HPP