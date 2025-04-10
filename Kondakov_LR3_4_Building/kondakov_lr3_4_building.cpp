#include "kondakov_lr3_4_building.h"

// ������������� �������� �� ��������� ��� ������
const string Building::DEFAULT_NAME = "Building";

// ���������� � 4 ����������� (��� ���������� ������)
Building::Building(const string& name,
				   int height,
				   int square,
	               vector<int>& reconstruction_dates)
	           : Building(name, height, square, height * square, reconstruction_dates) {}

// ���������� � ����������� (�������)
Building::Building(string name,
				   int height,
				   int square,
				   int volume,
				   vector<int> reconstruction_dates)
			   : name(move(name)),
	             height(height),
	             square(square),
	             volume(volume),
				 reconstruction_dates(move(reconstruction_dates)) {
	sort_container(this->reconstruction_dates); }

// ���������� ��������������
Building::Building(const string& name)
	: Building(name, DEFAULT_HEIGHT, DEFAULT_SQUARE, DEFAULT_VOLUME, {} ) {
}

// ���������� �����������
Building::Building(Building&& other) noexcept
			   : name(move(other.name)),
				 height(exchange(other.height, 0)),
				 square(exchange(other.square, 0)),
				 volume(exchange(other.volume, 0)),
				 reconstruction_dates(move(other.reconstruction_dates)) {
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
	return a.get_average_reconstruction_date() > b.get_average_reconstruction_date();
}
bool operator<(const Building& a, const Building& b) {
	return a.get_average_reconstruction_date() < b.get_average_reconstruction_date();
}
bool operator>=(const Building& a, const Building& b) {
	return a.get_average_reconstruction_date() >= b.get_average_reconstruction_date();
}
bool operator<=(const Building& a, const Building& b) {
	return a.get_average_reconstruction_date() <= b.get_average_reconstruction_date();
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
	oss << "��������:\t" << get_name() << "\n"
		<< "������:\t\t" << get_height_as_str() << "\n"
		<< "�������:\t" << get_square_as_str() << "\n"
		<< "�����:\t\t" << get_volume_as_str() << "\n"
		<< "������ ���\n�������������:\t" << get_reconstruction_dates_as_str();
	return oss.str();
}

// ��� �������� �� ��������� �� ���������: ���� �� ��������� -> false, ���� �� �� ��������� -> true
Building::operator bool() const {  // (���� �� ������������ � �������)
	return name != DEFAULT_NAME &&
		   height != DEFAULT_HEIGHT &&
		   square != DEFAULT_SQUARE &&
		   volume != DEFAULT_VOLUME &&
		   !reconstruction_dates.empty();
}

// ���������, ���������� ������
Building& Building::operator++() { height++; this->update_volume(); return *this; }
Building Building::operator++(int) {
	Building copy{ *this };
	++(*this);
	return copy;
}

// ���������, ���������� ������
Building& Building::operator--() { height = (height > 0) ? height - 1 : 0; this->update_volume(); return *this; }
Building Building::operator--(int) {
	Building copy{ *this };
	--(*this);
	return copy;
}

// �������� ���� ������
Building operator+(const Building& a, const Building& b) {
	Building building = a;
	building += b;
	return Building(building);  // ������ ��� ������������� ����������� ��� +=
}

// ������������ �� ��������� (�������� ������)
Building& Building::operator+=(const Building& b) {
	name += " & " + b.name;
	height += b.height;
	square += b.square;
	volume = height * square;
	reconstruction_dates += b.reconstruction_dates;
	sort_container(reconstruction_dates);
	return *this;
}

// ������������ �� ��������� (���������� ������)
Building& Building::operator+=(int n) {
	this->set_height(this->get_height() + n);
	return *this;
}

// ������������ � ���������� (���������� ������)
Building& Building::operator-=(int n) {
	this->set_height(this->get_height() - n > 0 ? this->get_height() - n : 0);
	return *this;
}