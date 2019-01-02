#ifndef My_CHARSTRING_H
#define My_CHARSTRING_H

#include <string>
#include <stdlib.h>
#include <atlconv.h>

class My_CharString
{
public:
	char * str;
	wchar_t * w_str;
	int size;
	int w_size;

public:
	My_CharString() 
	{
	size = 0;
	w_size = 0;
	}
	~My_CharString() {};

	int MBtoWC(std::string &e)
	{

		if (e == "")
		{
			if (w_size != 0)
			{
				delete w_str;
				w_size = 0;
			}
			return 0;
		}
		if (w_size != 0)
		{
			delete w_str;
		}
		Init(e);
		w_size = e.size() + 2;
		w_str = (wchar_t*)malloc(sizeof(wchar_t)*(w_size));
		MultiByteToWideChar(CP_UTF8, 0, str, -1, w_str, w_size);

		w_size = 0;

		for (w_size = 0; w_str[w_size] != '\0'; w_size++);
		
		return 0;
	}

	int Init(std::string e)
	{
		int i = 0;

		size = e.size();
		str = (char*)malloc(sizeof(char)*(size + 1));

		for (i = 0; i < size; i++)
		{
			str[i] = e[i];
		}
		str[i] = '\0';

		return 0;
	}

	int m_indexOf(std::string &a)
	{
		int lengtha;
		int check = 0;
		int i = 0;



		lengtha = a.size();

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

	int wm_indexOf(wchar_t* &a)
	{
		int lengtha = 0;
		int check = 0;
		int i = 0;

		for (lengtha = 0; a[lengtha] != '\0'; lengtha++);

		for (i = 0; i < lengtha; i++)
		{
			if (check > 0)
			{
				if (w_str[i] != a[check])
				{
					check = 0;
				}
			}

			if (w_str[i] == a[check])
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

	std::string get_str()
	{
		std::string newString = "";
		int i = 0;

		for (i = 0; i < size; i++)
		{
			newString += str[i];
		}

		return newString;
	}

	std::string m_substring(int begin, int end)
	{
		std::string newString = "";
		char * newChar;
		int i = 0;
		int j = 0;

		newChar = new char[end - begin];
		for (i = begin; i < end; i++)
		{
			newChar[j] = str[i];
			j++;
		}

		for (i = 0; i < j; i++)
		{
			newString += newChar[i];
		}

		return newString;
	}

	wchar_t* wm_substring(int begin, int end)
	{
		wchar_t* newWChar;
		char * newChar;
		int i = 0;
		int j = 0;

		newChar = new char[end - begin];
		newWChar = new wchar_t[end - begin + 1];
		for (i = begin; i < end; i++)
		{
			newWChar[j] = w_str[i];
			j++;
		}
		newWChar[j] = '\0';

		return newWChar;
	}

	void m_concat(std::string &a)
	{
		int i = 0;
		int cur = 0;
		int num = a.size();
		str = (char*)realloc(str, size + num + 1);

		cur = size;

		for (i = 0; i < num; i++ , cur++)
		{
			str[cur] = a[i];
		}
		str[cur] = '\0';

		size = size + num;
	}

	void m_concat(char e)
	{
		str = (char*)realloc(str, size + 2);
		str[size] = e;
		str[size + 1] = '\0';
		size += 1;
	}

	void wm_concat(wchar_t &e)
	{
		w_str = (wchar_t*)realloc(str, w_size + 2);
		w_str[w_size] = e;
		w_str[w_size + 1] = '\0';
		w_str += 1;
	}

	int m_assign(std::string &a)
	{
		int i = 0;
		int num = 0;
		num = a.size();

		if (size != 0)
		{
			free(str);
		}

		str = (char*)malloc(sizeof(char)*(num + 1));

		for (i = 0; i < num; i++)
		{
			str[i] = a[i];
		}
		str[i] = '\0';

		size = i;

		return 0;
	}

	int m_assign(char &e)
	{
		int i = 0;
		int num = 1;

		if (size != 0)
		{
			free(str);
		}

		str = (char*)malloc(sizeof(char)*(num + 1));

		str[0] = e;
		str[1] = '\0';

		size = num;

		return 0;
	}

	int m_assign(std::string a, int num1, int num2)
	{
		int i = 0;
		int check = 0;

		if (size != 0)
		{
			free(str);
		}

		str = (char*)malloc(sizeof(char)*(num2-num1 + 2));

		for (i = 0; i<num2 - num1 + 1; i++)
		{
			if (a[num1 + i] == '<')
			{
				check++;
			}

			if (check == 0)
			{
				str[i] = a[num1 + i];
			}

			if (a[num1 + i] == '>')
			{
				check = 0;
			}
		}
		str[i] = '\0';

		size = i;

		return 0;
	}

	int m_assign(std::string &a, int num)
	{
		int i = 0;

		if (size != 0)
		{
			free(str);
		}

		str = (char*)malloc(sizeof(char)*(num + 1));

		for (i = 0; i < num; i++)
		{
			str[i] = a[i];
		}
		str[i] = '\0';

		size = i;

		return 0;
	}

	int m_assign(int num, char &a)
	{
		int i;

		if (size != 0)
		{
			free(str);
		}

		str = (char*)malloc(sizeof(char)*(num + 1));

		for (i = 0; i<num; i++)
		{
			str[i] = a;
		}

		str[i] = '\0';

		size = i;

		return 0;
	}
};

#endif My_CHARSTRING_H