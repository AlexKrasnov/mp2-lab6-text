#include "TText.h"

TText::TText(TLink *p): path(100)
{
	if (p==NULL)
	{
		TLink *tmp=new TLink;
		pFirst=tmp;
	}
	else pFirst=p;
}

void TText::GoFirstLink()
{
	if (pCurr!=NULL)
	while (!path.empty())
		path.pop();
	pCurr=pFirst;
}

void TText::GoDownLink()
{
	if (pCurr!=NULL)
		if (pCurr->pDown!=NULL)
		{
			path.push(pCurr);
			pCurr=pCurr->pDown;
		}
}

void TText::GoNextLink()
{
	if (pCurr!=NULL)
		if (pCurr->pNext!=NULL)
		{
			path.push(pCurr);
			pCurr=pCurr->pNext;
		}
}

void TText::GoPrevLink()
{
	if (pCurr!=NULL)
	if (!path.empty())
		pCurr=path.pop();
}

void TText::InsDownLine(string s)
{
	if(pCurr!=NULL)
	{
		const string st = s;
		TLink *tmp = new TLink(st.c_str());
	    tmp->pNext=pCurr->pDown;
	    pCurr->pDown=tmp;
	}
}

void TText::InsDownSection(string s)
{
	if(pCurr!=NULL)
	{
		const string st = s;
		TLink *tmp = new TLink(st.c_str());
	    tmp->pDown=pCurr->pDown;
	    pCurr->pDown=tmp;
	}
}

void TText::InsNextLine(string s)
{
	if(pCurr!=NULL)
	{
		const string st = s;
		TLink *tmp=new TLink(st.c_str());
	    tmp->pNext=pCurr->pNext;
	    pCurr->pNext=tmp;
	}
}

void TText::InsNextSection(string s)
{
	if(pCurr!=NULL)
	{
		const string st = s;
		TLink *tmp=new TLink(st.c_str());
	    tmp->pDown=pCurr->pNext;
	    pCurr->pNext=tmp;
	}
}

void TText::DelDownLine()
{
	if(pCurr!=NULL)
		if(pCurr->pDown!=NULL)
		{
			TLink *tmp=pCurr->pDown;
			pCurr->pDown=pCurr->pDown->pNext;
			delete tmp;
		}
}

void TText :: DelDownSection()
{
	if (pCurr!=NULL)
	if (pCurr->pDown != NULL)
	{
		TLink* tmp1 = pCurr->pDown;
		TLink* tmp2 = tmp1->pNext;
		pCurr->pDown = tmp2;
	}
}

void TText::DelNextLine()
{
	if(pCurr!=NULL)
		if (pCurr->pNext!=NULL)
		{
			TLink *tmp=pCurr->pNext;
			pCurr->pNext=pCurr->pNext->pNext;
			delete tmp;
		}
}

void TText::DelNextSection ()
{
	if (pCurr!=NULL)
	if ( pCurr->pNext != NULL )
	{
		TLink* tmp1 = pCurr->pDown;
		TLink* tmp2 = tmp1->pNext;
		pCurr->pNext = tmp2;
	}
}

string TText::GetLine()
{
	char s[MaxLen];
	if(pCurr!=NULL)
		strcpy(s,pCurr->str);
	return s;
}

void TText::SetLine(string _str)
{
	const string s = _str;
	if(pCurr!=NULL)
		strcpy(pCurr->str,s.c_str());
}

int TText :: Reset(void)
{
	while (!St.empty())
		St.pop();
	pCurr = pFirst;
	if (pCurr != NULL)
	{
		St.push(pCurr);
		if (pCurr->pNext != NULL)
			St.push(pCurr->pNext);
		if (pCurr->pDown != NULL)
			St.push(pCurr->pDown);
	}
	return IsTextEnded();
}

int TText :: IsTextEnded(void) const
{
	return !St.GetSize();
}

int TText :: GoNext(void)
{
	if ( !IsTextEnded() )
	{
		pCurr = St.pop();
		if (pCurr!=pFirst)
		{
			if (pCurr->pNext != NULL)
				St.push(pCurr->pNext);
			if (pCurr->pDown != NULL)
				St.push(pCurr->pDown);
		}
	}
	return IsTextEnded();
}

TLink* TText::ReadSection(ifstream& ifs)
{
	string _str;
	TLink *pHead, *ptemp;
	pHead = new TLink;
	ptemp = pHead;
	while (!ifs.eof())
	{
		getline(ifs, _str);
		if (_str[0] == ' ') break;
		if (_str[0] == ' ') ptemp->pDown = ReadSection(ifs);
		else
		{
			TLink *p = new TLink(_str.c_str());
			ptemp->pNext = p;
			ptemp = p;
		}
	}
	if (pHead->pDown == NULL)
	{
		ptemp = pHead->pNext;
		delete pHead;
		pHead = ptemp;
	}
	return pHead;
}

void TText::LoadText(string f_name)
{
	ifstream ifs(f_name);
	pFirst = ReadSection(ifs);
	pCurr = pFirst;
}

void TText::PrintSection(TLink *ptemp)
{
	if (ptemp != NULL)
	{
		cout << ptemp->str << endl;
		if (ptemp->pDown != NULL)
		{
			cout << ' ';
			PrintSection(ptemp->pDown);
			cout << ' ';
		}
		PrintSection(ptemp->pNext);
	}
}

void TText::PrintText() { PrintSection(pFirst); }

void TText::SaveSection(TLink *ptemp, ofstream& ofs)
{
	if (ptemp != NULL)
	{
		ofs << ptemp->str << endl;
		if (ptemp->pDown != NULL)
		{
			ofs << ' ';
			SaveSection(ptemp->pDown,ofs);
			ofs << ' ';
		}
		SaveSection(ptemp->pNext,ofs);
	}
}

void TText::SaveText(string f_name)
{
	ofstream ofs(f_name);
	SaveSection(pFirst, ofs);
}

void TText::Navigation()
{
	int k;
	do
	{
		string tmp = ">>> ";
		tmp += GetLine();
		SetLine(tmp.c_str());
		PrintText();
		SetLine(pCurr->str + 4);
		cout << endl;
		cout << "Введите номер действия:" << endl;
		cout << "1. Перейти на первое звено" << endl;
		cout << "2. Перейти на следующее звено" << endl;
		cout << "3. Перейти на вложенное звено" << endl;
		cout << "4. Перейти на предыдущее звено" << endl;
		cout << "5. Выход из навигации" << endl;
		cin >> k;
		switch (k)
		{
		case 1: GoFirstLink();
			break;
		case 2: GoNextLink();
			break;
		case 3: GoDownLink();
			break;
		case 4: GoPrevLink();
			break;
		case 5: break;
		default: cout << "Некорректный ввод! Введите номер операции заново." << endl;
		}
	} while (k != 5);
}