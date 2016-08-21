#include<iostream>
#include<vector>

using namespace std;

class solution_Matrix_Chain {
	
public:

	void MatrixChain_LeastComputeCount(int N,
		vector<int>& p,
		vector<vector<int> >& m,
		vector<vector<int> >& s) {

		for (int i = 0; i < N; i++) {
			m[i][i] = 0;
		}
		for (int r = 2; r <= N; r++) {

			for (int i = 0; i <= N - r; i++) {
				int j = i + r - 1;
				m[i][j] = INT_MAX;
				for (int k = i; k < j; k++) {
					int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
					if (q < m[i][j]) {
						m[i][j] = q;
						s[i][j] = k;
					}
				}
			}
		}
	}
	void display_parens(vector<vector<int> >&s, int i, int j) {
		if (i == j) cout << "A" << i;
		else
		{
			cout << "(";
			display_parens(s, i, s[i][j]);
			display_parens(s, s[i][j] + 1, j);
			cout << ")";
		}
	}
	void func() {
		int N;
		cin >> N;
		vector<int> matrix(N + 1);
		for (int i = 0; i < N + 1; i++) {
			cin >> matrix[i];
		}
		vector<vector<int> > m(N, vector<int>(N));
		vector<vector<int> > s(N, vector<int>(N));
		MatrixChain_LeastComputeCount(N, matrix, m, s);
		cout << m[0][N - 1] << endl;
		display_parens(s, 0 ,N-1);
	}
};