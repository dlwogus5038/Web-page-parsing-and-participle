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
using namespace std;

int main(int argc, char *argv[])
{
	My_HashTable MHT;
	string inputPath = "output/";
	string outputPath = "output/";
	int *checkLabelNum = 0;

	extractInfo(checkLabelNum , inputPath, outputPath); //网页解析
	MHT.initDictionary(); //保存“词库”里面的所有单词到自定义的哈希表里
	divideWords(MHT ,outputPath , outputPath , checkLabelNum); //分词算法

	system("pause");

	return 0;
}