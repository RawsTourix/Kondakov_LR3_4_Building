#ifndef KONDAKOV_LR3_4_BUILDING_HPP
#define KONDAKOV_LR3_4_BUILDING_HPP

#include "kondakov_lr3_4_building.h"

// �������
inline void Building::set_name(const string& name) { this->name = name; }						// �������� ������
inline void Building::set_height(int height) { this->height = height; this->update_volume(); }	// ������ ������
inline void Building::set_square(int square) { this->square = square; this->update_volume(); }	// ������� ������
inline void Building::set_reconstruction_dates(const vector<int>& reconstruction_dates) {		// ������ ��� �������������
	this->reconstruction_dates = reconstruction_dates;
}

// �������
inline string Building::get_name() const { return this->name; }											// �������� ������
inline int Building::get_height() const { return this->height; }										// ������ ������
inline string Building::get_height_as_str() const { return to_string(this->height); }					// ������ ������ � ��������� �������
inline int Building::get_square() const { return this->square; }										// ������� ������
inline string Building::get_square_as_str() const { return to_string(this->square); }					// ������� ������ � ��������� �������
inline int Building::get_volume() const { return this->volume; }										// ����� ������
inline string Building::get_volume_as_str() const { return to_string(this->volume); }					// ����� ������ � ��������� �������
inline vector<int> Building::get_reconstruction_dates() const { return this->reconstruction_dates; }	// ������ ��� �������������
inline string Building::get_reconstruction_dates_as_str(const string& separator) const {			// ������ ��� ������������� ��� ������
	if (reconstruction_dates.empty()) return "";

	auto it = this->reconstruction_dates.begin();
	string result = to_string(*it);
	++it;

	while (it != this->reconstruction_dates.end()) {
		result += separator + to_string(*it);
		++it;
	}

	return result;
}

// ��������� ������� ���� �������������
inline int Building::get_average_reconstruction_date() const {
	return this->reconstruction_dates.empty() ? 0 :
		static_cast<int>(accumulate(this->reconstruction_dates.begin(), this->reconstruction_dates.end(), 0)) /
		static_cast<int>(this->reconstruction_dates.size());
}

// ���������� ������ ������ (��� ��������� ������ ��� �������)
inline void Building::update_volume() {
	this->volume = this->height * this->square;
}

// �������� ������������� ������ � ����� �� ���������
template <typename Container>
bool Building::name_exists(const string& name, const Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	return any_of(buildings.begin(), buildings.end(),
		[&name](const Building& building) { return building.get_name() == name; });
}

// ��������� ������ �� ���������� �� ��� ��������
template <typename Container>
Building* Building::get_building_by_name(const string& name, Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	auto it = find_if(buildings.begin(), buildings.end(),
		[&name](const Building& b) { return b.get_name() == name; });

	return (it != buildings.end()) ? &(*it) : nullptr;
}

// ��������� ������ ������ �� ��������� ��������
template <typename Container>
vector<Building> Building::get_buildings_by_name_substr(const string& substr, Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	vector<Building> found_buildings {};
	for (const auto& building : buildings)
		if (building.get_name().find(substr) != string::npos)
			found_buildings.push_back(building);

	return found_buildings;
}

// �������� ������ � �������� ���������
template <typename Container>
bool Building::delete_by_name(const string& name, Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	// ����������� ��������� � ����� ���������� ��� �������� � ������� ��������� �� ����� ����� ���������� (�� ��������� ���������)
	auto new_end = remove_if(buildings.begin(), buildings.end(), [&name](const Building& b) { return b.get_name() == name; });

	// �������� �� ��������
	bool removed = new_end != buildings.end();

	// �������� ���������, ������������ � �����
	buildings.erase(new_end, buildings.end());

	return removed;
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

	InputControl::enter_string(name, escape, "��������: ");								if (escape) return building_ptr;
	while (name_exists(name, buildings)) {
		cout << endl << "������ � ����� ��������� ��� ����������!" << endl << endl;
		InputControl::enter_string(name, escape, "��������: ");							if (escape) return building_ptr;
	}
	InputControl::enter_number(height, escape, "������: ");								if (escape) return building_ptr;
	InputControl::enter_number(square, escape, "�������: ");							if (escape) return building_ptr;
	InputControl::enter_number(years, escape, "����������\n�������������: ", 0, 20);	if (escape) return building_ptr;
	cout << endl;

	// ���������� ��� �������������
	for (int i = 1; i <= years; i++) {
		int year;
		ostringstream label;
		label << i << " ���: ";
		InputControl::enter_number(year, escape, label.str(), 0, 2025);  if (escape) return building_ptr;
		reconstruction_dates.push_back(year);
	}

	building_ptr = new Building(name, height, square, reconstruction_dates);

	return building_ptr;
}

// �������������� �����������, �������� ���������� ������ ������, � ������
template <typename Container>
string Building::buildings_to_string(const Container& buildings, const string& separator,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	string result = "";
	for (const auto& b : buildings) {
		if (!result.empty()) {
			result += separator;
		}
		result += static_cast<string>(b);
	}
	return result;
}

// ���������� ���������� ���� int
template <typename Container>
void Building::sort_container(Container& container,
	enable_if_t<is_same_v<typename Container::value_type, int>, int>*) {
	sort(container.begin(), container.end());
}

// ���������� ���������� ������ �� ���������� ���� �������������
template <typename Container>
bool Building::sort_buildings_by_reconstruction_dates(Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	// ���������� ���������� ������ �� ������ � ������ �������������� � ��� ���
	// ���������� ��� ������ ��� ��� � ����� ���������� � ���������� �������� �� ������ �� ���
	auto it = partition(buildings.begin(), buildings.end(), [](const Building& b) { return !b.get_reconstruction_dates().empty(); });

	if (it == buildings.begin())
		return false;
	else {
		// ���������� ������ � ������ �������������
		sort(buildings.begin(), it, [](const Building& b1, const Building& b2) {
			return b1.get_reconstruction_dates().back() < b2.get_reconstruction_dates().back(); });
		return true;
	}
}

#endif //! KONDAKOV_LR3_4_BUILDING_HPP