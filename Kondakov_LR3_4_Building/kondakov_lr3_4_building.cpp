#include "kondakov_lr3_4_building.h"

// Инициализация названия по умолчанию вне класса
const string Building::DEFAULT_NAME = "Building";

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
	sort_container(reconstruction_dates); }

// С параметрами для загрузки из бинарного файла
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

// Преобразования
Building::Building(const string& name)
	: Building(name, this->height, this->square, this->reconstruction_dates) {
	sort_container(reconstruction_dates); }

// Перемещения
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

// Сеттеры
inline void Building::set_name(const string& name) { this->name = name; }						// название здания
inline void Building::set_height(int height) { this->height = height; this->update_volume(); }	// высота здания
inline void Building::set_square(int square) { this->square = square; this->update_volume(); }	// площадь здания
inline void Building::set_reconstruction_dates(const vector<int>& reconstruction_dates) {		// список дат реконструкции
	this->reconstruction_dates = reconstruction_dates;
}

// Геттеры
inline string Building::get_name() const { return this->name; }											// название здания
inline int Building::get_height() const { return this->height; }										// высота здания
inline string Building::get_height_as_str() const { return to_string(this->height); }					// высота здания в строковом формате
inline int Building::get_square() const { return this->square; }										// площадь здания
inline string Building::get_square_as_str() const { return to_string(this->square); }					// площадь здания в строковом формате
inline int Building::get_volume() const { return this->volume; }										// объём здания
inline string Building::get_volume_as_str() const { return to_string(this->volume); }					// объём здания в строковом формате
inline vector<int> Building::get_reconstruction_dates() const { return this->reconstruction_dates; }	// список дат реконструкции
inline string Building::get_reconstruction_dates_as_str(const string& separator = ", ") const {			// список дат реконструкции как строка
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

// Получение средней даты реконструкции
inline int Building::get_average_reconstruction_date() const {
	return this->reconstruction_dates.empty() ? 0 :
		static_cast<int>(accumulate(this->reconstruction_dates.begin(), this->reconstruction_dates.end(), 0)) /
		static_cast<int>(this->reconstruction_dates.size());
}

// Обновление объёма здания (при изменении высоты или площади)
inline void Building::update_volume() {
	this->volume = this->height * this->square;
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
bool operator>(const Building& a, int year)  { return a.get_average_reconstruction_date() < year; }
bool operator<(const Building& a, int year)  { return a.get_average_reconstruction_date() > year; }
bool operator<=(const Building& a, int year) { return a.get_average_reconstruction_date() <= year; }
bool operator>=(const Building& a, int year) { return a.get_average_reconstruction_date() >= year; }

// Числа с объектом
bool operator==(int year, const Building& b) { return year == b.get_average_reconstruction_date(); }
bool operator!=(int year, const Building& b) { return year != b.get_average_reconstruction_date(); }
bool operator<(int year, const Building& b)  { return year < b.get_average_reconstruction_date(); }
bool operator>(int year, const Building& b)  { return year > b.get_average_reconstruction_date(); }
bool operator<=(int year, const Building& b) { return year <= b.get_average_reconstruction_date(); }
bool operator>=(int year, const Building& b) { return year >= b.get_average_reconstruction_date(); }

// Преобразование информации о здании в строку
Building::operator string() const {
	ostringstream oss;
	oss << "Название:\t\t" << get_name() << "\n"
		<< "Высота:\t\t\t" << get_height_as_str() << "\n"
		<< "Площадь:\t\t" << get_square_as_str() << "\n"
		<< "Объём:\t\t\t" << get_volume_as_str() << "\n"
		<< "Список дат\nреконструкции:\t" << get_reconstruction_dates_as_str() << "\n";
	return oss.str();
}

// Для проверки на параметры по умолчанию: если по умолчанию -> false, если не по умолчанию -> true
Building::operator bool() const {  // (пока не используется в проекте)
	return this->name != DEFAULT_NAME &&
		   this->height != DEFAULT_HEIGHT &&
		   this->square != DEFAULT_SQUARE &&
		   this->volume != DEFAULT_VOLUME &&
		   !this->reconstruction_dates.empty();
}

// Инкремент, увеличение высоты
Building& Building::operator++() { this->height++;  return *this; }
Building Building::operator++(int) {
	Building copy{ *this };
	++(*this);
	return copy;
}

// Декремент, уменьшение высоты
Building& Building::operator--() { this->height = (this->height > 0) ? this->height - 1 : 0;  return *this; }
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