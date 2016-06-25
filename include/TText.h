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
	TLink *pFirst;           // ������ ����� ������   
	TLink *pCurr;            // ������� ����� ������
	TStack <TLink*> path;    // ���� ��� ������ �� ������
	TStack <TLink*> St;	     // ���� ��� ���������
public:
	TText(TLink *p=NULL);
	~TText() {};
	void GoFirstLink();				// ������� � ������ ������
	void GoDownLink();				// ������� � ��������� ������ �� Down
	void GoNextLink();				// ������� � ��������� ������ �� Next
	void GoPrevLink();				// ������� � ���������� ������� � ������
	void InsDownLine(string s);	    // ������� ������ � ����������
	void InsDownSection(string s);	// ������� ������� � ����������
	void InsNextLine(string s);	    // ������� ������ � ��� �� �������
	void InsNextSection(string s);	// ������� ������� � ��� �� �������
	void DelDownLine();			    // ������� ������ � ���������
	void DelDownSection();			// ������� ������ � ���������
	void DelNextLine();			    // ������� ������ � ��� �� ������
	void DelNextSection();			// ������� ������ � ��� �� ������
	string GetLine();				// ������ ������� ������
	void SetLine(string s);	        // ������ ������� ������
	int Reset();					// ���������� �� ������ ������
	int IsTextEnded() const;		// �������� ����� ��� ���?
	int GoNext ();					// ������� � ��������� ������
	void Load(string f_name);       // ��������� ����� �����
	void SaveText(string f_name);   // ��������� ����� � ����
	void PrintText();               // ���������� �����
	TLink* ReadSection(ifstream& ifs);  // ������ ������ �� �����
    void SaveSection(TLink *ptemp, ofstream& ofs); //������ ������ �� ����� � ����
	void PrintSection(TLink *ptemp);    // ������ ������ �� ����� ptemp 
	void Navigation();              // ��������� �� ������
};