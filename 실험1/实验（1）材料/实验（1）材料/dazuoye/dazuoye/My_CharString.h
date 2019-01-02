#ifndef My_CharString_H
#define My_CharString_H

#include <string>

class My_CharString
{
public:
	std::string str;
	int size;

public:
	My_CharString() {};
	~My_CharString() {};
	int Init()
	{
		size = str.size();
	}

	int m_indexOf(std::string &a)
	{
		int lengtha;
		int check = 0;
		int i = 0,j;

		lengtha = a.size();
		size = str.size();

		for (i = 0; i < size; i++)
		{
			if (check > 0)
			{
				if (str[i] != a[check])
				{
					check = 0;
				}
			}

			if (str[i] == a[check])
			{
				check++;
			}

			if (check == lengtha)
			{
				break;
			}

		}

		if (check == lengtha)
		{
			return (i - check + 1);
		}
		else
		{
			return -1;
		}
	}

	std::string m_substring(int begin, int end)
	{
		std::string newString = "";
		int i = 0;

		for (i = begin; i < end; i++)
		{
			if (i == begin)
			{
				newString = str[i];
			}
			else
			{
				newString += str[i];
			}
		}

		return newString;
	}

	std::string m_concat(std::string &a,std::string &b)
	{
		std::string newString;
		newString = a;
		newString += b;

		return newString;
	}

	int m_assign(std::string &a)
	{
		str = a;
		return 0;
	}

	int m_assign(std::string a, int num1, int num2)
	{
		int i = 0;
		int check = 0;
		std::string newString;

		for(i=0;i<num2 - num1 + 1;i++)
		{
			if (a[num1 + i] == '<')
			{
				check++;
			}

			if (check == 0)
			{
				newString += a[num1 + i];
			}

			if (a[num1 + i] == '>')
			{
				check = 0;
			}
		}
		str = newString;

		return 0;
	}

	int m_assign(std::string &a, int num)
	{
		int i = 0;
		std::string newString;
		for (i = 0; i < num; i++)
		{
			newString = a[i];
		}

		str = newString;

		return 0;
	}

	int m_assign(int num, char &a)
	{
		int i;
		std::string newString;
		for(i=0;i<num;i++)
		{
			newString += a;
		}
		
		str = newString;

		return 0;
	}
};

#endif My_CharString_H
