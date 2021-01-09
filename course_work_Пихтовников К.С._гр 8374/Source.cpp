#include<iostream>
#include"windows.h"
#include <string>
#include <stdlib.h>
#include <fstream>
using namespace std;
const int number_of_vertices = 50, down = 80, up = 72, _enter = 13;
void gotoxy(int x, int y)//��������� ������� �� ������� x y 
{
	COORD coord;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

class alg_Kruskala
{
private:
	struct top
	{
		string top_one;
		string top_two;
		short weight;
	};
	struct nodes
	{
		string top = "";
		short number = 0;
	};
	top* _array= new top[1225];//�� ������� �� ������������� max ���-�� ����� ��� 50*49/2=1225
	nodes* mas = new nodes[50];
	int N = 0, size = 0;
	int check(top first, top second, int count)
	{
		if (count == 0)
		{
			return first.weight > second.weight;
		}
		else if (count == 1)
		{
			if (first.top_one > second.top_one or (first.top_one == second.top_one) and (first.top_two > second.top_two))
				return 1;
			else
				return 0;
		}
	}
	bool set(top s, int N)
	{
		int i =	0, j = 0;
		while (mas[i].top != s.top_one)
		{
			i++;
		};
		while (mas[j].top != s.top_two)
		{
			j++;
		};
		if (mas[i].number != mas[j].number)
		{
			if (mas[i].number and mas[j].number)
			{
				int num = mas[i].number;
				for (int k = 0; k < N; ++k)
				{
					if (mas[k].number == num)
						mas[k].number = mas[j].number;
				}
			}
			else
			{
				if (mas[i].number)
					mas[j].number = mas[i].number;
				else
					mas[i].number = mas[j].number;
			}
		}
		else if (!mas[i].number)
		{
			static int number = 1;
			mas[j].number = mas[i].number = number++;
		}
		else
			return 0;
		return 1;
	}
public:
	void in_File()	
	{
		bool f1, f2;
		ifstream file;
		file.open("input.txt");
		if (file.is_open())
		{
			string s;
			while (getline(file, s))
			{
				_array[N].top_one = s.substr(0, s.find(' ', 0));
				s.erase(0, s.find(' ', 0) + 1);
				_array[N].top_two = s.substr(0, s.find(' ', 0));
				s.erase(0, s.find(' ', 0) + 1);
				_array[N].weight = stoi(s);
				f1 = f2 = 1;
				for (int i = 0; i < size; ++i)
				{
					if (_array[N].top_one == mas[i].top)
						f1 = 0;
					if (_array[N].top_two == mas[i].top)
						f2 = 0;
					if (!(f1 or f2))
						break;
				}
				if (f1)
				{
					mas[size].top = _array[N].top_one;
					size++;
				}
				if (f2)
				{
					mas[size].top = _array[N].top_two;
					size++;
				}
				++N;
			}
			file.close();
		}
	}
	void insertionSort(int count) {
		for (int i = 1; i < N; i++)
		{
			int j = i - 1;
			while (j >= 0 && check(_array[j], _array[j + 1], count))
			{
				top mas = _array[j];
				_array[j] = _array[j + 1];
				_array[j + 1] = mas;
				--j;
			}
		}
	}
	int sum()
	{
		int sum = 0;
		for (int i = 0; i < N; ++i)
			sum += _array[i].weight;
		return sum;
	}
	void output_screeen(int count)
	{
		int x = 0, y = 0;
		for (int i = 0; i < N; ++i)
		{
			if (count == 0)
			{
				gotoxy(x, y);
				cout << _array[i].top_one << " " << _array[i].top_two << " " << _array[i].weight;
				y++;
			}
			else if (count == 1)
			{
				x = 30;
				gotoxy(x, y);
				cout << _array[i].top_one << " " << _array[i].top_two << " " << _array[i].weight;
				y++;
			}
		}
	}
	void algoritm_kruskala() {
		top* answer = new top[size - 1];//size-���������� ������
		int count = 0, i = 0;
		insertionSort(0);
		while (count < size - 1) 
		{
			if (set(_array[i++], size))
			{
				answer[count] = _array[i - 1];	
				count++;
			}
		}
		i = 0;
		while (i < count)
		{
			_array[i] = answer[i];
			i++;
		}
		N = i ;
		insertionSort(1);
	}
};

int main()
{
	setlocale(0, "");
	alg_Kruskala A;
	A.in_File();
	gotoxy(0, 0);
	A.output_screeen(0);
	A.algoritm_kruskala();
	gotoxy(30, 0);
	A.output_screeen(1);
	gotoxy(50, 4);
	cout << "�����";
	gotoxy(51, 5);
	cout << A.sum();
	system("pause");
	return 0;
}
