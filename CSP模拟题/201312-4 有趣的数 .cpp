/*问题描述
我们把一个数称为有趣的，当且仅当：
1. 它的数字只包含0, 1, 2, 3，且这四个数字都出现过至少一次。
2. 所有的0都出现在所有的1之前，而所有的2都出现在所有的3之前。
3. 最高位数字不为0。
因此，符合我们定义的最小的有趣的数是2013。除此以外，4位的有趣的数还有两个：2031和2301。
请计算恰好有n位的有趣的数的个数。由于答案可能非常大，只需要输出答案除以1000000007的余数。
输入格式
输入只有一行，包括恰好一个正整数n (4 ≤ n ≤ 1000)。 
输出格式
输出只有一行，包括恰好n 位的整数中有趣的数的个数除以1000000007的余数。 
样例输入
4
样例输出
3
*/
#include<iostream>
#include<vector>
using namespace std;
const long long mod = 1000000007;
/*
首位一定是2，所以2已存在；
其他三个数，8种情况，6种合法：
存在（Y/N)	0	1	3			下一个数-状态
状态0		N   N   N			2-state0,0-state2,3-state1
状态1		N	N	Y			0-state3,3-state1
			N	Y	N 不存在
			N	Y	Y 不存在
状态2		Y	N	N			0-state2,1-state4,2-state2,3-state3
状态3		Y	N	Y			0-state3,1-state5,3-state3
状态4		Y	Y	N			1-state4,2-state4,3-state5
状态5		Y	Y	Y			1-state5,3-state5
*/
int main() {
	int n;
	cin >> n;
	vector<vector<long long>> state(n,vector<long long> (6));	
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			for (int j = 0; j < 6; j++) {
				state[0][j] = 0;
			}
			state[0][0] = 1;
			continue;
		}
		state[i][0] = state[i - 1][0] % mod;
		state[i][1] = (state[i - 1][0] + state[i - 1][1]) %mod;
		state[i][2] = (state[i - 1][0] + state[i - 1][2] * 2) % mod;
		state[i][3] = (state[i - 1][1] + state[i - 1][2] + state[i - 1][3] * 2) % mod;
		state[i][4] = (state[i - 1][2] + state[i - 1][4] * 2) % mod;
		state[i][5] = (state[i - 1][3] + state[i - 1][4] + state[i - 1][5] * 2) % mod;
	}
	cout << state[n - 1][5];
	return 0;
}