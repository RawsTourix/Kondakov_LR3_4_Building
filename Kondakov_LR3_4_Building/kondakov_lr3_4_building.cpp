#include "kondakov_lr3_4_building.h"

// ������������� �������� �� ��������� ��� ������
const string Building::DEFAULT_NAME = "Building";

// ������������
// � �����������
Building::Building(const string& name,
				   int height,
				   int square,
	               const vector<int>& reconstruction_dates)
	           : name(name),
	             height(height),
	             square(square),
	             volume(height* square),
	             reconstruction_dates(reconstruction_dates) {
	sort_container(reconstruction_dates); }

// � ����������� ��� �������� �� ��������� �����
Building::Building(string name,
				   int height,
				   int square,
				   int volume,
				   vector<int> reconstruction_dates)
			   : name(name),
				 height(height),
				 square(square),
				 volume(volume),
				 reconstruction_dates(reconstruction_dates) {
	sort_container(reconstruction_dates); }

// ��������������
Building::Building(const string& name)
	: Building(name, this->height, this->square, this->reconstruction_dates) {
	sort_container(reconstruction_dates); }

// �����������
Building::Building(string&& name,
	               int height,
	               int square,
				   int volume,
	               vector<int>&& reconstruction_dates)
	           : name(move(name)),
	             height(height),
	             square(square),
	             volume(volume),
	             reconstruction_dates(move(reconstruction_dates)) {
}

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
inline string Building::get_reconstruction_dates_as_str(const string& separator = ", ") const {			// ������ ��� ������������� ��� ������
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

// ��������������� ����������
// ��������� �� ������� ���� �������������
// ���� ��������
bool operator==(const Building& a, const Building& b) {
	return a.get_average_reconstruction_date() == b.get_average_reconstruction_date();
}
bool operator!=(const Building& a, const Building& b) {
	return a.get_average_reconstruction_date() != b.get_average_reconstruction_date();
}
bool operator>(const Building& a, const Building& b) {
	return a.get_average_reconstruction_date() < b.get_average_reconstruction_date();
}
bool operator<(const Building& a, const Building& b) {
	return a.get_average_reconstruction_date() > b.get_average_reconstruction_date();
}
bool operator>=(const Building& a, const Building& b) {
	return a.get_average_reconstruction_date() <= b.get_average_reconstruction_date();
}
bool operator<=(const Building& a, const Building& b) {
	return a.get_average_reconstruction_date() >= b.get_average_reconstruction_date();
}

// ������� � ������
bool operator==(const Building& a, int year) { return a.get_average_reconstruction_date() == year; }
bool operator!=(const Building& a, int year) { return a.get_average_reconstruction_date() != year; }
bool operator>(const Building& a, int year)  { return a.get_average_reconstruction_date() < year; }
bool operator<(const Building& a, int year)  { return a.get_average_reconstruction_date() > year; }
bool operator<=(const Building& a, int year) { return a.get_average_reconstruction_date() <= year; }
bool operator>=(const Building& a, int year) { return a.get_average_reconstruction_date() >= year; }

// ����� � ��������
bool operator==(int year, const Building& b) { return year == b.get_average_reconstruction_date(); }
bool operator!=(int year, const Building& b) { return year != b.get_average_reconstruction_date(); }
bool operator<(int year, const Building& b)  { return year < b.get_average_reconstruction_date(); }
bool operator>(int year, const Building& b)  { return year > b.get_average_reconstruction_date(); }
bool operator<=(int year, const Building& b) { return year <= b.get_average_reconstruction_date(); }
bool operator>=(int year, const Building& b) { return year >= b.get_average_reconstruction_date(); }

// �������������� ���������� � ������ � ������
Building::operator string() const {
	ostringstream oss;
	oss << "��������:\t\t" << get_name() << "\n"
		<< "������:\t\t\t" << get_height_as_str() << "\n"
		<< "�������:\t\t" << get_square_as_str() << "\n"
		<< "�����:\t\t\t" << get_volume_as_str() << "\n"
		<< "������ ���\n�������������:\t" << get_reconstruction_dates_as_str() << "\n";
	return oss.str();
}

// ��� �������� �� ��������� �� ���������: ���� �� ��������� -> false, ���� �� �� ��������� -> true
Building::operator bool() const {  // (���� �� ������������ � �������)
	return this->name != DEFAULT_NAME &&
		   this->height != DEFAULT_HEIGHT &&
		   this->square != DEFAULT_SQUARE &&
		   this->volume != DEFAULT_VOLUME &&
		   !this->reconstruction_dates.empty();
}

// ���������, ���������� ������
Building& Building::operator++() { this->height++;  return *this; }
Building Building::operator++(int) {
	Building copy{ *this };
	++(*this);
	return copy;
}

// ���������, ���������� ������
Building& Building::operator--() { this->height = (this->height > 0) ? this->height - 1 : 0;  return *this; }
Building Building::operator--(int) {
	Building copy{ *this };
	--(*this);
	return copy;
}

// �������� ���� ������
Building operator+(const Building& a, const Building& b) {
	return Building(a.name + " & " + b.name, a.height + b.height, a.square + b.square,
		a.reconstruction_dates + b.reconstruction_dates);
}

// ������������ �� ���������
Building& Building::operator+=(const Building& b) {
	this->name += " & " + b.name;
	this->height += b.height;
	this->square += b.square;
	this->volume = height * square;
	this->reconstruction_dates.insert(reconstruction_dates.end(), b.reconstruction_dates.begin(), b.reconstruction_dates.end());
	return *this;
}