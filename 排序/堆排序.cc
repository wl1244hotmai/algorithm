#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//∂—≈≈–Ú
//20,30,90,40,70,110,60,10,100,50,80
#define lchild (pos<<1)
#define rchild ((pos<<1) + 1)
class Heap_Sort {
private:
	void swap(int* a, int* b) {
		int temp = *a;
		*a = *b;
		*b = temp;
	}

	void heap(int pos, vector<int>& arr,int size) {
		int max = pos;
		if (lchild <= size && arr[max] < arr[lchild] ) {
			max = lchild;
		}
		if (rchild <= size && arr[max] < arr[rchild] ) {
			max = rchild;
		}
		if (max != pos) {
			swap(&arr[max], &arr[pos]);
			heap(max, arr, size);
		}
	}

	void build_heap(vector<int>& arr,int size) {
		for (int i = size >> 1; i >= 1; i--) {
			heap(i, arr,size);
		}
	}
public:
	void heap_sort(vector<int>& arr,int size) {
		int j = size;
		build_heap(arr,size);
		for (; j > 1; j--) {
			size--;
			swap(&arr[1], &arr[j]);
			heap(1, arr,size);
		}
	}

};


int main() {
	Heap_Sort heap_sort;
	vector<int> arr{0, 20,30,90,40,70,110,60,10,100,50,80 };
	heap_sort.heap_sort(arr,arr.size()-1);
	for_each(arr.begin()+1, arr.end(), [&](int a) {
		cout << a << " ";
	});
	return 0;
}


