#include "My_HashTable.h"
#include "My_CharStringLink.h"
#include "My_CharString.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int My_HashTable::initDictionary(void)
{
	ifstream inputFile(L"词库/词库.dic");
	string newWord;
	My_CharString check;
	
	int num = 0;
	int numWord = 0;
	int i = 0;


	if (!inputFile.is_open())
	{
		cout << "ERROR 3" << endl;
		inputFile.close();
		return 0;
	}


	while (!inputFile.eof())
	{
		num = 0;
		numWord = 0;
		getline(inputFile, newWord); //读入一个单词
		check.MBtoWC(newWord); //把“string”转成“wchar_t”变量形式
		num = check.w_size;

		if (num > maxNumWord)
		{
			maxNumWord = num; //获得最大长度
		}

		for (i = 1; i <= num; i++)
		{
			numWord += (i*(check.w_str[i - 1])); //获得字符串链表数组的“index”值
		}

		m_HashTable[numWord % 1000].add(newWord); //保存在字符串链表数组里面

	}
	return 0;
}

wchar_t* My_HashTable::FineSameWord(wchar_t* &e)
{
	int eLength = 0;
	int i = 0;
	int eKey = 0;
	wchar_t * result;



	for (eLength = 0; e[eLength] != '\0'; eLength++); //获得字符串长度

	for (i = 1; i <= eLength; i++)
	{
		eKey += (i*e[i-1]); //这个字符串有可能在m_HashTable[eKey]里面
	}

	eKey = eKey % 1000;

	result = m_HashTable[eKey].search(e);//判断这个字符串是不是单词

	return result;
}