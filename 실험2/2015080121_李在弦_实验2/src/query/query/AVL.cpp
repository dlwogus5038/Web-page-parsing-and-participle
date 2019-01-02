#include "AVL.h"
#include "HtmlLink.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int My_AVL::initDictionary(int &MaxDicNum, My_AVL* &curAVL)
{
	ifstream inputFile(L"词库/词库.dic");
	string newWord;
	My_CharString check;

	int num = 0;
	long long int numWord = 0;
	int i = 0;

	if (!inputFile.is_open())
	{
		cout << "DICTIONARY ERROR" << endl;
		inputFile.close();
		return 0;
	}


	while (!inputFile.eof())
	{
		num = 0;
		numWord = 0;
		getline(inputFile, newWord); //?入一???
		check.MBtoWC(newWord); //把“string”?成“wchar_t”?量形式
		num = check.w_size;

		if (num > MaxDicNum)
			MaxDicNum = num; //?得最大?度
		//max 65295

		
		for (i = 1; i <= check.w_size; i++)
			numWord += (i*(check.w_str[i - 1])); //获得字符串链表数组的“index”值

		numWord = numWord % 100000;
		numWord += check.w_str[0] * 100000;
		numWord += (check.w_str[i-1] % 1000) * 1000000000;
		numWord += check.w_size * 1000000000000;

		Insert(check.w_str,check.w_size, curAVL, numWord); //保存在字符串?表??里面

	}

	return 0;
}

int My_AVL::Insert(wchar_t* &insertWchar,int wsize, My_AVL* &curAVL ,long long int ID)
{
	int insertState = 0;
	int maxNum = 0;
	int CharNum = 0;
	int i = 0;
	int j = 0;

	if (curAVL == this && curAVL->numstate == NO)
	{
		curAVL->charNode.HL.TermID = ID;

		curAVL->charNode.Term.w_size = wsize;
		curAVL->charNode.Term.w_str = new wchar_t[wsize + 1];
		for (j = 0; j < wsize; j++)
		{
			curAVL->charNode.Term.w_str[j] = insertWchar[j];
		}
		curAVL->charNode.Term.w_str[j] = '\0';

		curAVL->numstate = YES;
		return 0;
	}

	if (curAVL == NULL)
	{
		curAVL = new My_AVL;
		curAVL->charNode.HL.TermID = ID;

		curAVL->charNode.Term.w_size = wsize;
		curAVL->charNode.Term.w_str = new wchar_t[wsize + 1];
		for (j = 0; j < wsize; j++)
		{
			curAVL->charNode.Term.w_str[j] = insertWchar[j];
		}
		curAVL->charNode.Term.w_str[j] = '\0';

		curAVL->numstate = YES;
		return 1;
	}

	if (ID == curAVL->charNode.HL.TermID)
		return 0;

	if (ID > curAVL->charNode.HL.TermID)
	{
		insertState = Insert(insertWchar, wsize, curAVL->rchild, ID);

		if (insertState != 0)
		{
			if (curAVL->rchild != NULL)
				curAVL->rchildNum = curAVL->rchild->maxChildNum + 1;
			if (curAVL->lchild != NULL)
				curAVL->lchildNum = curAVL->lchild->maxChildNum + 1;

			if (curAVL->rchildNum > curAVL->lchildNum)
			{
				maxNum = curAVL->rchildNum;
			}
			else
			{
				maxNum = curAVL->lchildNum;
			}

			curAVL->maxChildNum = maxNum;

			curAVL->childNum = curAVL->lchildNum - curAVL->rchildNum;

			Adjust(curAVL);

			return 1;
		}

		return 0;
	}
	else
	{
		insertState = Insert(insertWchar, wsize, curAVL->lchild, ID);

		if (insertState != 0)
		{
			if (curAVL->lchild != NULL)
				curAVL->lchildNum = curAVL->lchild->maxChildNum + 1;
			if (curAVL->rchild != NULL)
				curAVL->rchildNum = curAVL->rchild->maxChildNum + 1;

			if (curAVL->rchildNum > curAVL->lchildNum)
			{
				maxNum = curAVL->rchildNum;
			}
			else
			{
				maxNum = curAVL->lchildNum;
			}

			curAVL->maxChildNum = maxNum;

			curAVL->childNum = curAVL->lchildNum - curAVL->rchildNum;

			Adjust(curAVL);

			return 1;
		}

		return 0;
	}
}

My_AVL* My_AVL::Search(My_AVL* &curAVL, long long int ID,wchar_t* &searchWord, std::string my_fileName)
{
	My_AVL *result = NULL;
	int fileNameSize = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int docID = 0;

	if (curAVL == NULL)
	{
		return NULL;
	}

	if (ID == curAVL->charNode.HL.TermID)
	{
		for (i = 0; searchWord[i] != '\0'; i++);

		if (i == curAVL->charNode.Term.w_size)
		{
			for (j = 0; j < i; j++)
			{
				if (curAVL->charNode.Term.w_str[j] != searchWord[j])
					return NULL;
			}
		}

		fileNameSize = my_fileName.size();

		for (k = 0; k < fileNameSize; k++)
		{
			docID *= 10;
			docID += my_fileName[k] - '0';
		}
		
		curAVL->charNode.HL.Add(docID);

		return curAVL;
	}

	else if (ID > curAVL->charNode.HL.TermID)
	{
		result = Search(curAVL->rchild, ID, searchWord, my_fileName);
		return result;
	}
	else if (ID < curAVL->charNode.HL.TermID)
	{
		result = Search(curAVL->lchild, ID, searchWord, my_fileName);
		return result;
	}
	else
	{
		return NULL;
	}
}

My_AVL* My_AVL::Search(My_AVL* &curAVL, long long int ID, wchar_t* &searchWord)
{
	My_AVL *result = NULL;
	int fileNameSize = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int docID = 0;

	if (curAVL == NULL)
	{
		return NULL;
	}

	if (ID == curAVL->charNode.HL.TermID)
	{
		for (i = 0; searchWord[i] != '\0'; i++);

		if (i == curAVL->charNode.Term.w_size)
		{
			for (j = 0; j < i; j++)
			{
				if (curAVL->charNode.Term.w_str[j] != searchWord[j])
					return NULL;
			}
		}

		return curAVL;
	}

	else if (ID > curAVL->charNode.HL.TermID)
	{
		result = Search(curAVL->rchild, ID, searchWord);
		return result;
	}
	else if (ID < curAVL->charNode.HL.TermID)
	{
		result = Search(curAVL->lchild, ID, searchWord);
		return result;
	}
	else
	{
		return NULL;
	}
}

int My_AVL::Adjust(My_AVL* &curAVL)
{
	My_AVL *A, *B, *C, *D;
	int maxNum = 0;

	if (curAVL == NULL)
		return 0;
	if (curAVL != NULL && curAVL->lchild != NULL)
	{
		if (curAVL->childNum == 2
			&& curAVL->lchild->childNum == 1)
		{

			A = curAVL;
			B = curAVL->lchild;
			C = curAVL->lchild->rchild;

			A->lchild = C;
			B->rchild = A;
			curAVL = B;

			if (A->lchild != NULL)
				A->lchildNum = A->lchild->maxChildNum + 1;
			else
				A->lchildNum = 0;

			if (A->rchild != NULL)
				A->rchildNum = A->rchild->maxChildNum + 1;
			else
				A->rchildNum = 0;

			if (A->lchildNum > A->rchildNum)
				A->maxChildNum = A->lchildNum;
			else
				A->maxChildNum = A->rchildNum;

			A->childNum = A->lchildNum - A->rchildNum;

			if (B->lchild != NULL)
				B->lchildNum = B->lchild->maxChildNum + 1;
			else
				B->lchildNum = 0;

			if (B->rchild != NULL)
				B->rchildNum = B->rchild->maxChildNum + 1;
			else
				B->rchildNum = 0;

			if (B->lchildNum > B->rchildNum)
				B->maxChildNum = B->lchildNum;
			else
				B->maxChildNum = B->rchildNum;

			B->childNum = B->lchildNum - B->rchildNum;

			A->childNum = A->lchildNum - A->rchildNum;
			B->childNum = B->lchildNum - B->rchildNum;

		}
		if (curAVL->lchild->rchild != NULL)
		{
			if (curAVL->childNum == 2
				&& curAVL->lchild->childNum == -1)
			{

				A = curAVL;
				B = curAVL->lchild;
				C = curAVL->lchild->rchild;
				D = curAVL->lchild->rchild->lchild;

				B->rchild = D;
				C->lchild = B;
				A->lchild = C;

				A->lchild = C->rchild;
				C->rchild = A;
				curAVL = C;

				if (A->lchild != NULL)
					A->lchildNum = A->lchild->maxChildNum + 1;
				else
					A->lchildNum = 0;

				if (A->rchild != NULL)
					A->rchildNum = A->rchild->maxChildNum + 1;
				else
					A->rchildNum = 0;

				if (A->lchildNum > A->rchildNum)
					A->maxChildNum = A->lchildNum;
				else
					A->maxChildNum = A->rchildNum;

				A->childNum = A->lchildNum - A->rchildNum;

				if (B->lchild != NULL)
					B->lchildNum = B->lchild->maxChildNum + 1;
				else
					B->lchildNum = 0;

				if (B->rchild != NULL)
					B->rchildNum = B->rchild->maxChildNum + 1;
				else
					B->rchildNum = 0;

				if (B->lchildNum > B->rchildNum)
					B->maxChildNum = B->lchildNum;
				else
					B->maxChildNum = B->rchildNum;

				B->childNum = B->lchildNum - B->rchildNum;

				if (C->lchild != NULL)
					C->lchildNum = C->lchild->maxChildNum + 1;
				else
					C->lchildNum = 0;

				if (C->rchild != NULL)
					C->rchildNum = C->rchild->maxChildNum + 1;
				else
					C->rchildNum = 0;

				if (C->lchildNum > C->rchildNum)
					C->maxChildNum = C->lchildNum;
				else
					C->maxChildNum = C->rchildNum;

				C->childNum = C->lchildNum - C->rchildNum;

				A->childNum = A->lchildNum - A->rchildNum;
				B->childNum = B->lchildNum - B->rchildNum;
				C->childNum = C->lchildNum - C->rchildNum;
			}
		}
	}

	if (curAVL != NULL && curAVL->rchild != NULL)
	{
		if (curAVL->childNum == -2
			&& curAVL->rchild->childNum == -1)
		{
			A = curAVL;
			B = curAVL->rchild;
			C = curAVL->rchild->lchild;

			A->rchild = C;
			B->lchild = A;
			curAVL = B;

			if (A->lchild != NULL)
				A->lchildNum = A->lchild->maxChildNum + 1;
			else
				A->lchildNum = 0;

			if (A->rchild != NULL)
				A->rchildNum = A->rchild->maxChildNum + 1;
			else
				A->rchildNum = 0;

			if (A->lchildNum > A->rchildNum)
				A->maxChildNum = A->lchildNum;
			else
				A->maxChildNum = A->rchildNum;

			A->childNum = A->lchildNum - A->rchildNum;

			if (B->lchild != NULL)
				B->lchildNum = B->lchild->maxChildNum + 1;
			else
				B->lchildNum = 0;

			if (B->rchild != NULL)
				B->rchildNum = B->rchild->maxChildNum + 1;
			else
				B->rchildNum = 0;

			if (B->lchildNum > B->rchildNum)
				B->maxChildNum = B->lchildNum;
			else
				B->maxChildNum = B->rchildNum;

			B->childNum = B->lchildNum - B->rchildNum;

			A->childNum = A->lchildNum - A->rchildNum;
			B->childNum = B->lchildNum - B->rchildNum;
		}

		if (curAVL->rchild->lchild != NULL)
		{
			if (curAVL->childNum == -2
				&& curAVL->rchild->childNum == 1)
			{
				A = curAVL;
				B = curAVL->rchild;
				C = curAVL->rchild->lchild;
				D = curAVL->rchild->lchild->rchild;

				B->lchild = D;
				C->rchild = B;
				A->rchild = C;

				A->rchild = C->lchild;
				C->lchild = A;
				curAVL = C;

				if (A->lchild != NULL)
					A->lchildNum = A->lchild->maxChildNum + 1;
				else
					A->lchildNum = 0;

				if (A->rchild != NULL)
					A->rchildNum = A->rchild->maxChildNum + 1;
				else
					A->rchildNum = 0;

				if (A->lchildNum > A->rchildNum)
					A->maxChildNum = A->lchildNum;
				else
					A->maxChildNum = A->rchildNum;

				A->childNum = A->lchildNum - A->rchildNum;

				if (B->lchild != NULL)
					B->lchildNum = B->lchild->maxChildNum + 1;
				else
					B->lchildNum = 0;

				if (B->rchild != NULL)
					B->rchildNum = B->rchild->maxChildNum + 1;
				else
					B->rchildNum = 0;

				if (B->lchildNum > B->rchildNum)
					B->maxChildNum = B->lchildNum;
				else
					B->maxChildNum = B->rchildNum;

				B->childNum = B->lchildNum - B->rchildNum;

				if (C->lchild != NULL)
					C->lchildNum = C->lchild->maxChildNum + 1;
				else
					C->lchildNum = 0;

				if (C->rchild != NULL)
					C->rchildNum = C->rchild->maxChildNum + 1;
				else
					C->rchildNum = 0;

				if (C->lchildNum > C->rchildNum)
					C->maxChildNum = C->lchildNum;
				else
					C->maxChildNum = C->rchildNum;

				C->childNum = C->lchildNum - C->rchildNum;

				A->childNum = A->lchildNum - A->rchildNum;
				B->childNum = B->lchildNum - B->rchildNum;
				C->childNum = C->lchildNum - C->rchildNum;
			}
		}
	}

	return 0;
}