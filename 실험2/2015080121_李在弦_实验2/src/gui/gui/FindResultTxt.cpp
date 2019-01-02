#include "stdafx.h"
#include "FindResultTxt.h"
#include <fstream>
#include <string>
using namespace std;

int FindResultTxt(CString *&CS,int &CSnum)
{
	ifstream inputTxt("result_gui.txt");
	string inputString;
	string nameString = "";
	string temp = "";
	int *htmlArr;
	int ISlen = 0;
	int htmlNum = 0;
	int i = 0;
	int nameLen = 0;

	CSnum = 0;

	getline(inputTxt, inputString); // 读取信息
	ISlen = inputString.size();
	
	for (i = 0; i < ISlen; i++)
	{
		if (inputString[i] == '(')
		{
			htmlNum++; //数一数有几个文档
		}
	}

	if (htmlNum > 20)
		htmlArr = new int[htmlNum];
	else
		htmlArr = new int[20];

	CS = new CString[20]; // 最多显示20个文档

	for (i = 0; i < 20; i++)
	{
		CS[i] = _T("");
	}

	for (i = 0; i < ISlen; i++)
	{
		if (inputString[i] == '(')
		{
			i++;
			nameString = "";
			while (inputString[i] != ',') // 获取文件名
			{
				nameString += inputString[i];
				i++;
			}

			nameLen = nameString.size();
			if (nameLen == 1) // 把文件名完整一点
			{
				temp = "000";
				temp += nameString;
				nameString = temp;
			}
			else if (nameLen == 2)
			{
				temp = "00";
				temp += nameString;
				nameString = temp;
			}
			else if (nameLen == 3)
			{
				temp = "0";
				temp += nameString;
				nameString = temp;
			}

			CS[CSnum] = nameString.c_str(); // 转换成‘UNICODE’
			CSnum++;
			if (CSnum == 20)
				break;
		}
	}

	inputTxt.close();
	return 0;
}