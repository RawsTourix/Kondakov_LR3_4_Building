#ifndef KONDAKOV_LR3_4_LOAD_MODULE_H
#define KONDAKOV_LR3_4_LOAD_MODULE_H

#include "kondakov_lr3_4_save_module.h"

class LoadModule {
public:
	// Раскодирование объектов здания из бинарного файла
	// и запись построчно в vector
	static vector<string> get_decoded_buildings_params(ifstream& file);

	// Преобразование строки с параметрами здания в vector зданий
	static vector<Building> get_buildings_from_binary_file(const string& filename);
};

#endif // !KONDAKOV_LR3_4_LOAD_MODULE_H