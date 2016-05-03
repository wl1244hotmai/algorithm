/**
#1048 : 状态压缩·二

时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
历经千辛万苦，小Hi和小Ho终于到达了举办美食节的城市！虽然人山人海，但小Hi和小Ho仍然抑制不住兴奋之情，他们放下行李便投入到了美食节的活动当中。美食节的各个摊位上各自有着非常多的有意思的小游戏，其中一个便是这样子的：
小Hi和小Ho领到了一个大小为N*M的长方形盘子，他们可以用这个盒子来装一些大小为2*1的蛋糕。但是根据要求，他们一定要将这个盘子装的满满的，一点缝隙也不能留下来，才能够将这些蛋糕带走。
这么简单的问题自然难不倒小Hi和小Ho，于是他们很快的就拿着蛋糕离开了~
但小Ho却不只满足于此，于是他提出了一个问题——他们有多少种方案来装满这个N*M的盘子呢？
值得注意的是，这个长方形盘子的上下左右是有区别的，如在N=4, M=3的时候，下面的两种方案被视为不同的两种方案哦！
提示：我们来玩拼图吧！不过不同的枚举方式会导致不同的结果哦！
输入
每个测试点（输入文件）有且仅有一组测试数据。
每组测试数据的第一行为两个正整数N、M，表示小Hi和小Ho拿到的盘子的大小。
对于100%的数据，满足2<=N<=1000, 3<=m<=5。<>
输出
考虑到总的方案数可能非常大，只需要输出方案数除以1000000007的余数。
样例输入
2 4
样例输出
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