#include<iostream>
#include<vector>
/** 
���ױ����⣬�����˿��������ˣ�һ��Ҫ��дд����ż�ס
����N,M
N��ʾ���������M��ʾҪ��ڼ��������(��0��ʼ����)
N����0��ʾ������
Ȼ�������������ݣ�
Ҫ�������M��������Ƕ��١�

������
ͨ���������� quick_sort_once��ʵ�֡�
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