/**
#1048 : ״̬ѹ������

ʱ������:10000ms
����ʱ��:1000ms
�ڴ�����:256MB
����
����ǧ����࣬СHi��СHo���ڵ����˾ٰ���ʳ�ڵĳ��У���Ȼ��ɽ�˺�����СHi��СHo��Ȼ���Ʋ�ס�˷�֮�飬���Ƿ��������Ͷ�뵽����ʳ�ڵĻ���С���ʳ�ڵĸ���̯λ�ϸ������ŷǳ��������˼��С��Ϸ������һ�����������ӵģ�
СHi��СHo�쵽��һ����СΪN*M�ĳ��������ӣ����ǿ��������������װһЩ��СΪ2*1�ĵ��⡣���Ǹ���Ҫ������һ��Ҫ���������װ�������ģ�һ���϶Ҳ���������������ܹ�����Щ������ߡ�
��ô�򵥵�������Ȼ�Ѳ���СHi��СHo���������Ǻܿ�ľ����ŵ����뿪��~
��СHoȴ��ֻ�����ڴˣ������������һ�����⡪�������ж����ַ�����װ�����N*M�������أ�
ֵ��ע����ǣ�������������ӵ�����������������ģ�����N=4, M=3��ʱ����������ַ�������Ϊ��ͬ�����ַ���Ŷ��
��ʾ����������ƴͼ�ɣ�������ͬ��ö�ٷ�ʽ�ᵼ�²�ͬ�Ľ��Ŷ��
����
ÿ�����Ե㣨�����ļ������ҽ���һ��������ݡ�
ÿ��������ݵĵ�һ��Ϊ����������N��M����ʾСHi��СHo�õ������ӵĴ�С��
����100%�����ݣ�����2<=N<=1000, 3<=m<=5��<>
���
���ǵ��ܵķ��������ܷǳ���ֻ��Ҫ�������������1000000007��������
��������
2 4
�������
5
*/
#include<iostream>
#include<vector>
#include<bitset>
#include<cassert>
using namespace std;

int getSum(int n, int m) {
	int bitLength = 1 << (2 * m);
	vector<vector<vector<int> > > dp(n+1, vector<vector<int> >(m+1, vector<int>(bitLength)));
	bitset<10> bitDP;
	int bitInt;
	for (int i = n; i > 0; i--) {
		for (int j = m; j > 0; j--) {
			for (int k = ((bitLength-1)>>(j-1)); k >= 0; k--) {
				bitInt = (k << (j - 1)) | ((1 << (j - 1)) - 1);
				if (i == n && (bitInt >> m) > 0) continue;
				bitDP = bitset<10>(bitInt);
				if (bitDP[j-1] == 1) {
					if (j == m) {
						if (i == n) {
							//dp[n][m][1111] = 1
							dp[i][j][bitInt] = 1;
						}
						else {
							dp[i][j][bitInt] = dp[i + 1][1][bitInt >> m];
						}
					}
					else {
						dp[i][j][bitInt] = dp[i][j + 1][bitInt];
					}
					continue;
				}
				else {
					//bitDP[j] != 1
					if ((i == n || bitDP[j + m - 1] == 1) && (j == m || bitDP[j + 1 - 1] == 1)) {
						dp[i][j][bitInt] = 0;
						continue;
					}
					bitset<10> bit_1 = bitDP;
					bit_1[j-1] = 1; bit_1[j + 1 -1] = 1;
					bitset<10> bit_2 = bitDP;
					bit_2[j - 1] = 1; bit_2[j + m - 1] = 1;
					if (i == n || bitDP[j + m - 1] == 1) {
						dp[i][j][bitInt] = dp[i][j][bit_1.to_ulong()];
						continue;
					}
					if (j == m || bitDP[j + 1 - 1] == 1) {
						dp[i][j][bitInt] = dp[i][j][bit_2.to_ullong()];
						continue;
					}
					dp[i][j][bitInt] = dp[i][j][bit_1.to_ulong()] + dp[i][j][bit_2.to_ullong()];
				}
			}
		}
	}
	return dp[1][1][0];
}
int main(int argv, char* argc[]) {
	int n, m;
	cin >> n >> m;
	cout<<getSum(n, m);
	return 0;
}