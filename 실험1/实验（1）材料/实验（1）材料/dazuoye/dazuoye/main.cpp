#include <iostream>
#include <string>
#include <fstream>
#include "My_CharString.h"
#include "My_CharStringLink.h"
#include "My_Stack.h"
using namespace std;

int main(int argc,char *argv[])
{
	My_CharString MCS;
	My_CharStringLink MCSL;
	My_Stack MSHead,MSQue,MSAuth,MSCont;
	My_Stack MS;
	string my_file[10];
	string my_result[10];
	string file = "0001.html";
	string B;
	string hlts = "headline-title";
	string hlte = "</h1>";
	string qts = "question-title";
	string qte = "</h2>";
	string aths = "author";
	string athe = "</span>";
	string ctss = "<div class=\"content\">";
	string cts = "<p>";
	string cte = "</p>";
	string ctee = "</div>";
	string ols = "<ol>";
	string ole = "</ol>";
	string li = "<li>";
	string bq = "<blockquote>";
	int i = 0;
	int hltstart = 0;
	int hltend = 0;
	int qtstart = 0;
	int qtend = 0;
	int athstart = 0;
	int athend = 0;
	int ctstart = 0;
	int ctend = 0;
	int ctcheck = 0;
	int ctnum = 0;
	ifstream inputFile;
	ofstream outputFile("output.txt");
	ofstream ResultFile("ResultFile.info");
	ofstream resultF;
	ofstream shi("shi.txt");

	my_file[0] = "0001.html";
	my_file[1] = "0002.html";
	my_file[2] = "0003.html";
	my_file[3] = "0004.html";
	my_file[4] = "0005.html";
	my_file[5] = "0006.html";
	my_file[6] = "0007.html";
	my_file[7] = "0008.html";
	my_file[8] = "0009.html";
	my_file[9] = "0010.html";

	my_result[0] = "0001.info";
	my_result[1] = "0002.info";
	my_result[2] = "0003.info";
	my_result[3] = "0004.info";
	my_result[4] = "0005.info";
	my_result[5] = "0006.info";
	my_result[6] = "0007.info";
	my_result[7] = "0008.info";
	my_result[8] = "0009.info";
	my_result[9] = "0010.info";


	/*
	MCS.str = "abcabcgabgfabkabcd";
	MCS.m_assign(MCS.str, 0, 4);

	cout << MCS.str;
	*/
	

	for (i = 0; i < 10; i++)
	{
		inputFile.open(my_file[i]);
		resultF.open(my_result[i]);
		if (!inputFile.is_open())
		{
			cout << "열기 오류" << endl;
			inputFile.close();
			return 0;
		}

		while (!inputFile.eof())
		{
			getline(inputFile, MCS.str);

			///////////////////////
			hltend = MCS.str.size() - 1;

			if (MCS.m_indexOf(hlts) != -1)
			{

				hltstart = MCS.m_indexOf(hlts);
				hltstart += 16;
				if (MCS.m_indexOf(hlte) != -1)
				{
					hltend = MCS.m_indexOf(hlte) - 1;
				}

				MCS.m_assign(MCS.str, hltstart, hltend);

				MSHead.m_push(MCS.str);
				MS.m_push(MCS.str);
				ResultFile << MCS.str << endl;
				resultF << MCS.str << endl;
			}

			//////////////////////

			qtend = MCS.str.size() - 1;

			if (MCS.m_indexOf(qts) != -1)
			{
				qtstart = MCS.m_indexOf(qts);
				qtstart += 16;
				if (MCS.m_indexOf(qte) != -1)
				{
					qtend = MCS.m_indexOf(qte) - 1;
				}

				MCS.m_assign(MCS.str, qtstart, qtend);

				MSQue.m_push(MCS.str);
				MS.m_push(MCS.str);
				ResultFile << MCS.str << endl;
				resultF << MCS.str << endl;
			}

			///////////////////////

			athend = MCS.str.size() - 1;

			if (MCS.m_indexOf(aths) != -1)
			{
				athstart = MCS.m_indexOf(aths);
				athstart += 8;
				if (MCS.m_indexOf(athe) != -1)
				{
					athend = MCS.m_indexOf(athe) - 1;
				}

				MCS.m_assign(MCS.str, athstart, athend);

				MSAuth.m_push(MCS.str);
				MS.m_push(MCS.str);
				ResultFile << MCS.str << endl;
				resultF << MCS.str << endl;

				ctnum = 2;
			}

			///////////////////////

			ctend = MCS.str.size() - 1;

			if ((MCS.m_indexOf(cts) != -1 || MCS.m_indexOf(li) != -1 || MCS.m_indexOf(bq) != -1) && ctcheck != 0 && ctnum == 1)
			{
				ctstart = 0;

				MCS.m_assign(MCS.str, ctstart, ctend);

				MSCont.m_push(MCS.str);
				MS.m_push(MCS.str);
				ResultFile << MCS.str << endl;
				resultF << MCS.str << endl;
			}

			if (MCS.m_indexOf(ctss) != -1)
			{
				ctcheck++;
				ctnum--;
			}

			if (MCS.m_indexOf(ols) != -1)
			{
				ctcheck++;
			}

			if (MCS.m_indexOf(ole) != -1)
			{
				ctcheck--;
			}
			
			if (MCS.m_indexOf(ctee) != -1)
			{
				ctcheck = 0;
			}

			outputFile << MCS.str << endl;
			cout << MCS.str << endl;
		}
		inputFile.close();
		resultF.close();
	}
	inputFile.close();
	outputFile.close();
	ResultFile.close();
	resultF.close();

	while (MS.current != MS.top)
	{
		shi << *MS.current << endl;
		MS.current++;
	}
	shi.close();

	system("pause");


	return 0;
}