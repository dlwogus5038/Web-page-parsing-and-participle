#include "stdafx.h"
#include "UsefulLabel.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void UsefulLabel(string* &UFLabel, int &UFLabelLength, string* &my_file, int fileNum)
{
	ifstream inputFile;
	ifstream ipFile;
	ifstream checkFile;
	ofstream outputFile("output.txt");
	ofstream opFile("output2.txt");
	ofstream outFile("output3.txt");
	ofstream outcheck("output4.txt");
	string readHtml;
	string ResulT = "";
	string biaoqian[1000] = { "" };
	string Label[100] = { "" };
	string check = "";
	string check2 = "";
	string check3 = "";
	string path = "input/";
	int LabelLength = 0;
	int LabelNum = 0;
	int bqnum = 0;
	int bqcur = 0;
	int cur = 0;
	int j = 0;
	int i = 0;
	int num = 0;
	int num2 = 0;
	int num3 = 0;
	int k = 0;
	int p = 0;
	int q = 0;

	for (i = 0; i < fileNum; i++) // 提取所有标签，保存到“output.txt”
	{
		path = "input/";
		path += my_file[i];
		inputFile.open(path);
		if (!inputFile.is_open())
		{
			cout << "ERROR 1" << endl;
			inputFile.close();
			return;
		}

		while (!inputFile.eof())
		{
			getline(inputFile, readHtml); //读入一行
			num = readHtml.size();
			for (j = 0; j < num; j++)
			{
				if (readHtml[j] == '<')
				{
					outputFile << readHtml[j];
					ResulT += readHtml[j];
					cur = 1;
				}
				else if (readHtml[j] == '>' || readHtml[j] == ' ')
				{
					cur = 0;
					outputFile << endl;
				}
				else if (cur == 1)
				{
					outputFile << readHtml[j];
					ResulT += readHtml[j];
				}
			}
		}
		inputFile.close();
	}
	outputFile.clear();
	outputFile.close();

	num2 = ResulT.size();
	for (k = 0; k < num2; k++) //整理“output.txt”文件
	{
		if (ResulT[k] == '<')
		{
			opFile << endl << ResulT[k];
		}
		else
		{
			opFile << ResulT[k];
		}
	}

	opFile.close();

	ipFile.open("output2.txt");
	while (!ipFile.eof()) //把“output2.txt”文件中的重复的标签都删除
	{
		getline(ipFile, check);
		for (p = 0; p < bqnum; p++)
		{
			if (check == biaoqian[p])
			{
				break;
			}
		}
		if (check == biaoqian[p])
		{
			continue;
		}
		biaoqian[bqcur] = check;
		outFile << check << endl;
		bqcur++;
		bqnum++;
	}

	ipFile.close();
	outFile.close();

	checkFile.open("output3.txt");
	while (!checkFile.eof()) //提取有效标签
	{
		getline(checkFile, check2);
		if (check2 == "")
		{
			continue;
		}
		check3 = "";
		if (check2[1] != '/')
		{
			check3 += "</";
			num3 = check2.size();
			for (p = 1; p < num3; p++)
			{
				check3 += check2[p];
			}

			for (q = 0; q < bqnum; q++)
			{
				if (biaoqian[q] == check3)
				{
					break;
				}
			}
			if (biaoqian[q] == check3)
			{
				Label[LabelLength] = check2;
				LabelLength++;
				outcheck << check2 << endl << check3 << endl;
			}
		}
	}
	checkFile.close();
	outcheck.close();
	UFLabel = new string[LabelLength]; //有效标签的数组

	remove("output.txt");
	remove("output2.txt");
	remove("output3.txt");
	remove("output4.txt");

	for (p = 0; p < LabelLength; p++)
	{
		UFLabel[p] = Label[p];
	}
	UFLabelLength = LabelLength;
}