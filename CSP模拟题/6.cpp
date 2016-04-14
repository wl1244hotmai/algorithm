///**
//问题描述：
//有 N 个非零且各不相同的整数。请你编一个程序求出它们中有多少对相反数(a 和 - a 为一对相反数)。
//输入格式
//第一行包含一个正整数 N。(1 ≤ N ≤ 500)。
//第二行为 N 个用单个空格隔开的非零整数, 每个数的绝对值不超过1000, 保证这些整数各不相同。
//输出格式
//只输出一个整数, 即这 N 个数中包含多少对相反数。
//样例输入
//5
//1 2 3 - 1 - 2
//样例输出
//2
//*/
//
//#include<iostream>
//#include<vector>
//using namespace std;
//int calDiverseNum(vector<int> input, vector<int> num) {
//	int count = 0;
//	int tmp = 0;
//	for (vector<int>::iterator itor = input.begin(); itor < input.end(); itor++) {
//		if (*itor > 0) {
//			tmp = *itor;
//		}
//		else{
//			tmp = -*itor;
//		}
//		num[tmp]++;
//		if (num[tmp] == 2) {
//			count++;
//		}
//	}
//	return count;
//}
//int main(int argv, char* argc[]) {
//	int N;
//	cin >> N;
//	vector<int> input(N,0);
//	vector<int> num(1000, 0);
//	for (int i = 0; i < N; i++) {
//		cin >> input[i];
//	}
//	cout << calDiverseNum(input,num);
//	return 0;
//}