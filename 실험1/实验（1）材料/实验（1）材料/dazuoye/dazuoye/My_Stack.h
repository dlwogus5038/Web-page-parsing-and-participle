#ifndef MY_STACK_H
#define MY_STACK_H

#include <iostream>
#include <string>


class My_Stack
{
public:
	std::string *bottom, *top ,*current;
	int size;
public:
	My_Stack() 
	{
		size = 1000;
		bottom = new std::string[size + 1];
		top = bottom;
		current = bottom;
	}
	~My_Stack() {};

	int m_push(std::string &e)
	{
		if (top - bottom >= size)
		{
			std::cout << "ERROR";
			return 0;
		}
		*top = e;
		top++;
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
		top--;
		e = *top;
		top++;
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
