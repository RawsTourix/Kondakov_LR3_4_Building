#include "kondakov_lr3_4_input_control.h"

// Удаление пробелов вначале и в конце (trim)
void InputControl::trim(string& str) {
	// Удаляем пробелы с начала
	while (!str.empty() && str.front() == ' ')
		str.erase(str.begin());

	// Удаляем пробелы с конца
	while (!str.empty() && str.back() == ' ')
		str.pop_back();
}

// Проверка на пустой ввод для отмены операции
bool InputControl::is_input_empty(const string& input) {
	if (input.empty()) {
		cout << endl << "[Отмена операции]";
		return true;
	}
	return false;
}

// Проверка конвертации в int
bool InputControl::is_int(const string& input, int min, int max) {
	try {
		int number = stoi(input);
		if (input.size() > to_string(number).size()) throw invalid_argument("input содержит недопустимые символы.");
		if (number < min) { cout << endl << "Вы ввели \"" << number << "\" — значение должно быть не меньше \"" << min << "\"" << endl << endl; return false; }
		if (number > max) { cout << endl << "Вы ввели \"" << number << "\" — значение должно быть не больше \"" << max << "\"" << endl << endl; return false; }
	}
	catch (const invalid_argument&) {
		cerr << endl << "Введённое значение \"" << input << "\" не является числом!" << endl << endl;
		return false;
	}
	catch (const out_of_range&) {
		cerr << endl << "Число \"" << input << "\" выходит за допустимый диапазон!" << endl << endl;
		return false;
	}
	return true;
}

// Проверка конвертации в float
bool InputControl::is_float(const string& input, float min, float max) {
	try {
		float number = stof(input);
		if (input.size() > to_string(number).size()) throw invalid_argument("input содержит недопустимые символы.");
		if (number < min) { cout << endl << "Вы ввели \"" << number << "\" — значение должно быть не меньше \"" << min << "\"" << endl << endl; return false; }
		if (number > max) { cout << endl << "Вы ввели \"" << number << "\" — значение должно быть не больше \"" << max << "\"" << endl << endl; return false; }
	}
	catch (const invalid_argument&) {
		cerr << endl << "Введённое вами значение \"" << input << "\" не является числом!" << endl << endl;
		return false;
	}
	catch (const out_of_range&) {
		cerr << endl << "Число \"" << input << "\" выходит за допустимый диапазон!" << endl << endl;
		return false;
	}
	return true;
}

// Ввод для строк
bool InputControl::input(string& varLink, const string& label) {
	string raw_input;

	cout << label;
	getline(cin, raw_input);
	trim(raw_input);
	if (is_input_empty(raw_input))
		return true;   // отмена операции
	else {
		varLink = raw_input;
		return false;  // продолжение операции
	}
}

// Возвращает один символ
char InputControl::get_char() {
	char ch;
	cin >> ch;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return ch;
}

// Считывает нажатие клавиши y/n
bool InputControl::yes_or_no(const string& label) {
	char ch;

	while (true) {
		cout << label << " (y/n): ";
		ch = get_char();
		cout << endl;

		if (ch == 'y' || ch == 'Y') return true;
		if (ch == 'n' || ch == 'N') return false;

		cout << endl << "Некорректный ввод!" << endl << endl;
	}
}