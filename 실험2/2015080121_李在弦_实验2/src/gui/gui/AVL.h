#ifndef AVL_H
#define AVL_H

#include "stdafx.h"
#include <iostream>
#include <string>
#include "My_CharString.h"
#include "HtmlLink.h"
#include <fstream>

class My_AVL;
class CharNode;
typedef enum { NO, YES } numState;

class CharNode
{
public:
	My_CharString Term;
	HtmlLink HL;
	int DF;
	int Occur;
};

class My_AVL
{
public:
	CharNode charNode;
	int lchildNum;
	int rchildNum;
	int maxChildNum;
	int childNum;
	numState numstate;
	My_AVL *lchild, *rchild;

	My_AVL() { charNode.HL.TermID = 0; childNum = 0; lchild = rchild = NULL; maxChildNum = 0; }
	~My_AVL() {};

	int initDictionary(int &MaxDicNum, My_AVL* &curAVL);
	int Insert(wchar_t* &insertWchar, int wsize, My_AVL* &curAVL, long long int ID);
	My_AVL* Search(My_AVL* &curAVL, long long int ID, wchar_t* &searchWord, std::string my_fileName);
	My_AVL* My_AVL::Search(My_AVL* &curAVL, long long int ID, wchar_t* &searchWord);
	int Adjust(My_AVL* &curAVL);
};

#endif