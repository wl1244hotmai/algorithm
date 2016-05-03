#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int getBest(int N, int M, vector<int> need, vector<int> value, vector<int> best) {
	for (int i = 1; i <= N; i++) {
		for (int j = need[i]; j <= M ; j++) {
			best[j] = max(best[j], best[j - need[i]] + value[i]);
		}
	}
	return best[M];
}
int main(int argv, char* argc[]) {
	int N, M;
	cin >> N >> M;
	vector<int> need(N + 1, 0);
	vector<int> value(N + 1, 0);
	vector<int> best(M + 1, 0);
	for (int i = 1; i <= N; ++i) {
		cin >> need[i] >> value[i];
	}
	cout << getBest(N, M, need, value, best);
	return 0;
}