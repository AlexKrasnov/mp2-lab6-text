#include "TText.h"
#include <clocale>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

TTextMem TLink::MemHeader;

void main()
{
	try
	{
		setlocale(LC_ALL, "Rus");
		TLink::InitMem(100);
		TText t;
		string str;
		//cout << "Введите имя документа с текстом:" << endl;
		//getline(cin, str);
		//t.LoadText(str);
		t.LoadText("file.txt");
		int n;
		cout << "\t\t***ЛР 6. Редактирование текстов***\n\n";
		do
		{
			cout << "Введите номер операции:" << endl;
			cout << "1. Вывести на экран текущий текст" << endl;
			cout << "2. Загрузить новый текст из файла" << endl;
			cout << "3. Вставить строку в данный уровень" << endl;
			cout << "4. Вставить строку в нижний уровень" << endl;
			cout << "5. Вставить раздел в данный уровень" << endl;
			cout << "6. Вставить раздел в нижний уровень" << endl;
			cout << "7. Удалить строку из данного уровня" << endl;
			cout << "8. Удалить строку из нижнего уровня" << endl;
			cout << "9. Удалить раздел из данного уровня" << endl;
			cout << "10. Удалить раздел из нижнего уровня" << endl;
			cout << "11. Вывести текущую строку" << endl;
			cout << "12. Изменить текущую строку" << endl;
			cout << "13. Вывести список свободных звеньев" << endl;
			cout << "14. Сборщик мусора" << endl;
			cout << "15. Перейти на первое звено" << endl;
			cout << "16. Перейти на следующее звено" << endl;
			cout << "17. Перейти на вложенное звено" << endl;
			cout << "18. Перейти на предыдущее звено" << endl;	
			cout << "19. Сохранить текст в файл" << endl;
			cout << "20. Выход" << endl;
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

			case 9:	t.DelNextSection();
				cout << endl;
				t.PrintText();
				break;

			case 10: t.DelDownSection();
				cout << endl;
				t.PrintText();
				break;

			case 11: cout << "Данная строка:" << endl;
				cout << t.GetLine() << endl;
				break;

			case 12: cout << "Введите текст, который хотите добавить:" << endl;
				cin.get();
				getline(cin, str);
				t.SetLine(str);
				cout << endl;
				t.PrintText();
				break;

			case 13: TLink::PrintFree();
				break;

			case 14: int k;
				TLink::MemCleaner(t, k); 
				cout << "Удалено " << '('<< k << ')' << endl;
				break;

			case 15: t.GoFirstLink();
				break;

			case 16: t.GoNextLink();
				break;

			case 17: t.GoDownLink();
				break;

			case 18: t.GoPrevLink();
				break;

			case 19: cout << "Введите имя документа, в который хотите сохранить текст:" << endl;
				cin.get();
				getline(cin, str);
				t.SaveText(str);
				break;

			case 20: break;

			default: cout << "Некорректный ввод! Введите номер операции заново." << endl;
			}
			cout << endl;
		} while (n!=20);
	}
	catch (const char* error)
	{
		cout << error << endl;
	}
}
