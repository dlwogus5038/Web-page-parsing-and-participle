#ifndef HTMLLINK_H
#define HTMLLINK_H

#include <iostream>

class HtmlNode
{
public:
	int DocID;
	int Times;
	HtmlNode *next;

	HtmlNode() { next = NULL; DocID = 0; Times = 0; }
};

class HtmlLink
{
public:
	long long int TermID;
	HtmlNode *htmlNode;

	HtmlLink() { TermID = 0; }
	int Add(int docID);
	HtmlNode* Search(int docID);
	int Edit(HtmlNode* &p);
	int Edit(int docID);
	int Remove(int docID);
};

#endif