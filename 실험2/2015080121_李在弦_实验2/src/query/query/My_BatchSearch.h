#ifndef MY_BATCHSEARCH_H
#define MY_BATCHSEARCH_H

#include "HtmlLink.h"
#include "AVL.h"
#include <fstream>
#include <iostream>

class ResultNode
{
public:
	int DocID;
	int Times;
	int wordTimes;
	ResultNode() { DocID = -1; Times = 0; wordTimes = 0; }
};

class My_BatchSearch
{
public:
	HtmlLink* searchLink;
	ResultNode* resultNode;
	My_BatchSearch() { wordNumber = 0; searchLink = NULL; nodeNumber = 0; }
	int wordNumber;
	int nodeNumber;
	int startSearch(My_AVL* &MAVL, int maxDicNum);
	int My_DivideWords(My_AVL* &MAVL, int maxDicNum ,std::string readQuery);
	int CrtLink(My_AVL* &curAVL);
	ResultNode* AdjustLink();
	int OutputLink(std::ofstream &outputQuery);
};

#endif

