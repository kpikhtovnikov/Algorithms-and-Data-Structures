#include<iostream>
#include<vector>
#include<math.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include<stack>
using namespace std;
void printArray(vector<int> arr, int N)
{
	for (int i = 0; i < N; i++)
		printf("%d  ", arr[i]);
	printf("\n");
}
int Get_Minrun(int N)
{
	int r = 0;
	while (N >= 64)
	{
		r = r | (N & 1);
		N >>= 1;
	}
	return N + r;
}
void reverse(vector<int>& mas, int left, int right)
{
	for (int i = left; i < (right - left) / 2; i++)
	{
		if (mas[left] != mas[right - 1])
			swap(mas[left], mas[right - 1]);
	}
}
void insertionSort(vector<int>& arr, int left, int right)
{
	for (int i = left + 1; i <= right; i++)
	{
		int temp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > temp && j >= left)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}

void merge(vector<int>& arr, int x1, int x2, int y1, int y2)
{
	int len1 = x2 - x1, len2 = y2 - y1;
	vector<int>left(len1);
	vector<int>right(len2);
	for (int i = 0; i < len1; i++)
		left[i] = arr[x1 + i];
	for (int i = 0; i < len2; i++)
		right[i] = arr[y1 + i];
	int i = 0;
	int j = 0;
	int k = x1;
	while (i < len1 && j < len2)
	{
		if (left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < len1)
	{
		arr[k] = left[i];
		k++;
		i++;
	}
	while (j < len2)
	{
		arr[k] = right[j];
		k++;
		j++;
	}
}
void tim_sort(vector<int>& arr, int N)
{
	stack<pair<int, int>> _stack;
	pair<int, int> X, Y, Z;
	vector<int>mas(N);
	int minrun = Get_Minrun(N);
	int i = 1, increasing_run = 1, decreasing_run = 1, run = 0, left = 0, right = 0;
	while (i < N)
	{
		if (arr[i] > arr[i - 1] && decreasing_run == 1)
		{
			increasing_run++;
		}
		else
		{
			if (arr[i] < arr[i - 1] && increasing_run == 1)
			{
				decreasing_run++;
			}
			else
			{
				if (increasing_run > 1 && increasing_run < minrun)
				{
					run = increasing_run + (minrun - increasing_run);
					right = right + run - 1;
					if (right >= N)
					{
						right = N - 1;
						insertionSort(arr, left, N - 1);
						_stack.push({ left, right });
						left = i = right;
					}
					else
					{
						insertionSort(arr, left, right);
						_stack.push({ left, right });
						if (right + 1 < N)
							left = right = i = right + 1;
						else
							left = i = right;
					}
					decreasing_run = 1;
					increasing_run = 1;
				}
				if (decreasing_run > 1 && decreasing_run < minrun)
				{
					reverse(arr, left, right + decreasing_run);
					run = decreasing_run + (minrun - decreasing_run);
					right = right + run - 1;
					if (right >= N)
					{
						right = N - 1;
						insertionSort(arr, left, N - 1);
						_stack.push({ left, right });
						left = i = right;
					}
					else
					{
						insertionSort(arr, left, right);
						_stack.push({ left, right });
						if (right + 1 < N)
							left = i = right = right + 1;
						else
							left = i = right;
					}
					decreasing_run = 1;
					increasing_run = 1;
				}
				if (increasing_run > 1 && increasing_run >= minrun)
				{
					right = right + increasing_run + 1;
					if (right >= N)
					{
						right = N - 1;
						insertionSort(arr, left, N - 1);
						_stack.push({ left, right });
						left = i = right;
					}
					else
					{
						insertionSort(arr, left, right);
						_stack.push({ left, right });
						if (right + 1 < N)
							left = i = right = right + 1;
						else
							left = i = right;
					}
					decreasing_run = 1;
					increasing_run = 1;
				}
				if (decreasing_run > 1 && decreasing_run >= minrun)
				{
					reverse(arr, left, right + decreasing_run);
					right = right + decreasing_run + 1;
					if (right >= N)
					{
						right = N - 1;
						insertionSort(arr, left, N - 1);
						_stack.push({ left, right });
						left = i = right;
					}
					else
					{
						insertionSort(arr, left, right);
						_stack.push({ left, right });
						if (right + 1 < N)
							left = i = right = right + 1;
						else
							left = i = right;
					}
					decreasing_run = 1;
					increasing_run = 1;
				}
			}
		}
		while (_stack.size() >= 3)
		{
			X = _stack.top();
			_stack.pop();
			Y = _stack.top();
			_stack.pop();
			Z = _stack.top();
			_stack.pop();
			if (X.second - X.first > (Y.second - Y.first + Z.second - Z.first) && Y.second - Y.first > Z.second - Z.first)
			{
				merge(arr, X.first, X.second, Y.first, Y.second);
				_stack.push({ Z.first, Z.second });
				_stack.push({ Y.first, Y.second });

			}
			else
			{
				if (X.second - X.first > Z.second - Z.first)
				{
					merge(arr, Z.first, Z.second, Y.first, Y.second);
					_stack.push({ Z.first, Y.second });
					_stack.push({ X.first, X.second });
				}
				else
				{
					merge(arr, Y.first, Y.second, X.first, X.second);
					_stack.push({ Z.first, Z.second });
					_stack.push({ Y.first, X.second });
				}
			}
		}
		if (_stack.size() < 3 && left == N - 1)
		{
			Y = _stack.top();
			_stack.pop();
			X = _stack.top();
			_stack.pop();
			merge(arr, X.first, X.second, Y.first, Y.second);
		}
		++i;
	}
}
void qsort(vector<int>& arr, int first, int last)
{
	if (first < last)
	{
		int left = first, right = last, middle = arr[(left + right) / 2];
		do
		{
			while (arr[left] < middle)
				left++;
			while (arr[right] > middle)
				right--;
			if (left <= right)
			{
				int tmp = arr[left];
				arr[left] = arr[right];
				arr[right] = tmp;
				left++;
				right--;
			}
		} while (left <= right);
		qsort(arr, first, right);
		qsort(arr, left, last);
	}
}
void time_programm()
{
	int N1 = 1000, N2 = 10000, N3 = 100000;
	int N = 0;
	unsigned int _time;
	vector<int> mas1(N1);
	vector<int> mas2(N2);
	vector<int> mas3(N3);
	srand(time(NULL));
	for (int i = 0; i < N1; ++i)
	{
		mas1[i] = rand() % 10001 - 5000;
	}
	srand(time(NULL));
	for (int i = 0; i < N2; ++i)
	{
		mas2[i] = rand() % 10001 - 5000;
	}
	srand(time(NULL));
	for (int i = 0; i < N3; ++i)
	{
		mas3[i] = rand() % 10001 - 5000;
	}
	cout << "random values" << endl;
	cout << "timesort	insertionsort	qsort" << endl;
	vector<int> arr1(N1);
	vector<int> arr2(N2);
	vector<int> arr3(N3);
	arr1 = mas1;		//1000
	arr2 = mas1;
	arr3 = mas1;
	_time = clock();
	tim_sort(arr1, N1);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	insertionSort(arr2, 0, N1 - 1);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	qsort(arr3, 0, N1 - 1);
	_time = clock() - _time;
	cout << _time << "		" << 1000 << endl;
	arr1 = mas2;		//100000
	arr2 = mas2;
	arr3 = mas2;
	_time = clock();
	tim_sort(arr1, N2);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	insertionSort(arr2, 0, N2 - 1);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	qsort(arr3, 0, N2 - 1);
	_time = clock() - _time;
	cout << _time << "		" << 10000 << endl;
	arr1 = mas3;		//1000000
	arr2 = mas3;
	arr3 = mas3;
	_time = clock();
	tim_sort(arr1, N3);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	insertionSort(arr2, 0, N3 - 1);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	qsort(arr3, 0, N3 - 1);
	_time = clock() - _time;
	cout << _time << "		" << 100000;
	for (int i = 0; i < N1; ++i)
	{
		mas1[i] = i;
	}
	for (int i = 0; i < N2; ++i)
	{
		mas2[i] = i;
	}
	for (int i = 0; i < N3; ++i)
	{
		mas3[i] = i;
	}
	cout << endl;
	cout << "sorted values" << endl;
	cout << "timesort	insertionsort	qsort" << endl;
	arr1 = mas1;		//1000
	arr2 = mas1;
	arr3 = mas1;
	_time = clock();
	tim_sort(arr1, N1);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	insertionSort(arr2, 0, N1 - 1);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	qsort(arr3, 0, N1 - 1);
	_time = clock() - _time;
	cout << _time << "		" << 1000 << endl;
	arr1 = mas2;		//100000
	arr2 = mas2;
	arr3 = mas2;
	_time = clock();
	tim_sort(arr1, N2);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	insertionSort(arr2, 0, N2 - 1);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	qsort(arr3, 0, N2 - 1);
	_time = clock() - _time;
	cout << _time << "		" << 10000 << endl;
	arr1 = mas3;		//1000000
	arr2 = mas3;
	arr3 = mas3;
	_time = clock();
	tim_sort(arr1, N3);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	insertionSort(arr2, 0, N3 - 1);
	_time = clock() - _time;
	cout << _time << "		";
	_time = clock();
	qsort(arr3, 0, N3 - 1);
	_time = clock() - _time;
	cout << _time << "		" << 100000;
}
int main()
{
	printf("Given Array is\n");
	time_programm();
	system("pause");
	return 0;
}
