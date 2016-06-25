#include "TText.h"
#include <clocale>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

TTextMem TLink::MemHeader;

string input()
{
	string str2, str1, res;
	cin >> str1;
	getline(cin, str2);
	return str1 + str2;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	TLink::InitMem(100);
	TText t;
	string str;
	//cout << "Введите имя документа с текстом:" << endl;
	//getline(cin, str);
	t.LoadText("file.txt");
	int n;
	do
	{
		cout << "Введите номер операции:" << endl;
		cout << "1. Вывести на экран текущий текст" << endl;
		cout << "2. Загрузить новый текст из файла" << endl;
		cout << "3. Вставить строку в текст в данную секцию" << endl;
		cout << "4. Вставить строку в текст в нижнюю секцию" << endl;
		cout << "5. Вставить строку в текст в данную секцию с созданием нижней секции" << endl;
		cout << "6. Вставить строку в текст в нижнюю секцию с созданием нижней секции" << endl;
		cout << "7. Удалить строку из текста в данной секции" << endl;
		cout << "8. Удалить строку из текста в нижней секции" << endl;
		cout << "9. Вывести данную строку" << endl;
		cout << "10. Редактировать данную строку" << endl;
		cout << "10. Навигация по тексту" << endl;
		cout << "12. Вывести список свободных звеньев" << endl;
		cout << "13. Сборщик мусора" << endl;
		cout << "14. Сохранить текст в файл" << endl;
		cout << "15. Завершение работы" << endl;
		cin >> n;
		switch (n)
		{
		case 1: cout << endl;
			t.PrintText();
			break;

		case 2: cout << "Введите имя документа с текстом:" << endl;
			cin.get();
			getline(cin, str);
			t.LoadText(str);
			break;

		case 3: cout << "Введите текст, который хотите добавить:" << endl;
			cin.get();
			getline(cin, str);
			t.InsNextLine(str);
			cout << endl;
			t.PrintText();
			break;

		case 4: cout << "Введите текст, который хотите добавить:" << endl;
			cin.get();
			getline(cin, str);
			t.InsDownLine(str);
			cout << endl;
			t.PrintText();
			break;

		case 5: cout << "Введите текст, который хотите добавить:" << endl;
			cin.get();
			getline(cin, str);
			t.InsNextSection(str);
			cout << endl;
			t.PrintText();
			break;

		case 6: cout << "Введите текст, который хотите добавить:" << endl;
			cin.get();
			getline(cin, str);
			t.InsDownSection(str);
			cout << endl;
			t.PrintText();
			break;

		case 7:	t.DelNextLine();
			cout << endl;
			t.PrintText();
			break;

		case 8: t.DelDownLine();
			cout << endl;
			t.PrintText();
			break;

		case 9: cout << "Данная строка:" << endl;
			cout << t.GetLine() << endl;
			break;

		case 10: cout << "Введите текст, который хотите добавить:" << endl;
			cin.get();
			getline(cin, str);
			t.SetLine(str);
			cout << endl;
			t.PrintText();
			break;

		case 11: t.Navigation();
			break;

		case 12: TLink::PrintFree();
			break;

		case 13: int k;
			TLink::MemClean(t, k); 
			cout << "Удалено" << k << "элементов" << endl;
			break;

		case 14: cout << "Введите имя документа, в который хотите сохранить текст:" << endl;
			cin.get();
			getline(cin, str);
			t.SaveText(str);
			break;

		case 15: break;

		default: cout << "Некорректный ввод! Введите номер операции заново." << endl;
		}
		cout << endl;
	} while (n!=15);
	return 0;
}