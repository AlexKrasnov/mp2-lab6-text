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

TText::~TText()
{
	pFirst = NULL;
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

void TText::Reset()
{
	path.Clear();
	pCurr=pFirst;
	if(pCurr!=NULL)
	{
		if(pCurr->pNext!=NULL)
			path.push(pCurr->pNext);
		if(pCurr->pDown!=NULL)
			path.push(pCurr->pDown);
	}
}

void TText::GoNext()
{
	if(!path.empty())
	{
		pCurr=path.pop();
		if(pCurr->pNext!=NULL)
			path.push(pCurr->pNext);
		if(pCurr->pDown!=NULL)
			path.push(pCurr->pDown);
	}
}

int TText::IsTextEnded() const {return path.empty();}

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
