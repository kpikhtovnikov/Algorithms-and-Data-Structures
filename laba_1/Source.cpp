#include<iostream>
#include<conio.h>
#include "windows.h"
#include<string.h>
using namespace std;
const int down = 80, up = 72, _enter = 13, _esc = 27, _backspace = 8;
void setcur(int x, int y)//��������� ������� �� ������� x y 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};
class _stack 
{
private:
	int *arr;
	unsigned count;//���-�� ��������� � �������
public:
	_stack(unsigned N = 0) //����������� �����
	{
		create(N); 
	}
	~_stack()  //���������� �����
	{ 
		Free(); 
	}
	void create(unsigned N = 0)//������� ������������ ����� ��� �������� ������������� �������
	{
		if (N)
		{
			arr = new int[count];
		}
		else
		{
			arr = 0;
		}
		count = N;
	}
	void _push(int value)//��������� ������� � ���� ��� � ����� �������
	{
		++count;
		int* cur = new int[count];
		for (int i = 0; i < count - 1; ++i)
		{
			cur[i] = arr[i];
		}
		free(arr);
		arr = cur;
		arr[count - 1] = value;				
	}
	void _pop()//������� ������� �� ����� ��� �������
	{
		if (count)
		{
			--count;
			arr[count] = 0;
		}
		else
			cout << "���� ����";
	}
	 char _top()//���������� �������� �������� �� �����
	{
		char ch;
		if (count > 0)
			ch = arr[count - 1];
		else
			ch = 0;
		//cout << ch;
		return ch;
	}
	void Free()//������� ����������� �����
	{
		if (arr)
		{
			delete[] arr;
			arr = 0;
			count = 0;
		}
	}
	bool is_empty()//��������:���� �� ����
	{
		if (count == 0)
			return false;
		else
			return true;
	}
};
struct list
{
	int value = 0;
	list* prev = 0;
	list* next = 0;
};
class _deque
{
private:
	list* prev ;
	list* next ;
	unsigned count = 0;
public:
	_deque(unsigned N = 0)
	{
		init();
	}
	~_deque()
	{
		clear();
	}
	void init()
	{
		count = 0;
		prev = 0;
		next = 0;
	}
	void create(unsigned N)//�������� ������
	{
		if (count)
			clear();
		//list* start=0;
		for (unsigned i = 1; i <= N; ++i)
		{
			prev = new list;
			prev->next = next;
			if(next)
				next->prev = prev;
			next = prev;
		}
		next->prev = 0;
	}
	void clear()//�������� ������
	{
		list* start = prev;
		while (start)
		{
			prev = start->next;
			delete start;
			start = prev;
		}
		count = 0;
	}
	void push_front(int value)//�������� � ������
	{
		list* start = new list();
		if (prev == NULL)
		{
			prev = next = start;
			start->value = value;
		}
		else 
		{
			start->next = prev;
			prev->prev = start;
			prev = start;
			prev->value = value;
			prev->prev = NULL;
		}
		++count;
	}
	void push_back(int value)//�������� � �����
	{
		list* start = new list();
		if (next == NULL)
		{
			next = prev = start;
			start->value = value;
		}
		else
		{
			start->prev = next;
			next->next = start;
			next = start;
			next->value = value;
			next->next = NULL;
		}
		++count;
	}
	void pop_front()//������� �������
	{
		list* start;
		if (prev != NULL) 
		{
			start = prev;
			prev = prev->next;
			delete start;
			if (prev == NULL)
				next = NULL;
			else
				prev->prev = NULL;
			--count;
		}
	}
	void pop_back()//������� � �����
	{
		list* start;
		if (next != NULL) {
			start = next;
			prev = prev->prev;
			delete start;
			if (next == NULL)
				prev = NULL;
			else
				next->next = NULL;
			--count;
		}
	}
	bool is_empty()//���� �� ������
	{
		if (prev == next)
			return false;
		else
			return true;
	}
	void _print()//����� ������
	{
		list* start = new list;
		start =prev ;
		while (start != NULL) 
		{
			cout << start->value;
			start = start->next;
		}
	}
};
int priority(char ch)//��������� ��������
{
	if (ch < 0) // ������� ��������
		return 4;
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '*' || ch == '/')
		return 2;
	if (ch == '^')
		return 3;
	return -1;
}
void printf_ch(char ch) //����� ���������
{
	if (ch < 0) 
	{
		switch (-ch) 
		{
		case '+': 
			cout << '+'; 
			break;
		case '-': 
			cout << '-';
			break;
		}
	}
	else 
	{
		switch (ch) 
		{
		case '+': 
			cout << '+';
			break;
		case '-': 
			cout << '-';
			break;
		case '*': 
			cout << '*';
			break;
		case '/':
			cout << '/';
			break;
		case '^':
			cout << '^';
			break;
		}
	}
}
void record()//������� � �������� �������� ������
{
	bool scobka = true;
	_stack B;
	string s;
	cin >> s;
	int i = 0;
	int count = s.length();//����� ������
	while(i<count)
	{
		if (s[i] == '(') 
		{
			B._push('(');
			scobka = true;
		}
		else 
		if (s[i] == ')') 
		{
			while (B._top() != '(') 
			{
				printf_ch(B._top());
				B._pop();
			}
			B._pop();
			scobka = false;
		}
		else 
		if (s[i]=='-'|| s[i] == '+' || s[i] == '*' || s[i] == '/'||s[i]=='^') 
		{
			char ch = s[i];
			if (scobka && (ch=='+'||ch=='-'))
				ch = -ch;
			while (B.is_empty() && ((ch >= 0 && (priority(B._top()) >= priority(ch))) ||(ch< 0 && priority(B._top()) > priority(ch))))
			{
				printf_ch(B._top());
				B._pop();
			}
			B._push(ch);
			scobka = true;
		}
		else 
		{
			int number = 0;
			while (i < count && s[i]>='0'&& s[i]<='9')
				number = number * 10 + s[i++] - '0';
			cout << number;
			--i;
			scobka = false;
		}
		++i;
	}
		while (B.is_empty()) 
		{
			printf_ch(B._top());
			B._pop();
		}
		system("pause");
};
int main()
{
	setlocale(0, "");
	while (true)
	{
		cout << "������� ������"<<endl;
		Sleep(2000);
		record();
		system("cls");
	}
	return 0;
}