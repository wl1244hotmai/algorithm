#include <iostream>
using namespace std;

struct node {
	long long n, s;
};
node dp[19][20][201];
int bit[19];
long long base[19];
const long long mod = 1e9 + 7;
long long l, r, k;

node dfs(int len, int dig, bool begin_zero, bool end_flag, int sum) {
	node t;
	t.s = 0, t.n = 0;
	if (len <= 0 || len > 19 || dig > 9  || k <-100 || k > 100) return t;
	if (!end_flag && dp[len][dig + (begin_zero ? 0 : 10)][sum + 100].n != -1)
		return dp[len][dig + (begin_zero ? 0 : 10)][sum + 100];
	//一位数的情况
	if (len == 1) {
		if (dig != sum) {
			return t;
		}
		t.s = dig;
		t.n = 1;
		return t;
	}

	int end = end_flag ? bit[len - 2] : 9;
	node tmp;
	for (int i = 0; i <= end; i++) {
		int new_sum = dig - sum;
		if (!begin_zero) {
			tmp = dfs(len - 1, i, i != 0, end_flag && (i == end), sum);
		}
		else {
			tmp = dfs(len - 1, i, true, end_flag && (i == end), new_sum);
		}
		t.n += tmp.n;
		t.s = ((t.s + tmp.s) % mod + ((tmp.n * dig) % mod * base[len]) % mod) % mod;
	}

	if (!end_flag) {
		dp[len][dig + (begin_zero ? 0 : 10)][sum + 100] = t;
	}
	return t;

}

int solve(long long number, int sum) {
	if (number <= 0)
		return 0;
	int cnt = 0;
	while (number) {
		bit[cnt++] = number % 10;
		number /= 10;
	}
	return dfs(cnt + 1, 0, false, true, sum).s;
}

int main(int argv, char argc) {
	base[1] = 1;
	for (int i = 2; i <= 19; i++) {
		base[i] = (base[i - 1] * 10) % mod;//10的N次方数据保存
	}
	node t;
	t.n = -1;
	t.s = 0;
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 20; j++)
			for (int k = 0; k < 201; k++)
				dp[i][j][k] = t;
	cin >> l >> r >> k;
	cout << (solve(r, k) - solve(l - 1, k) + mod) % mod;
	return 0;
}