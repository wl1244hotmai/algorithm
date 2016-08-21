#include<iostream>
#include<algorithm>
#include<iomanip>
#define loop(N) for(int i=0;i<N;i++)
using namespace std;

class Kuhn_Munkres_solution_match{
public:
	struct KM_MATCH {
		int n;
		int **edge; //边的权值
		bool **sub_map; //相等子图
		bool *x_onPath; //在一次增广路径寻找中，xi是否已经在增广路径上
		bool *y_onPath; //在一次增广路径寻找中，yj是否已经在增广路径上
		int *path; //配对
		KM_MATCH(int N) {
			this->n = N;
			edge = new int*[N];
			loop(N) {
				edge[i] = new int[N];
				memset(edge[i], -1, sizeof(int)*N);
			}
			sub_map = new bool*[N];
			loop(N) {
				sub_map[i] = new bool[N];
				memset(sub_map[i], false, sizeof(bool)*N);
			}
			x_onPath = new bool[N];
			y_onPath = new bool[N];
			path = new int[N];
			memset(x_onPath, 0, sizeof(bool)*N);
			memset(y_onPath, 0, sizeof(bool)*N);
			memset(path, -1, sizeof(int)*N);
		}
		void resetPath() {
			memset(path, -1, sizeof(int)*n);
		}
		void clearOnPathSign() {
			memset(x_onPath, 0, sizeof(bool)*n);
			memset(y_onPath, 0, sizeof(bool)*n);
		}
		~KM_MATCH() {
			loop(n) {
				delete[]edge[i];
				delete[]sub_map[i];
			}
			delete[]edge;
			delete[]sub_map;
			delete[]x_onPath;
			delete[]y_onPath;
			delete[]path;
		}
	};

	bool findAugmentPath(KM_MATCH* pMatch, int xi) {
		pMatch->x_onPath[xi] = true;
		for (int yj = 0; yj < pMatch->n; yj++) {
			if (pMatch->sub_map[xi][yj] && !pMatch->y_onPath[yj]) {
				pMatch->y_onPath[yj] = true;
				if (pMatch->path[yj] == -1 || findAugmentPath(pMatch, pMatch->path[yj])) {
					pMatch->path[yj] = xi;
					return true;
				}
			}
		}
		return false;
	}

	bool Kuhn_Munkres_Match(KM_MATCH* pMatch) {
		int N = pMatch->n;
		int *A = new int[N];
		int *B = new int[N];

		//初始化A、B标点
		for (int i = 0; i < N; i++) {
			B[i] = 0;
			A[i] = INT32_MIN;
			for (int j = 0; j < N; j++) {
				A[i] = max(A[i], pMatch->edge[i][j]);
			}
		}

		while (true) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					pMatch->sub_map[i][j] = pMatch->edge[i][j] == (A[i] + B[j]);
				}
			}
			pMatch->resetPath();
			int match = 0;
			for (int xi = 0; xi < N; xi++) {
				pMatch->clearOnPathSign();
				if (findAugmentPath(pMatch, xi))
					match++;
				else {
					pMatch->x_onPath[xi] = true;
					break;
				}
			}
			if (match == N) {
				delete[]A;
				delete[]B;
				return true;
			}
			int dx = INT32_MAX;
			for (int i = 0; i<N; i++) {
				if (pMatch->x_onPath[i]) {
					for (int j = 0; j < N; j++) {
						if (!pMatch->y_onPath[j]) {
							dx = min(dx, (A[i] + B[j]) - pMatch->edge[i][j]);
						}
					}
				}
			}
			for (int i = 0; i < N; i++) {
				if (pMatch->x_onPath[i])
					A[i] -= dx;
				if (pMatch->y_onPath[i])
					B[i] += dx;
			}
		}

		delete[]A;
		delete[]B;
		return false;

	}
	void func() {
		int N;
		cin >> N;
		KM_MATCH km_match(N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> km_match.edge[i][j];
			}
		}
		Kuhn_Munkres_Match(&km_match);
		int *path = new int[N];
		loop(N) {
			path[km_match.path[i]] = i;
		}
		loop(N) {
			cout << i << setw(6) << path[i] << endl;
		}
		delete[]path;
		return;
	}
};