#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void Creat(vector <int>&vect)
{
	for (int i = 0; i < vect.size(); i++)
	{
		vect[i] = rand() % 100;
	}
}

void Print(vector <int> vect)
{
	for (int i = 0; i < vect.size(); i++)
	{
		cout << vect[i] << "\t";
	}
	cout << endl;
}

void Series(vector<vector<int>>&vect_series, vector <int> vect) 
{
	int i = 0;
	while(i < vect.size())
	{
		vector <int> series;
		series.push_back(vect[i]);
		i++;
		while (i<vect.size() && vect[i-1]<vect[i])
		{
			series.push_back(vect[i]);
			i++;
		}
		vect_series.push_back(series);
	}
}

vector<int>Merge_Series(vector<int> vect1, vector<int> vect2) 
{
	int n1 = 0;
	int n2 = 0;
	vector<int>t;
	while (n1 < vect1.size() && n2 < vect2.size())
	{
		if (vect1[n1] <= vect2[n2])
		{
			t.push_back(vect1[n1]);
			n1++;
		}
		else
		{
			t.push_back(vect2[n2]);
			n2++;
		}
	}
	while (n1 < vect1.size())
	{
		t.push_back(vect1[n1]);
		n1++;
	}
	while (n2 < vect2.size())
	{
		t.push_back(vect2[n2]);
		n2++;
	}
	return t;
}

vector<int> Natural_Sort(vector <int> vect)
{
	vector<vector<int>>vect_series;
	Series(vect_series, vect);
	while (vect_series.size() >= 2)
	{
		vector <int>merge;
		merge = Merge_Series(vect_series[0],vect_series[1]);
		vect_series.push_back(merge);
		vect_series.erase(vect_series.begin());
		vect_series.erase(vect_series.begin());
	}
	return vect_series[0];	
}

void Balanc_Sort(vector <int> &vect)
{
	if (vect.size() < 2)
		return;
	if (vect.size() == 2)
	{
		if (vect[0] > vect[1])
		{
			int t = vect[0];
			vect[0] = vect[1];
			vect[1] = t;
		}
		return;
	}
	vector<int> left;
	vector<int> right;
	int mid = vect.size() / 2;
	for (int i = 0; i < mid; i++)
	{
		left.push_back(vect[i]);
	}
	for (int i = mid; i < vect.size(); i++)
	{
		right.push_back(vect[i]);
	}
	Balanc_Sort(left);
	Balanc_Sort(right);
	vect = Merge_Series(left, right);
}

void Fib(int length, int& size1, int& size2)
{
	int t;
	size1 = 0;
	size2 = 1;
	do {
		t = size2;
		size2 = size1 + size2;
		size1 = t;
	} while (size1 + size2 < length);
}

vector<vector<int>> Split_Series(vector<int> vect, int& seriesSize)
{
	vector<vector<int>> result;
	int length = 8;
	if (vect.size() >= length) {
		while (vect.size() % length != 0) {
			length++;
		}
	}
	else {
		length = vect.size();
	}

	seriesSize = vect.size() / length;
	for (int i = 0; i < length; i++) {
		vector<int> series;
		for (int j = 0; j < seriesSize; j++) {
			series.push_back(vect[i * seriesSize + j]);
		}
		result.push_back(series);
	}

	return result;
}

vector<int> Get_NULL(int size)
{
	vector<int> result;
	for (int i = 0; i < size; i++) {
		result.push_back(NULL);
	}
	return result;
}

vector<vector<int>> Merges_series(vector<vector<int>>& series1, vector<vector<int>>& series2)
{
	vector<vector<int>> result;
	int size = series2.size();
	for (int i = 0; i < size; i++) {
		result.push_back(Merge_Series(series1[i], series2[i]));
	}

	series1.erase(series1.begin(), series1.begin() + size);
	series2.clear();

	return result;
}

vector<int> Miltiphase_Sort(vector<int> vect)
{
	if (!vect.size()) {
		return vect;
	}

	vector<vector<vector<int>>> vects;
	int seriesSize;
	vector<vector<int>> series = Split_Series(vect, seriesSize);

	// Находим размеры линий
	int size1, size2;
	Fib(series.size(), size1, size2);

	// Сортируем серии
	for (int i = 0; i < series.size(); i++) {
		sort(series[i].begin(), series[i].end());
	}

	// Заполняем линии
	vector<vector<int>> series1;
	for (int i = 0; i < size2; i++) {
		series1.push_back(series[i]);
	}
	vects.push_back(series1);

	vector<vector<int>> series2;
	for (int i = size2; i < size2 + size1; i++) {
		series2.push_back((i < series.size()) ? series[i] : Get_NULL(seriesSize));
	}
	vects.push_back(series2);

	vector<vector<int>> series3;
	vects.push_back(series3);

	// Проходы
	while (!vects[1].empty()) {
		vects[2] = Merges_series(vects[0], vects[1]);
		vects.insert(vects.begin(), vects[2]);
		vects.pop_back();
	}

	int lastEmptyIndex = 0;
	while (vects[0][0][lastEmptyIndex] == NULL) {
		lastEmptyIndex++;
	}
	vects[0][0].erase(vects[0][0].begin(), vects[0][0].begin() + lastEmptyIndex);

	return vects[0][0];
}


int main()
{
	system("color F0");
	setlocale (0, "");
	int n=0;
	while (n<=0)
	{
		cout << "Введите количество чисел в массиве: ";
		cin >> n;
	} 
	
	vector<int>vect(n);
	Creat(vect);
	cout << "Начальный массив: ";
	Print(vect);

	int v;
	cout << "1 - СОРТИРОВКА МЕТОДОМ ЕСТЕСТВЕННОГО СЛИЯНИЯ: " << endl;
	cout << "2 - СОРТИРОВКА МЕТОДОМ СБЛАНАСИРОВАННОГО СЛИЯНИЯ:  " << endl;
	cout << "3 - СОРТИРОВКА МЕТОДОМ МНОГОФАЗНОГО СЛИЯНИЯ: " << endl;
	cin >> v;
	if (v == 1)
	{
		cout << "Отсортированный список: " << endl;
		vect=Natural_Sort(vect);
		Print(vect);
	}
	else if (v == 2)
	{
		cout << "Отсортированный список: " << endl;
		Balanc_Sort(vect);
		Print(vect);
	}
	else if (v == 3)
	{
		cout << "Отсортированный список: " << endl;
		vect=Miltiphase_Sort(vect);
		Print(vect);
	}
	else
	{
		cout << "Введено некорректное значение." << endl;
	}
	return 0;
}
