#include "kondakov_lr3_4_building.h"

// Конструкторы
// С параметрами
Building::Building(const string& name,
	int height,
	int square,
	const vector<int>& reconstruction_dates)
	: name(name),
	height(height),
	square(square),
	volume(height* square),
	reconstruction_dates(reconstruction_dates) {
}

// Преобразования
Building::Building(const string& name)
	: Building(name, this->height, this->square, this->reconstruction_dates) {
}

// Перемещения
Building::Building(string&& name,
	int height,
	int square,
	vector<int>&& reconstruction_dates)
	: name(move(name)),
	height(height),
	square(square),
	volume(volume),
	reconstruction_dates(move(reconstruction_dates)) {
}

// Сеттеры
inline void Building::set_name(const string& name) { this->name = name; }
inline void Building::set_height(int height) { this->height = height; }
inline void Building::set_square(int square) { this->square = square; }
inline void Building::set_reconstruction_dates(const vector<int>& reconstruction_dates) { this->reconstruction_dates = reconstruction_dates; }

// Геттеры
inline string Building::get_name() const { return this->name; }
inline int Building::get_height() const { return this->height; }
inline int Building::get_square() const { return this->square; }
inline vector<int> Building::get_reconstruction_dates() const { return this->reconstruction_dates; }

// Получение средней даты реконструкции
inline int Building::get_average_reconstruction_date() const {
	return accumulate(this->reconstruction_dates.begin(), this->reconstruction_dates.end(), 0) / this->reconstruction_dates.size();
}

// Переопределение операторов
// Сравнение по средней дате реконструкции
// Двух объектов
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

// Объекта с числом
bool operator==(const Building& a, int year) { return a.get_average_reconstruction_date() == year; }
bool operator!=(const Building& a, int year) { return a.get_average_reconstruction_date() != year; }
bool operator>(const Building& a, int year) { return a.get_average_reconstruction_date() < year; }
bool operator<(const Building& a, int year) { return a.get_average_reconstruction_date() > year; }
bool operator<=(const Building& a, int year) { return a.get_average_reconstruction_date() <= year; }
bool operator>=(const Building& a, int year) { return a.get_average_reconstruction_date() >= year; }

// Числа с объектом
bool operator==(int year, const Building& b) { return year == b.get_average_reconstruction_date(); }
bool operator!=(int year, const Building& b) { return year != b.get_average_reconstruction_date(); }
bool operator<(int year, const Building& b) { return year < b.get_average_reconstruction_date(); }
bool operator>(int year, const Building& b) { return year > b.get_average_reconstruction_date(); }
bool operator<=(int year, const Building& b) { return year <= b.get_average_reconstruction_date(); }
bool operator>=(int year, const Building& b) { return year >= b.get_average_reconstruction_date(); }


// Инкремент
Building& Building::operator++() { this->height++;  return *this; }
Building Building::operator++(int) {
	Building copy{ *this };
	++(*this);
	return copy;
}

// Декремент
Building& Building::operator--() { this->height = max(0, this->height);  return *this; }
Building Building::operator--(int) {
	Building copy{ *this };
	--(*this);
	return copy;
}

// Сложение двух зданий
Building operator+(const Building& a, const Building& b) {
	return Building(a.name + " & " + b.name, a.height + b.height, a.square + b.square,
		a.reconstruction_dates + b.reconstruction_dates);
}

// Присваивание со сложением
Building& Building::operator+=(const Building& b) {
	this->name += " & " + b.name;
	this->height += b.height;
	this->square += b.square;
	this->volume = height * square;
	this->reconstruction_dates.insert(reconstruction_dates.end(), b.reconstruction_dates.begin(), b.reconstruction_dates.end());
	return *this;
}