#include<iostream>
#include<vector>
/** 
网易笔试题，哎忘了快速排序了，一定要多写写代码才记住
输入N,M
N表示数组个数，M表示要求第几大的数字(从0开始计数)
N输入0表示结束。
然后输入数组数据，
要求给出第M大的数字是多少。

方法：
通过快速排序 quick_sort_once来实现。
*/
using namespace std;
struct input {
	int n,k;
	int * arr;
};

int Partition(int * arr, int begin, int end) {
	int i = begin, j = end;
	int pivot = arr[begin];
	while (i < j) {
		while (i < j && pivot <= arr[j]) {
			j--;
		}
		if (i < j) {
			arr[i++] = arr[j];
		}
		while (i < j && pivot >= arr[i]) {
			i++;
		}
		if (i < j) {
			arr[j--] = arr[i];
		}
	}
	arr[i] = pivot;
	return i;
}

int quick_sort_once(int *arr, int begin, int end, int k) {
	int pivotPos = Partition(arr, begin, end);
	if (k == pivotPos) {
		return arr[k];
	}
	if (k < pivotPos) {
		return quick_sort_once(arr, begin, pivotPos, k);
	}
	else {
		return quick_sort_once(arr, pivotPos + 1, end, k);
	}
}

int kth_number(int* arr,size_t size, int k) {
	int kth_number = 0;
	kth_number = quick_sort_once(arr, 0, size - 1, k);
	return kth_number;
}
int main(int argv, char* argc[]) {
	vector<input> inputs;
	int n, k;
	do {
		cin >> n >> k;
		if (!n) continue;
		int *tmp = new int[n];
		for (int i = 0; i < n; i++) {
			cin >> tmp[i];
		}
		input myInput = { n,k,tmp };
		inputs.push_back(myInput);
	} while (n);
	for (vector<input>::iterator itor = inputs.begin(); itor < inputs.end(); itor++) {
		/*	for (int j = 0; j < itor->n; j++) {
		cout << kth_number(itor->arr, itor->n, itor->n - 1 - j) << " ";
		}*/
		cout << kth_number(itor->arr, itor->n, itor->n - 1 - itor->k);
	}
	return 0;
}