#ifndef KONDAKOV_LR3_4_BUILDING_H
#define KONDAKOV_LR3_4_BUILDING_H

#include "kondakov_lr3_4_input_control.h"

// ������
class Building {
private:
	string name = DEFAULT_NAME;				// �������� ������
	int height = DEFAULT_HEIGHT;			// ������ ������
	int square = DEFAULT_SQUARE;			// ������� ������
	int volume = DEFAULT_VOLUME;			// ����� ������
	vector<int> reconstruction_dates {};  // ������ ��� �������������

public:
	// ���������� ����� ������ 
	// ������� ����: 
	// 1. ��������
	// 2. ������
	// 3. �������
	// 4. �����
	// 5. ������ ��� �������������
	static const int SIZE = 5;

	// �������� �� ���������
	static const string DEFAULT_NAME;	  // �������� ������ �� ���������
										  // (������������� ��� ������, �.�. string � ��� ������������� ��� ������ � �� ����� ����
										  // ��������������� ������ ������, ������ �����������, �.�. ��� �������� ����� ����������
										  // �� ����� ����������)

	static const int DEFAULT_HEIGHT = 0;  // ������ ������ �� ���������
	static const int DEFAULT_SQUARE = 0;  // ������� ������ �� ���������
	static const int DEFAULT_VOLUME = 0;  // ����� ������ �� ���������

	// �����������
	// �� ���������
	Building() = default;

	// � �����������
	Building(const string& name,
			 int height,
			 int square,
			 vector<int>& reconstruction_dates);

	// � ����������� ��� �������� �� ��������� �����
	Building(const string& name,
			 int height,
			 int square,
			 int volume,
			 vector<int> reconstruction_dates);

	// ��������������
	Building(const string& name);

	// �����������
	Building(const Building& building) = default;

	// �����������
	Building(string&& name,
			 int height,
			 int square,
			 int volume,
			 vector<int>&& reconstruction_dates);

	// ����������
	~Building() = default;

	// �������
	inline void set_name(const string& name);
	inline void set_height(int height);
	inline void set_square(int square);
	inline void set_reconstruction_dates(const vector<int>& reconstruction_dates);

	// �������
	inline string get_name() const;
	inline int get_height() const;
	inline string get_height_as_str() const;
	inline int get_square() const;
	inline string get_square_as_str() const;
	inline int get_volume() const;
	inline string get_volume_as_str() const;
	inline vector<int> get_reconstruction_dates() const;
	inline string get_reconstruction_dates_as_str(const string& separator = ", ") const;

	// ��������� ������� ���� �������������
	inline int get_average_reconstruction_date() const;

	// ���������� ������ ������ (��� ��������� ������ ��� �������)
	inline void update_volume();

	// ��������������� ����������
	// ��������� �� ������� ���� �������������
	// ���� ��������
	friend bool operator==(const Building& a, const Building& b);
	friend bool operator!=(const Building& a, const Building& b);
	friend bool operator>(const Building& a, const Building& b);
	friend bool operator<(const Building& a, const Building& b);
	friend bool operator>=(const Building& a, const Building& b);
	friend bool operator<=(const Building& a, const Building& b);

	// ������� � ������
	friend bool operator==(const Building& a, int year);
	friend bool operator!=(const Building& a, int year);
	friend bool operator>(const Building& a, int year);
	friend bool operator<(const Building& a, int year);
	friend bool operator>=(const Building& a, int year);
	friend bool operator<=(const Building& a, int year);

	// ����� � ��������
	friend bool operator==(int year, const Building& b);
	friend bool operator!=(int year, const Building& b);
	friend bool operator>(int year, const Building& b);
	friend bool operator<(int year, const Building& b);
	friend bool operator>=(int year, const Building& b);
	friend bool operator<=(int year, const Building& b);

	// ��� �������������� ���������� � ������ � ������
	explicit operator string() const;

	// ��� �������� �� ��������� �� ���������
	explicit operator bool() const;

	// ���������
	Building& operator++();
	Building operator++(int);

	// ���������
	Building& operator--();
	Building operator--(int);

	// ��������
	friend Building operator+(const Building& a, const Building& b);

	// ������������ �� ���������
	Building& operator+=(const Building& b);

	// �������� ������������� ������ � ����� �� ���������
	template <typename Container>
	static bool name_exists(const string& name, const Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// ��������� ������ �� ���������� �� ��� ��������
	template <typename Container>
	static Building* get_building_by_name(const string& name, Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// ��������� ������ ������ �� ��������� ��������
	template <typename Container>
	static vector<Building> get_buildings_by_name_substr(const string& substr, Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// �������� ������ � �������� ���������
	template <typename Container>
	static bool delete_by_name(const string& name, Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// ���������� ���������� ������ ������������� � ������� ��������� �� ������ ������
	template <typename Container>
	static Building* new_building(const Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// �������������� ����������� ������ � ������
	template <typename Container>
	static string buildings_to_string(const Container& buildings, const string& separator = "\n",
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);

	// ���������� ���������� ���� int
	template <typename Container>
	static void sort_container(Container& container,
		enable_if_t<is_same_v<typename Container::value_type, int>, int>* = 0);

	// ���������� ���������� ������ �� ���������� ���� �������������
	template <typename Container>
	static bool sort_buildings_by_reconstruction_dates(Container& buildings,
		enable_if_t<is_same_v<typename Container::value_type, Building>, int>* = 0);
};

#include "kondakov_lr3_4_building.hpp"

#endif //!KONDAKOV_LR3_4_BUILDING_H