#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<fstream>

using namespace std;
const int downDir = 1;
const int rightDir = 0;
int minChanged(vector<string> maze) {
	vector<vector<vector<int> > > dp(maze.size(),
		vector<vector<int> >(maze[0].size(),vector<int>(2)));
	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[i].size(); j++) {
			if (i == 0) {
				if (j == 0) {
					dp[i][j][rightDir] = maze[i][j] == 'b';
					dp[i][j][downDir] = (j<maze[0].size() - 1 && maze[i][j + 1] != 'b') + (maze[i][j] == 'b');
					continue;
				}
				dp[i][j][rightDir] = dp[i][j - 1][rightDir] + (maze[i][j] == 'b');
				dp[i][j][downDir] = dp[i][j - 1][rightDir] + (j<maze[0].size() - 1 && maze[i][j + 1] != 'b') + (maze[i][j] == 'b');
				continue;
			}
			if (j == 0) {
				dp[i][j][rightDir] = dp[i - 1][j][downDir] + (i < maze.size() - 1 && maze[i + 1][j] != 'b') + (maze[i][j] == 'b');
				dp[i][j][downDir] = dp[i - 1][j][downDir] + (maze[i][j] =='b');
				continue;
			}
			dp[i][j][rightDir] = min(dp[i][j - 1][rightDir], dp[i - 1][j][downDir] + (i < maze.size() - 1 && maze[i + 1][j] != 'b')) + (maze[i][j] == 'b');
			dp[i][j][downDir] = min(dp[i - 1][j][downDir], dp[i][j - 1][rightDir] + (j < maze[0].size() - 1 && maze[i][j + 1] != 'b')) + (maze[i][j] == 'b');

		}
	}
	return min(dp[maze.size() - 1][maze[0].size() - 1][rightDir],dp[maze.size()-1][maze[0].size()-1][downDir]);

}
int main(int argv, char* argc[]) {
	
	int N, M;
	cin >> N >> M;
	vector<string> maze(N, string(M,' '));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> maze[i][j];
		}
	}
	cout << minChanged(maze);
	return 0;
}