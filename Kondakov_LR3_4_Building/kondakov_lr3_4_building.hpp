#ifndef KONDAKOV_LR3_4_BUILDING_HPP
#define KONDAKOV_LR3_4_BUILDING_HPP

#include "kondakov_lr3_4_building.h"

// �������
inline void Building::set_name(const string& name) { this->name = name; }						    // �������� ������
inline void Building::set_height(int height) { this->height = height; this->update_volume(); }	    // ������ ������
inline void Building::set_square(int square) { this->square = square; this->update_volume(); }	    // ������� ������
inline void Building::set_reconstruction_dates(const vector<int>& reconstruction_dates) {		    // ������ ��� �������������
	this->reconstruction_dates.assign(reconstruction_dates.begin(), reconstruction_dates.end());
}

// �������
inline string Building::get_name() const { return name; }											// �������� ������
inline int Building::get_height() const { return height; }											// ������ ������
inline string Building::get_height_as_str() const { return to_string(height); }						// ������ ������ � ��������� �������
inline int Building::get_square() const { return square; }											// ������� ������
inline string Building::get_square_as_str() const { return to_string(square); }						// ������� ������ � ��������� �������
inline int Building::get_volume() const { return volume; }											// ����� ������
inline string Building::get_volume_as_str() const { return to_string(volume); }						// ����� ������ � ��������� �������
inline vector<int> Building::get_reconstruction_dates() const { return reconstruction_dates; }		// ������ ��� �������������
inline vector<int>& Building::get_reconstruction_dates_link() { return reconstruction_dates; }		// ������ �� �������� ������ ��� �������������
inline vector<int> Building::get_reversed_reconstruction_dates() const {
	vector<int> reversed(reconstruction_dates.begin(), reconstruction_dates.end());
	reverse(reversed.begin(), reversed.end());
	return reversed;
}
inline string Building::get_reconstruction_dates_as_str(const string& separator) const {			// ������ ��� ������������� ��� ������
	if (reconstruction_dates.empty()) return "";

	auto it = reconstruction_dates.begin();
	string result = to_string(*it);
	++it;

	while (it != reconstruction_dates.end()) {
		result += separator + to_string(*it);
		++it;
	}

	return result;
}

// ��������� ������� ���� �������������
inline int Building::get_average_reconstruction_date() const {
	if (reconstruction_dates.empty())
		return 0;

	int sum = accumulate(reconstruction_dates.begin(), reconstruction_dates.end(), 0);
	return static_cast<int>(sum / static_cast<int>(reconstruction_dates.size()));
}

// ���������� ������ ������ (��� ��������� ������ ��� �������)
inline void Building::update_volume() {
	volume = height * square;
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

	return (it == buildings.end()) ? nullptr : &(*it);
}

// ��������� ������ �� ���������� �� ��� ��������� �������� (��������)
template <typename Container>
Building* Building::get_building_by_input_name(Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	string name;

	do {
		if (InputControl::input(name, "��������: ")) return nullptr;
		cout << endl;
		if (!name_exists(name, buildings))
			cout << "������ � ����� ��������� �� ����������!" << endl << endl;
	} while (!name_exists(name, buildings));
	return Building::get_building_by_name(name, buildings);
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

	string name;
	int height, square;
	vector<int> reconstruction_dates {};

	cout << "������� ���������� � ������." << endl << endl;

	do {
		if (InputControl::input(name, "��������: "))						return building_ptr;
		if (name_exists(name, buildings))
			cout << endl << "������ � ����� ��������� ��� ����������!" << endl << endl;
	} while (name_exists(name, buildings));
	if (InputControl::input(height, "������: "))							return building_ptr;
	if (InputControl::input(square, "�������: "))							return building_ptr;

	if (InputControl::input_reconstruction_dates(reconstruction_dates))		return building_ptr;

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

// �������� ������������� ����
template <typename Container>
bool Building::year_exists(int year, const Container& reconstruction_dates,
	enable_if_t<is_same_v<typename Container::value_type, int>, int>*) {
	return any_of(reconstruction_dates.begin(), reconstruction_dates.end(),
		[&year](int y) { return y == year; });
}

// ��������� ���� �� ���������� �� ��������
template <typename Container>
int* Building::get_year_by_value(int year, Container& reconstruction_dates,
	enable_if_t<is_same_v<typename Container::value_type, int>, int>*) {
	auto it = find_if(reconstruction_dates.begin(), reconstruction_dates.end(),
		[&year](int y) { return y == year; });

	return (it == reconstruction_dates.end()) ? nullptr : &(*it);
}

// ��������� ���� �� ���������� �� ��������� ��������
template <typename Container>
int* Building::get_year_by_input_value(Container& reconstruction_dates,
	enable_if_t<is_same_v<typename Container::value_type, int>, int>*) {
	int year;

	do {
		if (InputControl::input(year, "���: ")) return nullptr;
		cout << endl;
		if (!year_exists(year, reconstruction_dates))
			cout << "������ ���� �� ����������!" << endl << endl;
	} while (!year_exists(year, reconstruction_dates));

	return get_year_by_value(year, reconstruction_dates);
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

// ���������� ���������� ������ �� ������� ���� �������������
template <typename Container>
bool Building::sort_buildings_by_avg_reconstruction_date(Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	// ���������� ���������� ������ �� ������ � ������ �������������� � ��� ���
	// ���������� ��� ������ ��� ��� � ����� ���������� � ���������� �������� �� ������ �� ���
	auto it = partition(buildings.begin(), buildings.end(), [](const Building& b) { return !b.get_reconstruction_dates().empty(); });

	if (it == buildings.begin())
		return false;
	else {
		sort(buildings.begin(), it, [](const Building& b1, const Building& b2) {
			return b1 < b2; });
		return true;
	}
}

// ���������� ���������� ������ �� ������
template <typename Container>
bool Building::sort_buildings_by_height(Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	if (buildings.empty())
		return false;
	else {
		sort(buildings.begin(), buildings.end(), [](const Building& b1, const Building& b2) {
			return b1.get_height() < b2.get_height(); });
		return true;
	}
}

// ���������� ���������� ������ �� �������
template <typename Container>
bool Building::sort_buildings_by_square(Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	if (buildings.empty())
		return false;
	else {
		sort(buildings.begin(), buildings.end(), [](const Building& b1, const Building& b2) {
			return b1.get_square() < b2.get_square(); });
		return true;
	}
}

// ���������� ���������� ������ �� ������
template <typename Container>
bool Building::sort_buildings_by_volume(Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	if (buildings.empty())
		return false;
	else {
		sort(buildings.begin(), buildings.end(), [](const Building& b1, const Building& b2) {
			return b1.get_volume() < b2.get_volume(); });
		return true;
	}
}

// ���������� ���������� ������ �� ���� ����������
template <typename Container>
bool Building::sort_buildings_by_all(Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	if (buildings.empty())
		return false;
	else {
		sort(buildings.begin(), buildings.end(), [](const Building& b1, const Building& b2) {
			// ��������� ����������, ����� tie ��� ������� �� �������� �� ������
			const string name1 = b1.get_name(); int h1 = b1.get_height(); int s1 = b1.get_square(); int v1 = b1.get_volume();
			const string name2 = b2.get_name(); int h2 = b2.get_height(); int s2 = b2.get_square(); int v2 = b2.get_volume();
			vector<int> dates1 = move(b1.get_reversed_reconstruction_dates());
			vector<int> dates2 = move(b2.get_reversed_reconstruction_dates());

			return tie(name1, h1, s1, v1, dates1) <
				   tie(name2, h2, s2, v2, dates2);
		});  // get_reversed_reconstruction_dates ����� ��� ����, ����� ���������� ������ �� ��������� ����� �������������
		return true;
	}
}

// ����� ������ �� ������ �� ������ ��������
template <typename Container>
Building* Building::choose_building_by_name_number(Container& buildings, const string& message,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	map<int, string> building_names_map = get_numbered_map(buildings, [](Building b) { return b.get_name(); });
	cout << building_names_map << endl << endl;

	int choice;
	Building* building_ptr = nullptr;

	cout << message << endl << endl;
	if (InputControl::input(choice, "����� ������: ", 1, static_cast<int>(building_names_map.size()))) return building_ptr;
	cout << endl;

	if (building_names_map.find(choice) == building_names_map.end()) {
		cout << "������ � ����� ������� �� �������.";
		return building_ptr;
	}
	else {
		building_ptr = get_building_by_name(building_names_map.at(choice), buildings);
		cout << static_cast<string>(*building_ptr) << endl << endl;
		return building_ptr;
	}
}

#endif //!KONDAKOV_LR3_4_BUILDING_HPP