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
		cout << endl << "[Отмена операции]" << endl;
		return true;
	}
	return false;
}

// Проверка конвертации в целое число
bool InputControl::is_int(const string& input, int min, int max) {
	try {
		int number = stoi(input);
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

// Вспомогательная функция для ввода целых чисел
void InputControl::enter_number(int& varLink, bool& escapeLink, const string& label, int min, int max) {
	string raw_input;

	do {
		cout << label;
		getline(cin, raw_input);
		trim(raw_input);
		escapeLink = is_input_empty(raw_input);
		if (escapeLink) return;
	} while (!is_int(raw_input, min, max));

	varLink = stoi(raw_input);
}

// Вспомогательная функция для ввода строк
void InputControl::enter_string(string& varLink, bool& escapeLink, const string& label) {
	string raw_input;

	cout << label;
	getline(cin, raw_input);
	trim(raw_input);
	escapeLink = is_input_empty(raw_input);
	if (!escapeLink)
		varLink = raw_input;
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