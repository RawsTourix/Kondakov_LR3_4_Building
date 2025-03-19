#ifndef KONDAKOV_LR3_4_BUILDING_H
#define KONDAKOV_LR3_4_BUILDING_H

#include "kondakov_lr3_4_def.h"

// ������
class Building {
private:
	string name = "Building";				// �������� ������
	int height = 0;							// ������ ������
	int square = 0;							// ������� ������
	int volume = 0;
	vector<int> reconstruction_dates = {};  // ������ ��� �������������

public:
	// �����������
	// �� ���������
	Building() = default;

	// � �����������
	Building(const string& name,
		int height,
		int square,
		const vector<int>& reconstruction_dates);

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
	inline int get_square() const;
	inline vector<int> get_reconstruction_dates() const;

	// ��������� ������� ���� �������������
	inline int get_average_reconstruction_date() const;

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


	// ����� ���������� ������
	inline int calculate_volume() { this->volume = this->height * this->square; return this->volume; }
};

#endif //!KONDAKOV_LR3_4_BUILDING_H