#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <locale>
#include "My_CharString.h"
#include "My_CharStringLink.h"
#include "My_Stack.h"
#include "UsefulLabel.h"
#include "get_files.h"
#include "extractInfo.h"
#include "My_HashTable.h"
#include "divideWords.h"
#include "AVL.h"
#include "My_BatchSearch.h"
using namespace std;

int main(int argc, char *argv[])
{
	My_AVL *MAVL;
	My_BatchSearch MBS;
	int MaxDicNum = 0;
	string inputPath = "output/";
	string outputPath = "output/";
	int *checkLabelNum = 0;

	MAVL = new My_AVL;
	extractInfo(checkLabelNum , inputPath, outputPath); //网页解析
	MAVL->initDictionary(MaxDicNum,MAVL); //保存“词库”里面的所有单词到自定义的哈希表里
	divideWords(MAVL ,outputPath , outputPath , checkLabelNum , MaxDicNum); //分词算法
	MBS.startSearch(MAVL, MaxDicNum);

	system("pause");

	return 0;
}