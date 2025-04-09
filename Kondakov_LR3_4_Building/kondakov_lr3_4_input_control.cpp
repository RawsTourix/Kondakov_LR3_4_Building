#include "kondakov_lr3_4_input_control.h"

// �������� �������� ������� � � ����� (trim)
void InputControl::trim(string& str) {
	// ������� ������� � ������
	while (!str.empty() && str.front() == ' ')
		str.erase(str.begin());

	// ������� ������� � �����
	while (!str.empty() && str.back() == ' ')
		str.pop_back();
}

// �������� �� ������ ���� ��� ������ ��������
bool InputControl::is_input_empty(const string& input) {
	if (input.empty()) {
		cout << endl << "[������ ��������]";
		return true;
	}
	return false;
}

// �������� ����������� � int
bool InputControl::is_int(const string& input, int min, int max) {
	try {
		int number = stoi(input);
		if (input.size() > to_string(number).size()) throw invalid_argument("input �������� ������������ �������.");
		if (number < min) { cout << endl << "�� ����� \"" << number << "\" � �������� ������ ���� �� ������ \"" << min << "\"" << endl << endl; return false; }
		if (number > max) { cout << endl << "�� ����� \"" << number << "\" � �������� ������ ���� �� ������ \"" << max << "\"" << endl << endl; return false; }
	}
	catch (const invalid_argument&) {
		cerr << endl << "�������� �������� \"" << input << "\" �� �������� ������!" << endl << endl;
		return false;
	}
	catch (const out_of_range&) {
		cerr << endl << "����� \"" << input << "\" ������� �� ���������� ��������!" << endl << endl;
		return false;
	}
	return true;
}

// �������� ����������� � float
bool InputControl::is_float(const string& input, float min, float max) {
	try {
		float number = stof(input);
		if (input.size() > to_string(number).size()) throw invalid_argument("input �������� ������������ �������.");
		if (number < min) { cout << endl << "�� ����� \"" << number << "\" � �������� ������ ���� �� ������ \"" << min << "\"" << endl << endl; return false; }
		if (number > max) { cout << endl << "�� ����� \"" << number << "\" � �������� ������ ���� �� ������ \"" << max << "\"" << endl << endl; return false; }
	}
	catch (const invalid_argument&) {
		cerr << endl << "�������� ���� �������� \"" << input << "\" �� �������� ������!" << endl << endl;
		return false;
	}
	catch (const out_of_range&) {
		cerr << endl << "����� \"" << input << "\" ������� �� ���������� ��������!" << endl << endl;
		return false;
	}
	return true;
}

// ���� ��� �����
bool InputControl::input(string& varLink, const string& label) {
	string raw_input;

	cout << label;
	getline(cin, raw_input);
	trim(raw_input);
	if (is_input_empty(raw_input))
		return true;   // ������ ��������
	else {
		varLink = raw_input;
		return false;  // ����������� ��������
	}
}

// ���������� ���� ������
char InputControl::get_char() {
	char ch;
	cin >> ch;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return ch;
}

// ��������� ������� ������� y/n
bool InputControl::yes_or_no(const string& label) {
	char ch;

	while (true) {
		cout << label << " (y/n): ";
		ch = get_char();
		cout << endl;

		if (ch == 'y' || ch == 'Y') return true;
		if (ch == 'n' || ch == 'N') return false;

		cout << endl << "������������ ����!" << endl << endl;
	}
}