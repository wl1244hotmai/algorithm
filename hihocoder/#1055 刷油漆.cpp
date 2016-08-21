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
		* ��������i��M��ʼ�����
		* ���Žṹ��dp[u][i] = max(dp[u][i], dp[u][i - j] + dp[v][j]);
		* �����˳�������Ϊ�� (���� u = 4, v = 6, M = 4):
		* dp[4][4] ( dp[4][3] + dp[6][1] )
		* dp[4][4] ( dp[4][2] + dp[6][2] )
		* dp[4][4] ( dp[4][1] + dp[6][3] )
		* �������У�ǰ������dp[4][3] dp[4][2]������û�а���v�ڵ�������
		* ���� 4
		*      |\
		*      6 7
		*      |
		*      8
		* ���У�����6�ڵ��ʱ��,dp[4][3],dp[4][2]����0�������ͱ�����dp[4][3]�а���v���ڵĽڵ���ظ������⡣
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
		//������� + �Ӵ�С����
		dfs(vi[1]);
		return dp[1][M];
	}

};

int main(int argv, char* argc[]) {
	Painting painting;
	cout << painting.solve();
	return 0;
}