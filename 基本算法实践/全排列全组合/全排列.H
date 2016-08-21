#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

class Permutation {
private:
	string chars;
	int length;
	void swap(int i, int j) {
		char temp = chars[i];
		chars[i] = chars[j];
		chars[j] = temp;
	}
	void print(string chars) {
		for_each(chars.begin(), chars.end(), [&](char c) {
			cout << c << " ";
		});
		cout << endl;
	}
	void reverse(int i) {
		int j = length - 1;
		while (i < j) {
			swap(i, j);
			i++; j--;
		}
	}
public:
	Permutation() {
		//init
		getline(cin, chars);
		sort(chars.begin(), chars.end());
		length = chars.size();
	}

	//递归实现
	void displayPermutation(int start) {
		//全排列 A B B D
		if (start == length) {
			print(chars);
		}
		for (int i = start; i < length; i++) {
			if (i == start || chars[i] != chars[i - 1]) {
				swap(start, i);
				displayPermutation(start + 1);
				swap(start, i);
			}
		}
	}

	//非递归实现
	//字典序排列
	//a.输出序列本身
	//b.从右至左找到第一个a_j，使得a_j < a_{ j + 1 }且a_{ j + 1 } > a_{ j + 2 } > ... > a_n
	//c.在a[j + 1..n]中找到最小的a_k使得a_j < a_k，交换a_j和a_k
	//d.将a[j + 1..n]逆序，输出当前序列
	//重复第2~5步，直到找不到第二步中合适的a_j
	void displayPermutation_2(int start) {
		string::reverse_iterator it;
		do {
			//打印本次
			print(chars);

			//找到最后的升序
			int i = chars.size() - 1;
			while (i>=0 && chars[i] >= chars[i + 1]) i--;
			
			if (i < 0) break;

			//找到i之后，比i大的最后一个数
			int j = chars.size() - 1;
			while (j > i && chars[j] <= chars[i]) j--;
			
			//交换
			swap(i, j);

			//将i之后的排列逆序；
			reverse(i+1);
		} while (true);
	}
};