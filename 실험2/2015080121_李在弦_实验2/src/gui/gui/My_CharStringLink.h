#ifndef My_CHARSTRINGLINK_H
#define My_CHARSTRINGLINK_H

#include "stdafx.h"
#include "My_CharString.h"
#include <string>

class CSNode
{
public:
	My_CharString my_CS;
	CSNode *prev, *next;
	int CSlength;
	CSNode()
	{
		CSlength = 0;
	}
};

class My_CharStringLink
{
public:
	CSNode *ap, *aq, *head;
	CSNode *rp, *rq;
	CSNode *sp, *sq;
	int length;
public:
	My_CharStringLink()
	{
		length = 0;
		head = ap = aq = NULL;
		rp = rq = NULL;
		sp = sq = NULL;
	}

	~My_CharStringLink() {};

	int add(std::string &e)
	{
		if (head == NULL)
		{
			ap = new CSNode;
			ap->my_CS.MBtoWC(e);
			ap->CSlength = ap->my_CS.w_size;

			head = ap;
			ap->next = ap->prev = NULL;
			ap = head;
			aq = NULL;
			length++;
		}
		else
		{
			while (ap->next != NULL)
			{
				ap = ap->next;
			}

			aq = new CSNode;
			aq->my_CS.MBtoWC(e);
			ap->CSlength = ap->my_CS.w_size;

			ap->next = aq;
			aq->prev = ap;
			aq->next = NULL;

			ap = aq;
			aq = NULL;
			length++;

		}

		return 0;
	}

	int add(wchar_t* &e)
	{
		int i = 0;
		for (i = 0; e[i] != '\0'; i++);

		if (head == NULL)
		{
			ap = new CSNode;
			ap->my_CS.w_str = e;
			ap->CSlength = i;

			head = ap;
			ap->next = ap->prev = NULL;
			ap = head;
			aq = NULL;
			length++;
		}
		else
		{
			while (ap->next != NULL)
			{
				ap = ap->next;
			}

			aq = new CSNode;
			aq->my_CS.w_str = e;
			aq->CSlength = i;

			ap->next = aq;
			aq->prev = ap;
			aq->next = NULL;

			ap = aq;
			aq = NULL;
			length++;

		}

		return 0;
	}

	int remove(std::string &e)
	{
		My_CharString check;
		int checknum = -1;
		check.MBtoWC(e);

		rp = head;

		checknum = rp->my_CS.wm_indexOf(check.w_str);
		if (checknum != -1)
		{
			rp->prev->next = rp->next;
			rp->next->prev = rp->prev;

			rp->prev = rp->next = NULL;
			delete rp;
			return 0;
		}

		while (rp->next != NULL)
		{
			checknum = rp->my_CS.wm_indexOf(check.w_str);
			if (checknum != -1)
			{
				break;
			}
			rp = rp->next;
		}

		if (checknum != -1)
		{
			rp->prev->next = rp->next;
			rp->next->prev = rp->prev;

			rp->prev = rp->next = NULL;
			delete rp;
		}

		return 0;

	}

	int remove(wchar_t* &e)
	{
		int checknum = -1;

		rp = head;

		checknum = rp->my_CS.wm_indexOf(e);
		if (checknum != -1)
		{
			rp->prev->next = rp->next;
			rp->next->prev = rp->prev;

			rp->prev = rp->next = NULL;
			delete rp;
			return 0;
		}

		while (rp->next != NULL)
		{
			checknum = rp->my_CS.wm_indexOf(e);
			if (checknum != -1)
			{
				break;
			}
			rp = rp->next;
		}

		if (checknum != -1)
		{
			rp->prev->next = rp->next;
			rp->next->prev = rp->prev;

			rp->prev = rp->next = NULL;
			delete rp;
		}

		return 0;

	}

	wchar_t* search(wchar_t* &e)
	{
		int checknum = -1;
		int eLength = 0;
		int i = 0;
		for (i = 0; e[i] != '\0'; i++);
		eLength = i;

		sp = head;

		if (sp->my_CS.w_size == eLength)
		{
			checknum = sp->my_CS.wm_indexOf(e);
		}

		if (checknum != -1)
		{
			return sp->my_CS.w_str;
		}

		while (sp->next != NULL)
		{
			if (sp->my_CS.w_size == eLength)
			{
				checknum = sp->my_CS.wm_indexOf(e);
				if (checknum != -1)
				{
					break;
				}
				sp = sp->next;
			}
			else
			{
				sp = sp->next;
			}
		}

		if (checknum != -1)
		{
			return sp->my_CS.w_str;
		}

		return NULL;
	}

};

#endif My_CHARSTRINGLINK_H