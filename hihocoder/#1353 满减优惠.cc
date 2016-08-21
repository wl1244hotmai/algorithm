// 时间限制:10000ms
// 单点时限:1000ms
// 内存限制:256MB

// 描述
// 最近天气炎热，小Ho天天宅在家里叫外卖。他常吃的一家餐馆一共有N道菜品，价格分别是A1, A2, ... AN元。并且如果消费总计满X元，还能享受优惠。小Ho是一个不薅羊毛不舒服斯基的人，他希望选择若干道不同的菜品，使得总价在不低于X元的同时尽量低。
// 你能算出这一餐小Ho最少消费多少元吗？
// 输入
// 第一行包含两个整数N和X，(1 <= N <= 20, 1 <= X <= 100)
// 第二行包含N个整数A1, A2, ...， AN。(1 <= Ai <= 100)
// 输出
// 输出最少的消费。如果小Ho把N道菜都买了还不能达到X元的优惠标准，输出-1。
// 样例输入
// 10 50
// 9 9 9 9 9 9 9 9 9 8
// 样例输出
// 53

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxInt = 2147483647;

void solution_1(){
	int N, X;
	cin >> N >> X;
	vector<int> foods(N + 1, 0);
	for (int i = 1; i <= N; i++) {
		cin >> foods[i];
	}
	vector<vector<int> > best(N+1,vector<int>(X+1, maxInt));
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		sum += foods[i];
		for (int j = 1; j <= X; j++) {
			if (j > sum) {
				break;
			}
			if (j <= foods[i]) {
				best[i][j] = min(best[i - 1][j], foods[i]);
			}
			else if (best[i - 1][j] == maxInt) {
				best[i][j] = best[i - 1][j - foods[i]] + foods[i];
			}	
			else {
				best[i][j] = min(best[i - 1][j], best[i - 1][j - foods[i]] + foods[i]);
			}
		}
	}
	if (best[N][X] == maxInt)
		cout << -1;
	else
		cout << best[N][X]<<endl;
	return;
}