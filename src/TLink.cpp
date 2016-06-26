#include "TLink.h"

TLink::TLink(const char *s, TLink *pN, TLink *pD):pNext(pN),pDown(pD)
{
	if(s!=NULL)
		strcpy_s(str,s);
	else str[0]='\0';
}

TLink::~TLink(){}

void TLink::InitMem(int size)
{
	MemHeader.pFirst = (TLink*) new char[size*sizeof(TLink)];
	MemHeader.pFree = MemHeader.pFirst;
	MemHeader.pLast = MemHeader.pFirst + (size - 1);
	TLink *tmp = MemHeader.pFirst;
	for (int i = 0; i < size - 1; i++, tmp++) // размерка памяти
	{
		tmp->str[0] = '\0';
		tmp->pNext = tmp + 1;
	}
	tmp->str[0] = '\0';
	tmp->pNext = NULL;
}

void* TLink::operator new(size_t size)
{
	TLink *tmp = MemHeader.pFree;
	if (tmp!= NULL)
		MemHeader.pFree = tmp->pNext;
	return tmp;
}

void TLink::operator delete(void* p)
{
	TLink *tmp = (TLink*)p;
	tmp->pNext = MemHeader.pFree;
	MemHeader.pFree = tmp;
}

void TLink::MemClean(TText &txt, int &count)
{
	count = 0;
	string s = "$$$";
	for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
	{
		s += txt.GetLine();
		txt.SetLine(s.c_str());
	}
	txt.SetLine(s.c_str());
	TLink *tmp = MemHeader.pFree;
	while (tmp != NULL)
	{
		for (int i = 0; i < 3; i++)
			tmp->str[i] = '$';
		tmp->str[3] = '\0';
		tmp = tmp->pNext;
	}
	tmp = MemHeader.pFirst;
	while (true)
	{
		if ((tmp->str[0] == '$') && (tmp->str[1] == '$') && (tmp->str[2] == '$'))
			strcpy(tmp->str, tmp->str + 3);
		else
		{
			delete tmp;
			count++;
		}
		if (tmp == MemHeader.pLast)
			break;
		tmp = tmp + 1;
	}
}

void TLink::PrintFree()
{
	setlocale(LC_ALL, "Rus");
	TLink *tmp = MemHeader.pFree;
	if (tmp == NULL)
		cout << "Нет свободных звеньев" << endl;
	else
	{
		int count = 0;
		cout << "Список содержимого свободных звеньев:" << endl;
		while (tmp != NULL)
		{
			if (tmp->str[0] != '\0')
				cout << tmp->str << endl;
			tmp = tmp->pNext;
			count++;
		}
		cout << "Всего - " << count << " свободных звеньев" << endl;
	}
}

int TLink::isAtom()
{
	return pDown == NULL;
}