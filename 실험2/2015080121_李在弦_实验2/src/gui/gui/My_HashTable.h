#ifndef MY_HASHTABLE_H
#define MY_HASHTABLE_H

#include "stdafx.h"
#include "My_CharStringLink.h"

class My_HashTable
{
public:
	My_CharStringLink m_HashTable[1000];
	int maxNumWord;
public:
	My_HashTable()
	{
		maxNumWord = 0;
	}
	~My_HashTable() {};

	int initDictionary(void);
	wchar_t* FineSameWord(wchar_t* &e);

};

#endif MY_HASHTABLE_H
