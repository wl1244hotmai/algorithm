/** 快速排序 **/
//66,13,51,76,81,26,57,69,23
//66,13 51 23,81,26,57,69,76
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partial_sort(int i, int j, vector<int>& arr) {
	int pivot = i;
	while (i<j) {
		//如果选择i作为pivot，则首先从j开始向前，再从i开始向后,
		//vice versa
		while (i<j && arr[j] >= arr[pivot])
			j--;
		while (i<j && arr[i] <= arr[pivot])
			i++;
		swap(&arr[i], &arr[j]);
	}
	swap(&arr[pivot], &arr[i]);
	return i;
}

void quickSort(int i, int j, vector<int>& arr) {
	if (i < j) {
		int m = partial_sort(i, j, arr);
		quickSort(i, m - 1, arr);
		quickSort(m + 1, j, arr);
	}
}

int main() {
	vector<int> arr{ 66,13,51,76,81,26,57,69,23 };
	quickSort(0, arr.size() - 1, arr);
	for_each(arr.begin(), arr.end(), [&](int a) {
		cout << a << " ";
	});
	return 0;
}