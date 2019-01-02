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
using namespace std;

My_CharStringLink* divideWords(My_AVL* &MAVL, string inputPath 
	, string outputPath , int* &checkLabelNum, int maxDicNum)
{
	My_CharString MCS;
	My_CharStringLink* ResultLink;
	My_AVL *my_checkAVL;
	ifstream inputFile;
	wofstream outputFile;
	string *my_file;
	string *my_result;
	string *my_fileName;
	string _path = "output/";
	string _filter = "*.info";
	string FileName = "";
	string readInfo = "";
	wchar_t* checkWC;
	wchar_t* resultWC;
	vector<string> _files;
	int fileNum = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int num = 0;
	int begin = 0;
	int end = 0;
	int checkWord = 0;
	int checkSize = 0;
	long long int wordID = 0;


	_wsetlocale(LC_ALL, L"China");
	setlocale(LC_CTYPE, "");
	locale &loc = locale::global(locale(locale(), "", LC_CTYPE));


	ResultLink = new My_CharStringLink; //所有分词好的单词保存到这个地方

	_files = get_files_inDirectory(_path, _filter); //털뙤"input"匡숭셸쟁충唐뜩몸;
	fileNum = _files.size();
	my_file = new string[fileNum];
	my_result = new string[fileNum];
	my_fileName = new string[fileNum];

	for (i = 0; i < fileNum; i++)
	{
		my_file[i] = _files[i];
	}

	for (i = 0; i < fileNum; i++)
	{
		FileName = "";
		j = 0;
		while (_files[i][j] != '.')
		{
			FileName += _files[i][j];
			j++;
		}
		my_result[i] = FileName + ".txt";
		my_fileName[i] = FileName;
	}

	for (i = 0; i < fileNum; i++)
	{
		inputPath = "output/";
		outputPath = "output/";

		inputPath += my_file[i];
		outputPath += my_result[i];

		inputFile.open(inputPath);
		outputFile.open(outputPath);

		outputFile.imbue(locale(locale(), "", LC_CTYPE));
		wcout.imbue(locale(locale(), "", LC_CTYPE));

		if (!inputFile.is_open())
		{
			cout << "ERROR 4" << endl;
			inputFile.close();
			return 0;
		}

		while (!inputFile.eof())
		{
			getline(inputFile, readInfo); //读入一行
			checkWord = 0;

			if (checkLabelNum[i] != 0)
			{
				checkLabelNum[i]--; //不是正文时，直接跳过
				continue;
			}

			if (readInfo != "")
			{
				num = readInfo.size();
				MCS.MBtoWC(readInfo);
			}
			else
			{
				continue;
			}

			begin = 0;
			if (MCS.w_size <= maxDicNum)
			{
				end = MCS.w_size;
			}
			else
			{
				end = maxDicNum;
			}

			while (1) //开始做分词
			{
				if (begin == end && begin == MCS.w_size)
				{
					break;
				}

				if (end == begin)
				{
					begin += 1;

					if (MCS.w_size > begin + maxDicNum)
					{
						end = begin + maxDicNum;
					}
					else
					{
						end = MCS.w_size;
					}

					if (begin == end && end == MCS.w_size)
					{
						break;
					}
				}


				checkWC = MCS.wm_substring(begin, end); //用自定义的wm_substring函数提取部分字符串

				checkSize = end - begin;

				wordID = 0;

				for (k = 1; k <= checkSize; k++)
					wordID += (k*(checkWC[k - 1])); //获得字符串链表数组的“index”值
				wordID = wordID % 100000;
				wordID += checkWC[0] * 100000;
				wordID += (checkWC[k - 1] % 1000) * 1000000000;
				wordID += checkSize * 1000000000000;

				my_checkAVL = MAVL->Search(MAVL, wordID, checkWC, my_fileName[i]);

				if (my_checkAVL == NULL)
					resultWC = NULL;
				else
					resultWC = my_checkAVL->charNode.Term.w_str; //查找有没有跟“checkWC”一样的单词

				if (resultWC != NULL)
				{
					ResultLink->add(resultWC); //把分词后的单词保存到“ResultLink”
					begin = end;
					if (MCS.w_size > begin + maxDicNum)
					{
						end = begin + maxDicNum;
					}
					else
					{
						end = MCS.w_size;
					}
					outputFile << resultWC << endl;
				}
				else
				{
					if (begin != MCS.w_size)
					{
						end--;
					}
					else
					{
						break;
					}
				}

			}


		}

		inputFile.close();
		outputFile.close();

	}


	return ResultLink;
}