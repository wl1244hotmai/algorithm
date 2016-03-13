#include<iostream>
using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}

//递归解法
//int getMaxReward(int** num, int depth, int index,int length) {
//	if (depth == length-1) {
//		return num[depth][index];
//	}
//	int maxReward = num[depth][index], 
//		left = 0, 
//		right = 0;
//	left = getMaxReward(num, depth + 1, index, length);
//	right = getMaxReward(num, depth + 1, index+1, length);
//	maxReward += max(left,right);
//	return maxReward;
//}

//动态规划
int getMaxReward(int** num, int depth, int index, int length) {
	if (length == 1) {
		return num[0][0];
	}
	for (int i = 1; i < length;i++) {
		for (int j = 0; j < i+1; j++){
			if (j == 0) {
				num[i][j] += num[i - 1][j];
				continue;
			}
			if (j == i) {
				num[i][j] += num[i - 1][j - 1];
				continue;
			}
			num[i][j] += max( num[i - 1][j] ,num[i - 1][j - 1]);
		}
	}
	int maxReward = 0;
	for (int j = 0; j < length; j++)  {
		maxReward = max(maxReward, num[length - 1][j]);
	}
	return maxReward;
}

int main(int argc, char* argv[]) {
	int n = 0;
	cin >> n;
	int **num = new int*[n];
	for (int i = 0; i<n; i++) {
		num[i] = new int[i+1];
		for (int j = 0; j < i+1; j++) {
			cin >> num[i][j];
		}
	}
	int res = getMaxReward(num, 0, 0, n);
	cout<<res<<endl;
	for (int i = 0; i < n; i++) {
		delete[] num[i];
	}
	system("pause");
	return 0;
}