#ifndef KONDAKOV_LR3_4_SAVE_MODULE_H
#define KONDAKOV_LR3_4_SAVE_MODULE_H

#include "kondakov_lr3_4_building.h"

class SaveModule {
public:
    // ������������� ������ ������ � ������ ������� ��� ���������� � ����
    template <typename Iterator>
    static string parse_buildings_to_save(Iterator begin, Iterator end);

    // �������� ������ � ������� � �������� ����
    template <typename Iterator>
    static bool save_buildings_to_bin(Iterator begin, Iterator end, const string& filename);
};

#endif // !KONDAKOV_LR3_4_SAVE_MODULE_H