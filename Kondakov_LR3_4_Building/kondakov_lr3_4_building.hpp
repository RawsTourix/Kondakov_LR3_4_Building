#ifndef KONDAKOV_LR3_4_BUILDING
#define KONDAKOV_LR3_4_BUILDING

#include "kondakov_lr3_4_building.h"

// �������� ������������� ������ � ����� �� ���������
template <typename Container>
bool Building::name_exists(const string& name, const Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	for (const auto& building : buildings)
		if (building.name == name)
			return true;
	return false;
}

// ���������� ���������� ������ ������������� � ������� ��������� �� ������ ������
template <typename Container>
Building* Building::new_building(const Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	Building* building_ptr = nullptr;

	bool escape = false;

	string name;
	int height, square, years;
	vector<int> reconstruction_dates;

	cout << "������� ���������� � ������." << endl << endl;

	InputControl::enter_string(name, escape, "��������: ");					  if (escape) return building_ptr;
	while (name_exists(name, buildings)) {
		cout << endl << "������ � ����� ��������� ��� ����������!" << endl << endl;
		InputControl::enter_string(name, escape, "��������: ");				  if (escape) return building_ptr;
	}
	InputControl::enter_number(height, escape, "������: ");					  if (escape) return building_ptr;
	InputControl::enter_number(square, escape, "�������: ");				  if (escape) return building_ptr;
	InputControl::enter_number(years, escape, "���������� �������������: ");  if (escape) return building_ptr;

	// ���������� ��� �������������
	for (int i = 1; i <= years; i++) {
		int year;
		ostringstream label;
		label << i << " ���: ";
		InputControl::enter_number(year, escape, label.str());  if (escape) return building_ptr;
		reconstruction_dates.push_back(year);
	}

	building_ptr = new Building(name, height, square, reconstruction_dates);

	return building_ptr;
}

// �������������� �����������, �������� ���������� ������ ������, � ������
template <typename Iterator>
string Building::buildings_to_string(Iterator begin, Iterator end, const string& separator,
	enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
	if (begin == end) return "";

	string result = static_cast<string>(*begin);
	++begin;

	while (begin != end) {
		result += separator + static_cast<string>(*begin);
		++begin;
	}

	return result;
}

// ���������� ���������� ���� int
template <typename Container>
void Building::sort_container(Container& container,
	enable_if_t<is_same_v<typename Container::value_type, int>, int>*) {
	sort(container.begin(), container.end());
}

#endif //! KONDAKOV_LR3_4_BUILDING