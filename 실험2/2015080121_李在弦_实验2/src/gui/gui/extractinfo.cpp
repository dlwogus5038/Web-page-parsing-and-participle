#include "stdafx.h"
#include "extractInfo.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "My_CharString.h"
#include "My_CharStringLink.h"
#include "My_Stack.h"
#include "UsefulLabel.h"
#include "get_files.h"
using namespace std;

int extractInfo(int* &checkLabelNum, string inputPath, string outputPath)
{
	My_CharString MCS;
	My_CharStringLink MCSL;
	My_Stack MSHead, MSQue, MSAuth, MSCont;
	My_Stack MS;
	string readHtml;
	string *my_file;
	string *my_result;
	string *UFLabel;
	string FileName;
	string headString = "headline-title";
	string questionString = "question-title";
	string contentString = "class=\"content\"";
	string contentEnd = "</div>";
	string authorString = "class=\"author\"";
	ifstream inputFile;
	ofstream outputFile;
	string View_More = "view-more";
	string USFCheck1 = "";
	string USFCheck2 = "";
	string _path = "input/";
	string _filter = "*.html";
	vector<string> _files;
	int contentState = 0;
	int StringState = 0;
	int endlState = 0;
	int fileNum = 0;
	int UFLabelLength = 0;
	int checkLabel = 0;
	int checkAuNum = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int h = 0;
	int num = 0;
	int checkContent = 0;

	_files = get_files_inDirectory(_path, _filter); //털뙤"input"匡숭셸쟁충唐뜩몸;
	fileNum = _files.size();
	my_file = new string[fileNum];
	my_result = new string[fileNum];
	checkLabelNum = new int[fileNum];

	for (i = 0; i < fileNum; i++)
	{
		my_file[i] = _files[i]; //提取输入文件的名字
		checkLabelNum[i] = 0;
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
		my_result[i] = FileName + ".info";
	}

	UsefulLabel(UFLabel, UFLabelLength, my_file, fileNum);

	for (i = 0; i < fileNum; i++)
	{
		inputPath = "input/";
		outputPath = "output/";
		inputPath += my_file[i];
		outputPath += my_result[i];
		inputFile.open(inputPath);
		outputFile.open(outputPath);
		if (!inputFile.is_open())
		{
			cout << "ERROR 2" << endl; //没有文件时会输出“ERROR 2"	;
			inputFile.close();
			return 0;
		}

		contentState = 0;
		checkContent = 0;

		while (!inputFile.eof())
		{
			num = 0;
			getline(inputFile, readHtml); //读入一行
			num = readHtml.size();
			checkLabel = 0;
			checkAuNum = 0;
			endlState = 0;

			for (h = 0; h < num; h++)
			{
				if (readHtml[h] == '<')
				{
					checkAuNum++;
				}
			}

			for (j = 0; j < num; j++)
			{
				if (readHtml[0] != '<') //没有标签时
				{
					break;
				}

				if (readHtml[j] == '<' && readHtml[j + 1] == '/') //退栈
				{
					while (readHtml[j] != '>')
					{
						j++;
					}
					if (StringState == 1 || StringState == 3)
					{
						StringState = 0;
					}
					if (StringState == 2)
					{
						if (readHtml == (contentEnd))
						{
							StringState = 0;
						}
					}
					if (MS.top->size != 0)
					{
						free(MS.top->str);
					}
					MS.top->size = 0;
					MS.top--;
				}

				else if (readHtml[j] == '<') //进展
				{
					MS.top++;
					while (readHtml[j] != '>')
					{
						MS.m_push(readHtml[j]);
						j++;
					}
					MS.m_push(readHtml[j]);

					for (k = 0; k < UFLabelLength; k++)
					{
						USFCheck1 = UFLabel[k] + " "; //UFLabel是有效标签的数组
						USFCheck2 = UFLabel[k] + ">";
						if (MS.top->m_indexOf(USFCheck1) == -1 && MS.top->m_indexOf(USFCheck2) == -1)
						{
							checkLabel++; //判断有没有有效标签
						}
					}

					if (checkLabel == UFLabelLength) //有有效标签
					{
						free(MS.top->str);
						MS.top->size = 0;
						MS.top--;
						checkLabel = 0;
						checkAuNum = 0;
						continue;
					}
					else
					{
						if (StringState == 2)
						{
							endlState++;
						}

						if (MS.top->m_indexOf(headString) != -1)
						{
							StringState = 1;
							endlState++;
							if (checkContent == 0)
							{
								checkLabelNum[i]++;
							}
						}
						else if (MS.top->m_indexOf(questionString) != -1)
						{
							StringState = 1;
							endlState++;
							if (checkContent == 0)
							{
								checkLabelNum[i]++;
							}
						}
						else if (MS.top->m_indexOf(contentString) != -1 && contentState == 1)
						{
							StringState = 2;
							contentState++;
							checkContent++;
						}
						else if (MS.top->m_indexOf(authorString) != -1)
						{
							StringState = 3;
							endlState++;
							contentState++;
							if (checkContent == 0)
							{
								checkLabelNum[i]++;
							}
						}
						if (MS.top->m_indexOf(View_More) != -1)
						{
							StringState = 0;
						}
						checkLabel = 0;
					}
				}

				else if (StringState == 1 || StringState == 2 || StringState == 3)
				{
					if (StringState != 3)
					{
						MS.m_push(readHtml[j]); //保存到栈里面
						outputFile << readHtml[j]; //保存内容
					}
					else if (StringState == 3 && checkAuNum >= 3)
					{
						if (readHtml[j] < 0 && readHtml[j + 1] < 0 && readHtml[j + 2] <0
							&& readHtml[j + 3] == '<' && readHtml[j + 4] == '/')
						{
							while (readHtml[j] != '<')
							{
								j++; //去掉在作者部分的不需要的部分
							}
							j--;
						}
						else if ((readHtml[j] == ',' || readHtml[j] == ' ') && readHtml[j + 1] == '<'
							&& readHtml[j + 2] == '/')
						{
							//去掉在作者部分的不需要的部分
						}
						else
						{
							MS.m_push(readHtml[j]);
							outputFile << readHtml[j]; //保存内容

						}
					}
					else if (StringState == 3 && checkAuNum < 3)
					{
						MS.m_push(readHtml[j]);
						outputFile << readHtml[j]; //保存内容
					}
				}
			}
			if (endlState != 0)
			{
				outputFile << endl; //换行部分

			}
		}
		inputFile.close();
		outputFile.close();
	}

	return 0;
}