/* hihocoder week 89 �������������
ʱ������:10000ms
����ʱ�� : 1000ms
�ڴ����� : 256MB
����
Given an integer n, for all integers not larger than n, find the integer with the most divisors.If there is more than one integer with the same number of divisors, print the minimum one.

����
One line with an integer n.
For 30 % of the data, n �� 103
For 100 % of the data, n �� 1016

���
One line with an integer that is the answer.

��������
100
�������
60
*/

/**
	˼·�����������������2��ʼ������piΪ������niΪ�����ĸ���
	ÿ���������� p1*n1 * p2*n2 * .... *pi *ni;
	����������Ϊ(n1+1)*(n2+1)*...*(ni+1);

	��������,������С��,��p1<p2;��n1>=n2; 
	֤������֤�����n1>n2,��������Ӹ���һ�����Ǹ�С������ì�ܡ�
*/

#include<iostream>
#include<math.h>
using namespace std;
long long maxDivisors = 0;
long long result = 0;
long long N;
void DFS(const int* prime, long long now, long long divisors, long long lastNi) {
	if (divisors > maxDivisors
		|| divisors == maxDivisors && now < result) { // 2*2*2*3 = 24, 4*2 = 8�����ӣ�2*3*5 = 30, 2*2*2 = 8������
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