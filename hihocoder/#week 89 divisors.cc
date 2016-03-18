/* hihocoder week 89 因子数最大问题
时间限制:10000ms
单点时限 : 1000ms
内存限制 : 256MB
描述
Given an integer n, for all integers not larger than n, find the integer with the most divisors.If there is more than one integer with the same number of divisors, print the minimum one.

输入
One line with an integer n.
For 30 % of the data, n ≤ 103
For 100 % of the data, n ≤ 1016

输出
One line with an integer that is the answer.

样例输入
100
样例输出
60
*/

/**
	思路：深度优先搜索，从2开始遍历；pi为质数，ni为质数的个数
	每个数都等于 p1*n1 * p2*n2 * .... *pi *ni;
	因子树个数为(n1+1)*(n2+1)*...*(ni+1);

	存在性质,对于最小解,若p1<p2;则n1>=n2; 
	证明：反证，如果n1>n2,则存在因子个数一样但是更小的数，矛盾。
*/

#include<iostream>
#include<math.h>
using namespace std;
long long maxDivisors = 0;
long long result = 0;
long long N;
void DFS(const int* prime, long long now, long long divisors, long long lastNi) {
	if (divisors > maxDivisors
		|| divisors == maxDivisors && now < result) { // 2*2*2*3 = 24, 4*2 = 8个因子，2*3*5 = 30, 2*2*2 = 8个因子
		maxDivisors = divisors;
		result = now;
	}
	long long i = 1;
	while (now * pow(*prime, i) <= N
		&& (i <= lastNi || *prime == 2)) {
		DFS(prime + 1, now * pow(*prime, i), divisors * (i+1), i+1);
		i++;
	}
}
int main(int argv, char* argc[]) {
	const int prime[] = { 2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 , 29 , 31 ,37, 41, 43};
	cin >> N;
	if (N == 1) {
		cout << 1;
		return 0;
	}
	DFS(prime, 1, 1, 1);
	cout << result;
	system("pause");
	return 0;
}