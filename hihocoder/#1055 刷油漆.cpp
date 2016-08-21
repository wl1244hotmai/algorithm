#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct stick {
	int value;
	stick* parent;
	vector<stick*> children;
	int number;
	int nodesNum;
};

class Painting {
private:
	int N, M;
	vector<stick> vi;
	vector<vector<int> > dp;

	void init() {
		cin >> N >> M;
		vi.assign(N + 1, stick());
		for (int i = 1; i <= N; i++) {
			cin >> vi[i].value;
			vi[i].number = i;
		}
		int p, c;
		for (int i = 0; i < N-1; i++) {
			cin >> p >> c;
			vi[p].children.push_back(&vi[c]);
			vi[c].parent = &vi[p];
		}
	}
	int countChildrenNum(stick& u) {
		u.nodesNum = 1;
		for_each(u.children.begin(), u.children.end(), [&](stick* v) {
			u.nodesNum += countChildrenNum(*v);
		});
		return u.nodesNum;
	}

public:
	Painting() {
		init();
		countChildrenNum(vi[1]);
	}

	void dfs(stick& u) {
		/**
		* 核心在于i从M开始向后求。
		* 最优结构：dp[u][i] = max(dp[u][i], dp[u][i - j] + dp[v][j]);
		* 则计算顺序可以认为是 (假设 u = 4, v = 6, M = 4):
		* dp[4][4] ( dp[4][3] + dp[6][1] )
		* dp[4][4] ( dp[4][2] + dp[6][2] )
		* dp[4][4] ( dp[4][1] + dp[6][3] )
		* 这三步中，前两步的dp[4][3] dp[4][2]都是在没有包含v节点的情况。
		* 比如 4
		*      |\
		*      6 7
		*      |
		*      8
		* 当中，计算6节点的时候,dp[4][3],dp[4][2]都是0，这样就避免了dp[4][3]中包含v所在的节点而重复的问题。
		*/
		int i = u.number;
		dp[i][1] = u.value;
		for_each(u.children.begin(), u.children.end(), [&](stick* v) {
			dfs(*v);
			for (int m = min(M, u.nodesNum); m >= 2; m--) {
				for (int j = 1; j < m; j++) {
					dp[i][m] = max(dp[i][m], dp[i][m - j] + dp[v->number][j]);
				}
			}
		});
	}

	int solve() {
		dp.assign(N + 1, vector<int>(N + 1));
		//后序遍历 + 从大到小访问
		dfs(vi[1]);
		return dp[1][M];
	}

};

int main(int argv, char* argc[]) {
	Painting painting;
	cout << painting.solve();
	return 0;
}