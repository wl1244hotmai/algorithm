// 时间限制:11000ms
// 单点时限:1000ms
// 内存限制:256MB

// 描述
// 如下图所示，某市市区由M条南北向的大街和N条东西向的道路组成。其中由北向南第i条路和第i+1条路之间的距离是Bi (1 <= i < N)，由西向东第i条街和第i+1条街之间的距离是Ai (1 <= i < M)。

// 小Ho现在位于第x条路和第y条街的交叉口，他的目的地是第p条路和第q条街的交叉口。由于连日降雨，城市中有K个交叉口积水太深不能通行。小Ho想知道到达目的地的最短路径的长度是多少。
// 输入
// 第一行包含两个整数N和M。(1 <= N, M <= 500) ?
// 第二行包含N-1个整数, B1, B2, B3, ... BN-1。(1 <= Bi <= 100) ?
// 第三行包含M-1个整数, A1, A2, A3, ... AM-1。(1 <= Ai <= 100) ?
// 第四行包含一个整数K，表示积水的交叉口的数目。 (0 <= K <= 30) ?
// 以下K行每行包含2个整数，X和Y，表示第X条路和第Y条街的交叉口积水。(1 <= X <= N, 1 <= Y <= M) ?
// 第K+5行包含一个整数Q，表示询问的数目。 (1 <= Q <= 10) ?
// 以下Q行每行包含4个整数x, y, p, q，表示小Ho的起止点。起止点保证不在积水的交叉口处。 ?(1 <= x, p <= N, 1 <= y, q <= M)
// 输出
// 对于每组询问，输出最短路的长度。如果小Ho不能到达目的地，输出-1。
// 样例输入
// 4 5  
// 2 4 1  
// 3 3 3 2  
// 3  
// 1 3  
// 2 3  
// 3 2  
// 1  
// 1 2 2 4  
// 样例输出
// 24

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<limits.h>
using namespace std;
int N, M;
vector<int> Broad;
vector<int> Aroad;
void solve(vector<vector<int> > &points,
	const vector<vector<bool> > &blocked,
	vector<vector<bool> > &visited,
	int x_s, int y_s, int p, int q) {
	points[x_s][y_s] = 0;
	queue<pair<int, int> > pQueue;
	pQueue.push({ x_s,y_s });
	int i, j,
		x, y;
	while (!pQueue.empty()) {
		pair<int, int> cur = pQueue.front();
		pQueue.pop();
		i = cur.first;
		j = cur.second;
		visited[i][j] = true;
		x = i - 1;
		y = j;
		if (x >= 0 && !blocked[x][y] && !visited[x][y]) {
			if (points[x][y] > points[i][j] + Broad[i - 1]) {
				//贪婪思想，从[x][y]出发，如果cost更大，根本没必要push。
				//因为如果走cost更大的方案，从xy出去的方案也会cost更大。
				//参照图的最短路径，这里只要push cost更小的方案
				points[x][y] = points[i][j] + Broad[i - 1];
				if (x != p || y != q)
					pQueue.push({ x,y });
			}
		}
		x = i + 1;
		y = j;
		if (x < N && !blocked[x][y] && !visited[x][y]) {
			if (points[x][y]>points[i][j] + Broad[i]) {
				points[x][y] = points[i][j] + Broad[i];
				if (x != p || y != q)
					pQueue.push({ x,y });
			}
		}
		x = i;
		y = j - 1;
		if (y >= 0 && !blocked[x][y]&& !visited[x][y]) {
			if (points[x][y] > points[i][j] + Aroad[j - 1]) {
				points[x][y] = points[i][j] + Aroad[j - 1];
				if (x != p || y != q)
					pQueue.push({ x,y });
			}
		}
		x = i;
		y = j + 1;
		if (y < M && !blocked[x][y] && !visited[x][y]) {
			if (points[x][y] > points[i][j] + Aroad[j]) {
				points[x][y] = points[i][j] + Aroad[j];
				if (x != p || y != q)
					pQueue.push({ x,y });
			}
		}
	}
}

void solution_2() {

	cin >> N >> M;
	vector<vector<int> > points(N, vector<int>(M, 0));
	vector<vector<bool> > blocked(N, vector<bool>(M, false));
	vector<vector<bool> > visited(N, vector<bool>(M, false));
	// i,j所在的点，
	// left cost: Aroad[j-1]
	// right cost: Aroad[j]
	// up cost: Broad[i-1]
	// down cost: Broad[j]
	Broad.assign(N - 1, 0);
	for (int i = 0; i < N - 1; i++) {
		cin >> Broad[i];
	}
	Aroad.assign(M - 1, 0);
	for (int i = 0; i < M - 1; i++) {
		cin >> Aroad[i];
	}
	int K;
	cin >> K;
	for (int i = 0; i < K; i++) {
		int X, Y;
		cin >> X >> Y;
		blocked[X - 1][Y - 1] = true;
	}
	int Q;
	cin >> Q;
	for (int i = 0; i < Q; i++) {
		points.assign(N, vector<int>(M, INT_MAX));
		visited.assign(N, vector<bool>(M, false));
		int x, y, p, q;
		cin >> x >> y >> p >> q;
		solve(points, blocked, visited, x - 1, y - 1, p - 1, q - 1);
		if (points[p - 1][q - 1] == INT_MAX)
			cout << -1 << endl;
		else
			cout << points[p - 1][q - 1] << endl;
	}
	return;
}