#include "HtmlLink.h"

int HtmlLink::Add(int docID)
{
	HtmlNode *p, *q;

	p = htmlNode;
	q = NULL;

	if (p == NULL)
	{
		p = new HtmlNode;
		p->DocID = docID;
		p->Times = 1;
		htmlNode = p;
		return 0;
	}

	while (p != NULL)
	{
		if (p->DocID == docID)
		{
			Edit(p);
			return 0;
		}
		q = p;
		p = p->next;
	}

	p = new HtmlNode;
	p->DocID = docID;
	p->Times = 1;

	q->next = p;
	return 0;
}

HtmlNode* HtmlLink::Search(int docID)
{
	HtmlNode *p;

	p = htmlNode;

	while (p != NULL)
	{
		if (p->DocID == docID)
			return p;

		p = p->next;
	}

	return NULL;
}

int HtmlLink::Edit(HtmlNode* &p)
{
	if (p != NULL)
		p->Times++;
	return 0;
}

int HtmlLink::Edit(int docID)
{
	HtmlNode *p;

	p = Search(docID);

	if (p != NULL)
		p->Times++;

	return 0;
}

int HtmlLink::Remove(int docID)
{
	HtmlNode *p, *q;

	p = htmlNode;

	if (p == NULL)
		return 0;
	if (p->next == NULL && p->DocID == docID)
	{
		delete htmlNode;
		htmlNode = NULL;
		return 0;
	}

	q = p;

	while (p != NULL)
	{
		if (p->DocID == docID)
		{
			q->next = p->next;
			delete p;
			p = NULL;
			return 0;
		}

		q = p;
		p = p->next;
	}

	return 0;

}