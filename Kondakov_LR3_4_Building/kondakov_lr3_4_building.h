#ifndef KONDAKOV_LR3_4_BUILDING_H
#define KONDAKOV_LR3_4_BUILDING_H

#include "kondakov_lr3_4_input_control.h"

// Здание
class Building {
private:
	string name = DEFAULT_NAME;				// название здания
	int height = DEFAULT_HEIGHT;			// высота здания
	int square = DEFAULT_SQUARE;			// площадь здания
	int volume = DEFAULT_VOLUME;			// объём здания
	vector<int> reconstruction_dates {};  // список дат реконструкции

public:
	// Количество полей класса 
	// Текущие поля: 
	// 1. название
	// 2. высота
	// 3. площадь
	// 4. объём
	// 5. список дат реконструкции
	static const int SIZE = 5;

	// Значения по умолчанию
	static const string DEFAULT_NAME;	  // название здания по умолчанию
										  // (инициализация вне класса, т.к. string — это нетривиальный тип данных и не может быть
										  // инициализирован внутри класса, будучи константным, т.к. его значение будет неизвестно
										  // на этапе компиляции)

	static const int DEFAULT_HEIGHT = 0;  // высота здания по умолчанию
	static const int DEFAULT_SQUARE = 0;  // площадь здания по умолчанию
	static const int DEFAULT_VOLUME = 0;  // объём здания по умолчанию

	// Конструкоры
	// По умолчанию
	Building() = default;

	// С параметрами
	Building(const string& name,
			 int height,
			 int square,
			 vector<int>& reconstruction_dates);

	// С параметрами для загрузки из бинарного файла
	Building(const string& name,
			 int height,
			 int square,
			 int volume,
			 vector<int> reconstruction_dates);

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
	inline string get_height_as_str() const;
	inline int get_square() const;
	inline string get_square_as_str() const;
	inline int get_volume() const;
	inline string get_volume_as_str() const;
	inline vector<int> get_reconstruction_dates() const;
	inline string get_reconstruction_dates_as_str(const string& separator = ", ") const;

	// Получение средней даты реконструкции
	inline int get_average_reconstruction_date() const;

	// Обновление объёма здания (при изменении высоты или площади)
	inline void update_volume();

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

	// Для преобразования информации о здании в строку
	explicit operator string() const;

	// Для проверки на параметры по умолчанию
	explicit operator bool() const;

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

	// Проверка существования здания с таким же названием
	template <typename Container>
	static bool name_exists(const string& name, const Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Получение здания из контейнера по его названию
	template <typename Container>
	static Building* get_building_by_name(const string& name, Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Получение списка зданий по подстроке названия
	template <typename Container>
	static vector<Building> get_buildings_by_name_substr(const string& substr, Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Удаление здания с заданным названием
	template <typename Container>
	static bool delete_by_name(const string& name, Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Заполнение параметров здания пользователем и возврат указателя на объект здания
	template <typename Container>
	static Building* new_building(const Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Преобразование контейнеров зданий в строку
	template <typename Container>
	static string buildings_to_string(const Container& buildings, const string& separator = "\n",
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Сортировка контейнера типа int
	template <typename Container>
	static void sort_container(Container& container,
		enable_if_t<is_same_v<typename Container::value_type, int>, int>* = 0);

	// Сортировка контейнера зданий по последнему году реконструкции
	template <typename Container>
	static bool sort_buildings_by_reconstruction_dates(Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);
};

#include "kondakov_lr3_4_building.hpp"

#endif //!KONDAKOV_LR3_4_BUILDING_H