#include "kondakov_lr3_4_load_module.h"

// �������������� �������� ������ �� ��������� �����
// � ������ ��������� � vector
vector<string> LoadModule::get_decoded_buildings_params(ifstream& file) {
    vector<string> building_params;         // ��������� ������
    
    ostringstream buffer;                   // �������� oss ��� �������� �������������� ���������� � �������
    buffer << file.rdbuf();                 // �������������
    string params_string = buffer.str();    // ������� �������������� ���������� � ������

    istringstream params(params_string);    // ������ iss ��� ������������ ������ ���������� �� ������
    string param;                           // ������ ��� �������� ���������

    // ���������� ������ ���������� �� iss � ���������� � vector
    while (getline(params, param))
        building_params.push_back(param);

    return building_params;
}

// �������������� ������ � ����������� ������ � vector ������
vector<Building> LoadModule::get_buildings_from_binary_file(const string& filename) {
    vector<Building> buildings {};
    ifstream file(filename, ios::binary | ios::in);

    if (file.is_open()) {
        // ��������� ������ � ����������� ������
        vector<string> building_params = get_decoded_buildings_params(file);

        int param_id = 1;                   // ����� ��������� (��� ���������������� ������)
        string name;				        // �������� ������
        int height;							// ������ ������
        int square;							// ������� ������
        int volume;							// ����� ������
        vector<int> reconstruction_dates;   // ������ ��� �������������

        // �������� �� ��������� ���������� ���������� ������ � ���������� ���������� � ������:
        // ���� ��� �� ������, ������ ���� ���� �������� ��������� ������, ���� ���-�� ������ ������ ��� ������
        if (building_params.size() % Building::SIZE == 0) {
            for (const string& param : building_params) {
                switch (param_id) {
                case 1: name = param;         break;  // ��������� ��������
                case 2: height = stoi(param); break;  // ��������� ������ � ��������������� � int
                case 3: square = stoi(param); break;  // ��������� ������� � ��������������� � int
                case 4: volume = stoi(param); break;  // ��������� ������ � ��������������� � int
                case 5: [&]() {   // ��� ��� ������ ���������������� ���������� ������ switch-case, ������ ������-�������
                            istringstream years(param);
                            string year;
                            while (getline(years, year, ',')) {
                                year.erase(0, year.find_first_not_of(' '));  // ������� �������� � ������
                                year.erase(year.find_last_not_of(' ') + 1);  // ������ �������� � �����

                                return reconstruction_dates.push_back(stoi(year));  // ��������� ������ ��� �������������
                            }
                        }; break;
                default:
                    cout << "������ ������ ������! ��������� ����������� �������� ������." << endl << endl;
                    file.close();
                    return buildings;
                }
                param_id++;

                if (param_id > Building::SIZE) {  // ��� ���������� ���� ������������ ����������
                    param_id = 1;                 // ����������� ������ ���������� �������� ��������
                    buildings.emplace_back(Building(name, height, square, volume, reconstruction_dates));  // � ������ ������ � �����
                }                                                                                          // ����������� � ����� vector
            }
        }
        else
            cout << "������: ���������� ������ ������ ��� ������ ��������� �����!" << endl << endl;

        file.close();
    }
    return buildings;
}