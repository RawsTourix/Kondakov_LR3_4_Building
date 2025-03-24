#ifndef KONDAKOV_LR3_4_BUILDING
#define KONDAKOV_LR3_4_BUILDING

#include "kondakov_lr3_4_building.h"

// Проверка существования здания с таким же названием
template <typename Container>
bool Building::name_exists(const string& name, const Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	return any_of(buildings.begin(), buildings.end(),
		[&](const Building& building) { return building.name == name; });
}

// Получение здания из контейнера по его названию
template <typename Container>
Building* Building::get_building_by_name(const string& name, const Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	auto it = find_if(buildings.begin(), buildings.end(),
		[&](const Building& b) { return b.name == name; });

	return (it != buildings.end()) ? &(*it) : nullptr;
}

// Удаление здания с заданным названием
template <typename Container>
bool Building::delete_by_name(const string& name, Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	// Перемещение элементов в конец контейнера для удаления и возврат итератора на новый конец контейнера (до удаляемых элементов)
	auto new_end = remove_if(buildings.begin(), buildings.end(), [&](Building b) { b.name == name });
	// Удаление элементов, перемещённых в конец
	buildings.erase(new_end, buildings.end());

	if (find_if(buildings.begin(), buildings.end(), [&](const Building& b) { b.name == name }) == buildings.end())
		return true;
	else
		return false;
}

// Заполнение параметров здания пользователем и возврат указателя на объект здания
template <typename Container>
Building* Building::new_building(const Container& buildings,
	enable_if_t<is_same_v<typename Container::value_type, Building>, int>*) {
	Building* building_ptr = nullptr;

	bool escape = false;

	string name;
	int height, square, years;
	vector<int> reconstruction_dates;

	cout << "Введите информацию о здании." << endl << endl;

	InputControl::enter_string(name, escape, "Название: ");					  if (escape) return building_ptr;
	while (name_exists(name, buildings)) {
		cout << endl << "Здание с таким названием уже существует!" << endl << endl;
		InputControl::enter_string(name, escape, "Название: ");				  if (escape) return building_ptr;
	}
	InputControl::enter_number(height, escape, "Высота: ");					  if (escape) return building_ptr;
	InputControl::enter_number(square, escape, "Площадь: ");				  if (escape) return building_ptr;
	InputControl::enter_number(years, escape, "Количество реконструкций: ");  if (escape) return building_ptr;

	// Добавление дат реконструкции
	for (int i = 1; i <= years; i++) {
		int year;
		ostringstream label;
		label << i << " год: ";
		InputControl::enter_number(year, escape, label.str());  if (escape) return building_ptr;
		reconstruction_dates.push_back(year);
	}

	building_ptr = new Building(name, height, square, reconstruction_dates);

	return building_ptr;
}

// Преобразование контейнеров, хранящих экземпляры класса Здание, в строку
template <typename Iterator>
string Building::buildings_to_string(Iterator begin, Iterator end, const string& separator,
	enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
	if (begin == end) return "";

	string result = static_cast<string>(*begin);
	++begin;

	while (begin != end) {
		result += separator + static_cast<string>(*begin);
		++begin;
	}

	return result;
}

// Сортировка контейнера типа int
template <typename Container>
void Building::sort_container(Container& container,
	enable_if_t<is_same_v<typename Container::value_type, int>, int>*) {
	sort(container.begin(), container.end());
}

// Сортировка контейнера зданий по последнему году реконструкции
template <typename Iterator>
bool Building::sort_buildings_by_reconstruction_dates(Iterator begin, Iterator end,
	enable_if_t<is_same_v<typename iterator_traits<Iterator>::value_type, Building>, int>*) {
	// Разделение контейнера зданий на здания с датами ректонструкций и без них
	// Перемещает все здания без дат в конец контейнера и возвращает итератор на первое из них
	auto it = partition(begin, end, [](const Building& b) { return !b.get_reconstruction_dates().empty(); });

	if (it == end)
		return false;
	else {
		// Сортировка зданий с датами реконструкции
		sort(begin, it, [](const Building& b1, const Building& b2) {
			return b1.get_reconstruction_dates().back() > b2.get_reconstruction_dates().back(); });
		return true;
	}
}

#endif //! KONDAKOV_LR3_4_BUILDING