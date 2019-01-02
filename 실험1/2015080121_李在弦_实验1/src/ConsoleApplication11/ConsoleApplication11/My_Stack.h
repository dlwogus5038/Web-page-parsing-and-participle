#ifndef MY_STACK_H
#define MY_STACK_H

#include <iostream>
#include <string>
#include "My_charstring.h"


class My_Stack
{
public:
	My_CharString *bottom, *top, *current;
	int size;
public:
	My_Stack()
	{
		int MAX_SIZE = 1000;
		bottom = new My_CharString[MAX_SIZE + 1];
		top = bottom;
		current = bottom;
	}
	~My_Stack() {};

	int m_push(std::string &e)
	{
		top->m_assign(e);
		return 0;
	}

	int m_push(char &e)
	{
		if (top->size == 0)
		{
			top->m_assign(e);
		}
		else
		{
			top->m_concat(e);
		}
		return 0;
	}

	int m_pop()
	{
		if (top == bottom)
		{
			std::cout << "ERROR";
			return 0;
		}
		top--;
		return 0;
	}

	std::string m_top()
	{
		std::string e;
		if (top == bottom)
		{
			std::cout << "ERROR";
			return "";
		}
		e = top->get_str();
		top--;
		return e;
	}

	int m_empty()
	{
		if (bottom == top)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
#endif MY_STACK_H