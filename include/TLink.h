#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define MaxLen 255

#include <string>
#include "TText.h"
#include <iostream>
using namespace std;

class TLink;
class TText;

class TTextMem
{
	TLink *pFirst, *pLast, *pFree;
	friend class TLink;
};

class TLink
{
public:
	char str[MaxLen];    // строка текста
	TLink *pNext;        // указатель на следующую строку текста
	TLink *pDown;        // указатель на подуровень
	static TTextMem MemHeader;   // для управления памятью
	TLink(const char *s = NULL, TLink *pN = NULL, TLink *pD = NULL);
	~TLink();
	static void InitMem(int size);       // инициализация памяти 
	void* operator new(size_t size);     // выделение звена
	void operator delete(void *p);       // освобождение звена
	static void MemCleaner(TText &txt, int &count);    // "сборщик мусора"
	static void PrintFree();             // печать свободных звеньев
	int isAtom();                        // проверка атомарности элемента
};
