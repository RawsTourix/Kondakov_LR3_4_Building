#include "kondakov_lr3_4_load_module.h"

// –аскодирование объектов здани€ из бинарного файла
// и запись построчно в vector
vector<string> LoadModule::get_decoded_buildings_params(ifstream& file) {
    vector<string> building_params;         // параметры зданию
    
    ostringstream buffer;                   // создание oss дл€ хранени€ декодированной информации о здани€х
    buffer << file.rdbuf();                 // декодирование
    string params_string = buffer.str();    // перенос декодированной информации в строку

    istringstream params(params_string);    // создаЄм iss дл€ посторочного чтени€ параметров из строки
    string param;                           // строка дл€ хранени€ параметра

    // ѕострочное чтение параметров из iss и добавление в vector
    while (getline(params, param))
        building_params.push_back(param);

    return building_params;
}

// ѕреобразование строки с параметрами здани€ в vector зданий
vector<Building> LoadModule::get_buildings_from_binary_file(const string& filename) {
    vector<Building> buildings {};
    ifstream file(filename, ios::binary | ios::in);

    if (file.is_open()) {
        // ѕолучение строки с параметрами зданий
        vector<string> building_params = get_decoded_buildings_params(file);

        int param_id = 1;                   // номер параметра (дл€ последовательной записи)
        string name;				        // название здани€
        int height;							// высота здани€
        int square;							// площадь здани€
        int volume;							// объЄм здани€
        vector<int> reconstruction_dates;   // список дат реконструкции

        // ѕроверка на кратности количества параметров здани€ и количество параметров в строке:
        // если они не кратны, значит либо была изменена структура здани€, либо где-то ошибка чтени€ или записи
        if (building_params.size() % Building::SIZE == 0) {
            for (const string& param : building_params) {
                switch (param_id) {
                case 1: name = param;         break;  // получение названи€
                case 2: height = stoi(param); break;  // получение высоты с преобразованием в int
                case 3: square = stoi(param); break;  // получение площади с преобразованием в int
                case 4: volume = stoi(param); break;  // получение объЄма с преобразованием в int
                case 5: [&]() {   // так как нельз€ инициализировать переменные внутри switch-case, создаю л€мбда-функцию
                            istringstream years(param);
                            string year;
                            while (getline(years, year, ',')) {
                                year.erase(0, year.find_first_not_of(' '));  // очистка пробелов в начале
                                year.erase(year.find_last_not_of(' ') + 1);  // очиска пробелов в конце

                                return reconstruction_dates.push_back(stoi(year));  // получение списка дат реконструкции
                            }
                        }; break;
                default:
                    cout << "ќшибка записи данных! ќбнаружен неизвестный параметр здани€." << endl << endl;
                    file.close();
                    return buildings;
                }
                param_id++;

                if (param_id > Building::SIZE) {  // при заполнении всех существующих параметров
                    param_id = 1;                 // присваиваем номеру параметров исходное значение
                    buildings.emplace_back(Building(name, height, square, volume, reconstruction_dates));  // и создаЄм здание с этими
                }                                                                                          // параметрами в конце vector
            }
        }
        else
            cout << "ќшибка: обнаружены лишние данные при чтении бинарного файла!" << endl << endl;

        file.close();
    }
    return buildings;
}