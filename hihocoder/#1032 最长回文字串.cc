/**
* LPS Longest Palindromic Substring
* 解法1：后缀树；
* 解法2：向左向右寻找最长半径 (ABCBA -> *A*B*C*B*A*)
*/

#include <iostream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <math.h>

using namespace std;


char* processStr(char* targetStr) {
	int targetstrLength = strlen(targetStr);
	char* resultStr = new char[targetstrLength * 2 + 2];
	for (int i = 0; i < targetstrLength; i++) {
		resultStr[2 * i] = '#';
		resultStr[2 * i + 1] = targetStr[i];
	}
	resultStr[targetstrLength * 2] = '#';
	resultStr[targetstrLength * 2 + 1] = 0;
	return resultStr;
}

int getLPS_SolutionTwo(char* targetStr) {
	char* ProcessedStr = processStr(targetStr);
	delete targetStr;
	int ProcessedStrLength = strlen(ProcessedStr);
	int* Length = new int[2000100];
// 	int Length[2000100] = {0};
	int mx = 0;
	int maxId = 0;
	int maxLength = 0;
    int i_mirror = 0;
	for (int i = 1; ProcessedStr[i]!=0; i++) {
        // Length[i] = 1;
        i_mirror = 2 * maxId - i;
		Length[i] = (mx > i)? min(Length[i_mirror], mx - i) : 1;
		while ((i - Length[i]) >= 0
			&& (i + Length[i])<ProcessedStrLength
			&& ProcessedStr[i + Length[i]] == ProcessedStr[i - Length[i]]) {
			Length[i]++;
		}
		Length[i] -= 1;
		if (i + Length[i] > mx) {
			mx = i + Length[i];
			maxId = i;
		}
		maxLength = max(maxLength, Length[i]);
	}
	delete Length;
	return maxLength;
}


int main(int argv, char argc) {

	int N = 0;
	cin >> N;
	char **myStr = new char*[N];
	for (int i = 0; i < N; i++) {
		myStr[i] = new char[1000001];
		cin >> myStr[i];
	}
	for (int i = 0; i < N; i++) {
		cout << getLPS_SolutionTwo(myStr[i]) << endl;
	}
// 	delete myStr;
//	system("pause");
	return 0;
}
