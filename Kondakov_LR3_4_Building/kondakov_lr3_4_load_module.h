#ifndef KONDAKOV_LR3_4_LOAD_MODULE_H
#define KONDAKOV_LR3_4_LOAD_MODULE_H

#include "kondakov_lr3_4_save_module.h"

class LoadModule {
public:
	// �������������� �������� ������ �� ��������� �����
	// � ������ ��������� � vector
	static vector<string> get_decoded_buildings_params(ifstream& file);

	// �������������� ������ � ����������� ������ � vector ������
	static vector<Building> get_buildings_from_binary_file(const string& filename);
};

#endif // !KONDAKOV_LR3_4_LOAD_MODULE_H