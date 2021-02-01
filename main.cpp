#include <iostream>
using namespace std;
#include <fstream>
#include <string>

void compress(string sourseFileName, string zipFileName)
{
    char key, ch;
    string str;
    int freq = 1;

    ifstream fin(sourseFileName); // исходный файл
    ofstream fcom(zipFileName);   // файл, в котором будет результат выаоления действий

    fin >> key;

    while (getline(
        fin, str)) // читение данных построчно, пока не будут прочитаны все строки
    {
        for (int i = 0; i <= str.length();
             i++) // читение по одному символу из строки
        {
            if (i == str.length()) // если все символы из строки были прочитаны
            {
                fcom << key << freq << endl;
                key = fin.peek();
                freq = 0;
                break;
            }
            else if (key == str[i])
            {
                freq++;
            }
            else
            {
                fcom << key << freq;
                key = str[i];
                freq = 1;
            }
        }
    }

    fin.close();
    fcom.close();

    cout << "АРХИВИРОВАНИЕ ПРОШЛО УСПЕШНО!" << endl;
}

void decompress(string sourseFileName, string zipFileName)
{
    string str;
    int freq;
    int index;
    char key;

    ifstream fcom(sourseFileName); // файл для распаковки
    ofstream fdecom(
        zipFileName); // файл, в котором будут храниться распакованные данные

    while (getline(fcom, str))
    {
        for (int i = 0; i < str.length();
             i += 2) //  чтение двух битов строки за одну итерацию, поэтому шаги 2
        {
            key = str[i];
            freq = str[i + 1] - 48; // чтобы преобразовать значение ascii чисел в целое число

            index = 1;
            while (index <= freq)
            {
                fdecom << key;
                index++;
            }
        }
        fdecom << endl;
    }

    fcom.close();
    fdecom.close();

    cout << "РАЗАРХИВИРОВАНИЕ ПРОШЛО УСПЕШНО!" << endl;
}

int main()
{
    int choice;
    string sourseFileName;
    string zipFileName;
    
    cout << "1. Архивировать файл" << endl;
    cout << "2. Разархивировать файл" << endl;
    cout << "3. Выход" << endl;
    while (1)
    {
        cin >> choice;

        switch (choice)
        {
        case 1: // архивировать
            cout << "Введите путь файла для архивиции, либо путь ранее заархивированного файла: " << endl;
            cin >> sourseFileName;
            cout << "Введите имя файла, где будет результат выполнения действия" << endl;
            cin >> zipFileName;
            compress(sourseFileName, zipFileName);
            cin.get();
            break;
        case 2: // разархивировать
            cout << "Введите путь файла для архивиции, либо путь ранее заархивированного файла:" << endl;
            cin >> sourseFileName;
            cout << "Введите имя файла, где будет результат выполнения действия" << endl;
            cin >> zipFileName;
            decompress(sourseFileName, zipFileName);
            cin.get();
            break;
        case 3: //выход
            exit(0);
        default:
            cout << "ОШИБКА: выберите действие!" << endl;
        }
    }
    return 0;
}
