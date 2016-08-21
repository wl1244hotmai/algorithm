// ʱ������:11000ms
// ����ʱ��:1000ms
// �ڴ�����:256MB

// ����
// ����ͼ��ʾ��ĳ��������M���ϱ���Ĵ�ֺ�N��������ĵ�·��ɡ������ɱ����ϵ�i��·�͵�i+1��·֮��ľ�����Bi (1 <= i < N)�������򶫵�i���ֺ͵�i+1����֮��ľ�����Ai (1 <= i < M)��

// СHo����λ�ڵ�x��·�͵�y���ֵĽ���ڣ�����Ŀ�ĵ��ǵ�p��·�͵�q���ֵĽ���ڡ��������ս��꣬��������K������ڻ�ˮ̫���ͨ�С�СHo��֪������Ŀ�ĵص����·���ĳ����Ƕ��١�
// ����
// ��һ�а�����������N��M��(1 <= N, M <= 500) ?
// �ڶ��а���N-1������, B1, B2, B3, ... BN-1��(1 <= Bi <= 100) ?
// �����а���M-1������, A1, A2, A3, ... AM-1��(1 <= Ai <= 100) ?
// �����а���һ������K����ʾ��ˮ�Ľ���ڵ���Ŀ�� (0 <= K <= 30) ?
// ����K��ÿ�а���2��������X��Y����ʾ��X��·�͵�Y���ֵĽ���ڻ�ˮ��(1 <= X <= N, 1 <= Y <= M) ?
// ��K+5�а���һ������Q����ʾѯ�ʵ���Ŀ�� (1 <= Q <= 10) ?
// ����Q��ÿ�а���4������x, y, p, q����ʾСHo����ֹ�㡣��ֹ�㱣֤���ڻ�ˮ�Ľ���ڴ��� ?(1 <= x, p <= N, 1 <= y, q <= M)
// ���
// ����ÿ��ѯ�ʣ�������·�ĳ��ȡ����СHo���ܵ���Ŀ�ĵأ����-1��
// ��������
// 4 5  
// 2 4 1  
// 3 3 3 2  
// 3  
// 1 3  
// 2 3  
// 3 2  
// 1  
// 1 2 2 4  
// �������
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
				//̰��˼�룬��[x][y]���������cost���󣬸���û��Ҫpush��
				//��Ϊ�����cost����ķ�������xy��ȥ�ķ���Ҳ��cost����
				//����ͼ�����·��������ֻҪpush cost��С�ķ���
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
	// i,j���ڵĵ㣬
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