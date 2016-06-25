#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "TLink.h"
#include "TStack.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class TLink;

class TText
{
	TLink *pFirst;           // первое звено списка   
	TLink *pCurr;            // текущее звено списка
	TStack <TLink*> path;    // стек для обхода по списку
	TStack <TLink*> St;	     // стек для итератора
public:
	TText(TLink *p=NULL);
	~TText() {};
	void GoFirstLink();				// переход к первой строке
	void GoDownLink();				// переход к следующей строке по Down
	void GoNextLink();				// переход к следующей строке по Next
	void GoPrevLink();				// переход к предыдущей позиции в тексте
	void InsDownLine(string s);	    // вставка строки в подуровень
	void InsDownSection(string s);	// вставка раздела в подуровень
	void InsNextLine(string s);	    // вставка строки в тот же уровень
	void InsNextSection(string s);	// вставка раздела в тот же уровень
	void DelDownLine();			    // удалить строку в подуровне
	void DelDownSection();			// удалить раздел в подуровне
	void DelNextLine();			    // удалить строку в том же уровне
	void DelNextSection();			// удалить раздел в том же уровне
	string GetLine();				// чтение текущей строки
	void SetLine(string s);	        // замена текущей строки
	int Reset();					// установить на первую запись
	int IsTextEnded() const;		// завершён текст или нет?
	int GoNext ();					// переход к следующей записи
	void Load(string f_name);       // загрузить новый текст
	void SaveText(string f_name);   // сохранить текст в файл
	void PrintText();               // напечатать текст
	TLink* ReadSection(ifstream& ifs);  // чтение текста из файла
    void SaveSection(TLink *ptemp, ofstream& ofs); //запись текста со звена в файл
	void PrintSection(TLink *ptemp);    // печать текста со звена ptemp 
	void Navigation();              // навигация по тексту
};