#include "stdafx.h"
#include "My_BatchSearch.h"
#include "My_CharString.h"
#include "AVL.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

ResultNode* My_BatchSearch::AdjustLink()
{
	ResultNode *checkNode;
	ResultNode *checkNode2;
	ResultNode temp;
	HtmlNode *p;
	int checkNodeNum = 0;
	int checkNodeNum2 = 0;
	int checkState = 0;
	int i = 0;
	int j = 0;

	checkNode = new ResultNode[wordNumber * 100];

	for (i = 0; i < wordNumber; i++) // 获取各个单词的文档链表信息
	{
		p = searchLink[i].htmlNode;
		while (p != NULL)
		{
			checkNode[checkNodeNum].DocID = p->DocID;
			checkNode[checkNodeNum].Times = p->Times;
			checkNodeNum++;

			p = p->next;
		}
	}

	checkNode2 = new ResultNode[checkNodeNum];

	for (i = 0; i < checkNodeNum; i++) // 对重复的文档进行处理（相加出现次数）
	{
		checkState = 0;
		for (j = 0; j < checkNodeNum; j++)
		{
			if (checkNode[i].DocID == checkNode[j].DocID && checkNode[j].Times != -1
				&& checkNode[i].DocID != -1 && checkNode[j].DocID != -1)
			{
				checkNode2[checkNodeNum2].DocID = checkNode[j].DocID;
				checkNode2[checkNodeNum2].Times += checkNode[j].Times;
				checkNode2[checkNodeNum2].wordTimes++;

				checkNode[j].Times = -1;
				checkState++;
			}
		}
		if (checkState != 0)
			checkNodeNum2++;
	}

	for (i = 0; i < checkNodeNum2; i++) // 把出现次数多的排在前面，把交多的排在前面
	{
		for (j = 0; j < checkNodeNum2 - 1; j++)
		{
			if (checkNode2[j].wordTimes <= checkNode2[j + 1].wordTimes)
			{
				if (checkNode2[j].Times < checkNode2[j + 1].Times)
				{
					temp = checkNode2[j];
					checkNode2[j] = checkNode2[j + 1];
					checkNode2[j + 1] = temp;
				}
			}
		}
	}

	nodeNumber = checkNodeNum2;
	delete checkNode;
	return checkNode2;
}

int My_BatchSearch::OutputLink(ofstream &outputQuery)
{
	int i = 0;

	for (i = 0; i < nodeNumber; i++)
		outputQuery << '(' << resultNode[i].DocID << ',' << resultNode[i].Times << ") ";  // 输出结果
	outputQuery << endl;
	return 0;
}

int My_BatchSearch::startSearch(My_AVL* &MAVL, int maxDicNum, CString m_keyWord)
{
	string inputString;
	string readQuery;
	ofstream outputQuery("result_gui.txt");
	int inputSize = 0;
	int i = 0;


	inputString = CW2A(m_keyWord, CP_UTF8);

	inputSize = inputString.size();

	readQuery = "";
	searchLink = new HtmlLink[100];
	wordNumber = 0;
	nodeNumber = 0;

	for (i = 0; i < inputSize; i++)
	{
		if (inputString[i] == ' ')
		{
			My_DivideWords(MAVL, maxDicNum, readQuery); // 对关键词进行分词
			readQuery = "";
		}
		else
			readQuery += inputString[i];
	}

	My_DivideWords(MAVL, maxDicNum, readQuery);

	resultNode = AdjustLink(); // 获取各个单词的信息，再次排序
	OutputLink(outputQuery);

	delete searchLink;
	searchLink = NULL;

	return 0;
}

int My_BatchSearch::CrtLink(My_AVL* &curAVL)
{
	searchLink[wordNumber] = curAVL->charNode.HL;
	wordNumber++;
	return 0;
}

int My_BatchSearch::My_DivideWords(My_AVL* &MAVL, int maxDicNum, string readQuery)
{
	string inputString;
	My_CharString check;
	My_CharString MCS;
	My_AVL *my_checkAVL;
	wchar_t* checkWC;
	wchar_t* resultWC;
	int num = 0;
	int begin = 0;
	int end = 0;
	int checkSize = 0;
	long long int wordID = 0;
	int i = 0;
	int k = 0;


	if (readQuery != "")
	{
		num = readQuery.size();
		MCS.MBtoWC(readQuery);
	}
	else
		return 0;

	begin = 0;

	if (MCS.w_size <= maxDicNum)
		end = MCS.w_size;
	else
		end = maxDicNum;

	while (1) //开始做分词
	{
		if (begin == end && begin == MCS.w_size)
			break;

		if (end == begin)
		{
			begin += 1;

			if (MCS.w_size > begin + maxDicNum)
				end = begin + maxDicNum;
			else
				end = MCS.w_size;

			if (begin == end && end == MCS.w_size)
				break;
		}


		checkWC = MCS.wm_substring(begin, end); //用自定义的wm_substring函数提取部分字符串

		checkSize = end - begin;

		wordID = 0;

		for (k = 1; k <= checkSize; k++)
			wordID += (k*(checkWC[k - 1])); //获得字符串链表数组的“index”值

		wordID = wordID % 100000;
		wordID += checkWC[0] * 100000;
		wordID += (checkWC[k - 1] % 1000) * 1000000000; // wordID = KEY
		wordID += checkSize * 1000000000000;

		my_checkAVL = MAVL->Search(MAVL, wordID, checkWC);

		if (my_checkAVL == NULL)
			resultWC = NULL;
		else
			resultWC = MAVL->Search(MAVL, wordID, checkWC)->charNode.Term.w_str; //查找有没有跟“checkWC”一样的单词

		if (resultWC != NULL)
		{
			CrtLink(my_checkAVL);
			begin = end;
			if (MCS.w_size > begin + maxDicNum)
				end = begin + maxDicNum;
			else
				end = MCS.w_size;
		}
		else
		{
			if (begin != MCS.w_size)
				end--;
			else
				break;
		}

	}



	return 0;
}
