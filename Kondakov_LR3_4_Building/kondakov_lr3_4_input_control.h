#ifndef KONDAKOV_LR3_4_INPUT_CONTROL_H
#define KONDAKOV_LR3_4_INPUT_CONTROL_H

#include "kondakov_lr3_4_def.h"

class InputControl {
public:
	// �������� �������� ������� � � ����� (trim)
	static void trim(string& str);

	// �������� �� ������ ���� ��� ������ ��������
	static bool is_input_empty(const string& input);

	// �������� ����������� � ����� �����
	static bool is_int(const string& input, int min, int max);

	// ��������������� ������� ��� ����� ����� �����
	static void enter_number(int& varLink, bool& escapeLink, const string& label = "", int min = 0, int max = 2147483647);

	// ��������������� ������� ��� ����� �����
	static void enter_string(string& varLink, bool& escapeLink, const string& label = "");

	// ���������� ���� ������
	static char get_char();

	// ��������� ������� ������� y/n
	static bool yes_or_no(const string& label);
};

#endif // !KONDAKOV_LR3_4_INPUT_CONTROL_H