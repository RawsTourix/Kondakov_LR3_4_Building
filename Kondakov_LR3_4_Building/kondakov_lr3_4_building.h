#ifndef KONDAKOV_LR3_4_BUILDING_H
#define KONDAKOV_LR3_4_BUILDING_H

#include "kondakov_lr3_4_def.h"

// Здание
class Building {
private:
	string name = "Building";				// название здания
	int height = 0;							// высота здания
	int square = 0;							// площадь здания
	int volume = 0;
	vector<int> reconstruction_dates = {};  // список дат реконструкции

public:
	// Конструкоры
	// По умолчанию
	Building() = default;

	// С параметрами
	Building(const string& name,
		int height,
		int square,
		const vector<int>& reconstruction_dates);

	// Преобразования
	Building(const string& name);

	// Копирования
	Building(const Building& building) = default;

	// Перемещения
	Building(string&& name,
		int height,
		int square,
		int volume,
		vector<int>&& reconstruction_dates);

	// Деструктор
	~Building() = default;

	// Сеттеры
	inline void set_name(const string& name);
	inline void set_height(int height);
	inline void set_square(int square);
	inline void set_reconstruction_dates(const vector<int>& reconstruction_dates);

	// Геттеры
	inline string get_name() const;
	inline int get_height() const;
	inline int get_square() const;
	inline vector<int> get_reconstruction_dates() const;

	// Получение средней даты реконструкции
	inline int get_average_reconstruction_date() const;

	// Переопределение операторов
	// Сравнение по средней дате реконструкции
	// Двух объектов
	friend bool operator==(const Building& a, const Building& b);
	friend bool operator!=(const Building& a, const Building& b);
	friend bool operator>(const Building& a, const Building& b);
	friend bool operator<(const Building& a, const Building& b);
	friend bool operator>=(const Building& a, const Building& b);
	friend bool operator<=(const Building& a, const Building& b);

	// Объекта с числом
	friend bool operator==(const Building& a, int year);
	friend bool operator!=(const Building& a, int year);
	friend bool operator>(const Building& a, int year);
	friend bool operator<(const Building& a, int year);
	friend bool operator>=(const Building& a, int year);
	friend bool operator<=(const Building& a, int year);

	// Числа с объектом
	friend bool operator==(int year, const Building& b);
	friend bool operator!=(int year, const Building& b);
	friend bool operator>(int year, const Building& b);
	friend bool operator<(int year, const Building& b);
	friend bool operator>=(int year, const Building& b);
	friend bool operator<=(int year, const Building& b);

	// Инкремент
	Building& operator++();
	Building operator++(int);

	// Декремент
	Building& operator--();
	Building operator--(int);

	// Сложение
	friend Building operator+(const Building& a, const Building& b);

	// Присваивание со сложением
	Building& operator+=(const Building& b);


	// Метод вычисления объёма
	inline int calculate_volume() { this->volume = this->height * this->square; return this->volume; }
};

#endif //!KONDAKOV_LR3_4_BUILDING_H