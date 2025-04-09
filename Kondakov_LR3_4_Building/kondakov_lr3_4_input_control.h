#ifndef KONDAKOV_LR3_4_INPUT_CONTROL_H
#define KONDAKOV_LR3_4_INPUT_CONTROL_H

#include "kondakov_lr3_4_def.h"

class InputControl {
public:
	// �������� �������� ������� � � ����� (trim)
	static void trim(string& str);

	// �������� �� ������ ���� ��� ������ ��������
	static bool is_input_empty(const string& input);

	// �������� ����������� � int
	static bool is_int(const string& input, int min, int max);

	// �������� ����������� � float
	static bool is_float(const string& input, float min, float max);

	// ���� ��� ����� (int, float)
	template <typename T>
	static bool input(T& varLink, const string& label, T min = 0, T max = 2147483647,
		enable_if_t<is_same_v<typename T, int> ||
					is_same_v<typename T, float>, int>* = 0);

	// ���� ��� �����
	static bool input(string& varLink, const string& label);

	// ���� ��� �������������
	template <typename Container>
	static bool input_reconstruction_dates(Container& reconstruction_dates, int min = 0, int max = 20,
		enable_if_t<is_same_v<typename Container::value_type, int>, int>* = 0);

	// ���������� ���� ������
	static char get_char();

	// ��������� ������� ������� y/n
	static bool yes_or_no(const string& label);
};

#include "kondakov_lr3_4_input_control.hpp"

#endif // !KONDAKOV_LR3_4_INPUT_CONTROL_H