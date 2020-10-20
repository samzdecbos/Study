
#include <fstream>
#include <iostream>
#include <math.h>
#include <cstring>
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus"); // корректное отображение Кириллицы
    char buff;
    unsigned char unbuff;
    int asciibuff;
    unsigned long int num[256][2];
    string names[] = {"Arh23.rar","Pic23.bmp","Pic23.jpg","text23.doc","text23.docx","text23.txt"};
    
    for (int ll = 0; ll < 6; ll++) {
        ifstream fin(names[ll], ios_base::binary); // открыли файл для чтения

        for (int i = 0; i < 256; i++) {
            num[i][0] = 0;
            num[i][1] = i;
        }

        if (fin.is_open()) {
            while (!fin.eof()) {
                fin.read(&buff, 1);
                unbuff = buff;
                asciibuff = unbuff;
                for (int i = 0; i < 256; i++)
                {
                    if (asciibuff == i) num[i][0]++;
                }
            }
        }
        else {
            cout << "Файл не открыт" << endl;
        }

        fin.close(); // закрываем файл

        ofstream fout(names[ll]+".tab", ios_base::out);

        double sum = 0.0;
        for (int i = 0; i < 256; i++)
            sum = sum + num[i][0];

        double entropy = 0;
        for (int i = 0; i < 256; i++)
        {
            if (num[i][0] != 0) {
                entropy = entropy - (num[i][0] / sum) * log2(num[i][0] / sum);
            }
        }

        cout << "энтропия " + names[ll] + "= " << entropy << endl;

        fout << "энтропия = " << entropy << endl;

        for (int i = 0; i < 255; i++) {
            for (int j = 0; j < 255 - i; j++) {
                if (num[j][0] < num[j + 1][0]) {
                    // меняем элементы местами
                    for (int k = 0; k < 2; k++) {
                        int temp = num[j][k];
                        num[j][k] = num[j + 1][k];
                        num[j + 1][k] = temp;
                    }

                }
            }
        }

        fout << endl;
        for (int i = 0; i < 256; i++) {
            if (num[i][0] != 0) {
                fout << num[i][0] << "\t" << num[i][1] << endl;
            }
        }
    }

    return 0;
}