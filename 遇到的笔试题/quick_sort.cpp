#include<iostream>
#include<vector>
//网易笔试题，哎忘了快速排序了，一定要多写写代码才记住
//特意写一次quick sort来记住。
using namespace std;
struct input {
	int n;
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
	for (int i = begin; i <= end; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return i;

}

void quick_sort_once(int *arr, int begin, int end) {
	if (begin >= end)
		return;
	int pivotPos = Partition(arr, begin, end);
	quick_sort_once(arr, begin, pivotPos);
	quick_sort_once(arr, pivotPos+1, end);
	cout << "one term after:";
	for (int i = begin; i <= end; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void quick_sort(int * arr, size_t size) {
	quick_sort_once(arr, 0, size-1);
}

int main(int argv, char* argc[]) {
	vector<input> inputs;
	int n;
	do {
		cin >> n;
		if (!n) continue;
		int *tmp = new int[n];
		for (int i = 0; i < n; i++) {
			cin >> tmp[i];
		}
		input myInput = { n,tmp };
		inputs.push_back(myInput);
	} while (n);
	for (vector<input>::iterator itor = inputs.begin(); itor < inputs.end(); itor++) {
		quick_sort(itor->arr, itor->n);
		for (int i = 0; i < itor->n; i++) {
			cout << itor->arr[i]<<" ";
		}
	}
	return 0;
}