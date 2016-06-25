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
		tmp->pNext = tmp + 1;
	}
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
	string st, st1;
	count = 0;
	for (txt.Reset(); !txt.IsTextEnded(); txt.GoNext())
	{
		if (st.find("$$$") != 0)
		{
			st = txt.GetLine();
			st1 = "$$$";
			st1 += txt.GetLine();
			txt.SetLine(st1);
		}
	}
	TLink* pLink = MemHeader.pFree;
	for (  ; pLink != NULL; pLink = pLink->pNext)
	{
		strcpy(pLink->str, "$$$");
	}
	pLink = MemHeader.pFirst;
	for (; pLink <= MemHeader.pLast; pLink++)
	{
		if ( strstr(pLink->str,"$$$") != NULL )
		{
			strcpy(pLink->str, pLink->str+3);
		}
		else 
		{ 
			delete pLink; count++; 
		}
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
		int c = 0;
		cout << "Список содержимого свободных звеньев:" << endl;
		while (tmp != NULL)
		{
			if (tmp->str[0] != '\0')
				cout << tmp->str << endl;
			tmp = tmp->pNext;
			c++;
		}
		cout << "Всего - " << c << " свободных звеньев" << endl;
		cout << endl;
	}
}

int TLink::isAtom()
{
	return pDown == NULL;
}