#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/**
*  return the maximum number of a and b;
*/
int max(int a, int b) {
	return (a < b) ? b : a;
}

/**
* get the maximum result by recursion
*/
int get_max(int **array, int i_index, int j_index, int m, int n, bool upFlag, bool downFlag) {
	int max_m = -1;
	if (i_index - 1 >= 0
		&& array[i_index - 1][j_index] != -1
		&& upFlag == true)
	{
		max_m = get_max(array, i_index - 1, j_index, m, n, true, false);
	}
	if (i_index + 1 < n
		&& array[i_index + 1][j_index] != -1
		&& downFlag == true)
	{
		max_m = max(max_m, get_max(array, i_index + 1, j_index, m, n, false, true));
	}
	if (j_index + 1 < m
		&& array[i_index][j_index + 1] != -1)
	{
		max_m = max(max_m, get_max(array, i_index, j_index + 1, m, n, true, true));
	}
	if (max_m == -1)
	{
		if (j_index == m - 1)
		{
			return array[i_index][j_index];
		}
		if (j_index < m - 1)
		{
			return -1;
		}
	}
	return array[i_index][j_index] + max_m;
}

int main(int argv, char argc)
{
	int maxValue = -1;
	bool upFlag = true;
	bool downFlag = true;
	int n, m;
	do {
		cin >> n >> m;
		cin.get(); //get the '\n' after input m and n;
	} while (!(n >= 1 && m <= 500 && m >= 1));
	// create dynamic array;
	int **array = new int *[n];
	for (int i = 0; i < n; i++) {
		array[i] = new int[m];
		string line;
		//input each line tp array;
		getline(cin, line, '\n'); 
		istringstream in(line);
		for (int j = 0; j < m; j++)
		{
			in >> array[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		if (array[i][0] != -1)
		{
			maxValue = max(maxValue, get_max(array, i, 0, m, n, true, true));
		}
	}
	cout << maxValue;
	//delete array;
	for (int i = 0; i < n; i++)
	{
		delete[] array[i];
		array[i] = NULL;
	}
	delete[]array;
	array = NULL;
	//return 0;
	system("pause");
}
