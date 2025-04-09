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
	vector<int> reconstruction_dates {};    // список дат реконструкции

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

	// Конструкор по умолчанию
	Building() = default;

	// Конструкор с 4 параметрами (с вычислениием объёма)
	Building(const string& name,
			 int height,
			 int square,
			 vector<int>& reconstruction_dates);

	// Конструкор с параметрами (базовый)
	Building(string name,
			 int height,
			 int square,
			 int volume,
			 vector<int> reconstruction_dates);

	// Конструкор преобразования
	Building(const string& name);

	// Конструкор копирования
	Building(const Building&) = default;
	Building& operator=(const Building&) = default;

	// Конструкор перемещения
	Building(Building&& other) noexcept;
	Building& operator=(Building&&) noexcept = default;

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
	inline vector<int>& get_reconstruction_dates_link();
	inline vector<int> get_reversed_reconstruction_dates() const;
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

	// Присваивание со сложением (увеличение высоты)
	Building& operator+=(int n);

	// Присваивание с вычитанием (уменьшение высоты)
	Building& operator-=(int n);

	// Проверка существования здания с таким же названием
	template <typename Container>
	static bool name_exists(const string& name, const Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Получение здания из контейнера по его названию
	template <typename Container>
	static Building* get_building_by_name(const string& name, Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Получение здания из контейнера по его введённому названию (устарело)
	template <typename Container>
	static Building* get_building_by_input_name(Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Получение списка зданий по подстроке названия
	template <typename Container>
	static vector<Building> get_buildings_by_name_substr(const string& substr, Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Удаление здания с заданным названием
	template <typename Container>
	static bool delete_by_name(const string& name, Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Удаление здания по его ссылке из списка
	template <typename Container>
	static bool delete_by_building_link(const Building& building, Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Заполнение параметров здания пользователем и возврат указателя на объект здания
	template <typename Container>
	static Building* new_building(const Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Преобразование контейнеров зданий в строку
	template <typename Container>
	static string buildings_to_string(const Container& buildings, const string& separator = "\n\n",
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Проверка существования даты
	template <typename Container>
	static bool year_exists(int year, const Container& reconstruction_dates,
		enable_if_t<is_same_v<typename Container::value_type, int>, int>* = 0);

	// Получение даты из контейнера по значению
	template <typename Container>
	static int* get_year_by_value(int year, Container& reconstruction_dates,
		enable_if_t<is_same_v<typename Container::value_type, int>, int>* = 0);

	// Получение даты из контейнера по введённому значению
	template <typename Container>
	static int* get_year_by_input_value(Container& reconstruction_dates,
		enable_if_t<is_same_v<typename Container::value_type, int>, int>* = 0);

	// Сортировка контейнера зданий по последнему году реконструкции
	template <typename Container>
	static bool sort_buildings_by_reconstruction_dates(Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Сортировка контейнера зданий по средней дате реконструкции
	template <typename Container>
	static bool sort_buildings_by_avg_reconstruction_date(Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Сортировка контейнера зданий по высоте
	template <typename Container>
	static bool sort_buildings_by_height(Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Сортировка контейнера зданий по площади
	template <typename Container>
	static bool sort_buildings_by_square(Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Сортировка контейнера зданий по объёму
	template <typename Container>
	static bool sort_buildings_by_volume(Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Сортировка контейнера зданий по всем параметрам
	template <typename Container>
	static bool sort_buildings_by_all(Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Выбор здания из списка по номеру названия
	template <typename Container>
	static Building* choose_building_by_name_number(Container& buildings, const string& message = "Выберите здание из списка.",
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// Получение даты из контейнера по номеру даты из списка
	static int* choose_reconstruction_date_by_year_number(Building& building);
};

#include "kondakov_lr3_4_building.hpp"

#endif //!KONDAKOV_LR3_4_BUILDING_H