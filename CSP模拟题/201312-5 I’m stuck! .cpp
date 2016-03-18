/*
试题名称： I’m stuck!
时间限制： 1.0s
内存限制： 256.0MB
问题描述：
问题描述
给定一个R行C列的地图，地图的每一个方格可能是'#', '+', '-', '|', '.', 'S', 'T'七个字符中的一个，分别表示如下意思：
'#': 任何时候玩家都不能移动到此方格；
'+': 当玩家到达这一方格后，下一步可以向上下左右四个方向相邻的任意一个非'#'方格移动一格；
'-': 当玩家到达这一方格后，下一步可以向左右两个方向相邻的一个非'#'方格移动一格；
'|': 当玩家到达这一方格后，下一步可以向上下两个方向相邻的一个非'#'方格移动一格；
'.': 当玩家到达这一方格后，下一步只能向下移动一格。如果下面相邻的方格为'#'，则玩家不能再移动；
'S': 玩家的初始位置，地图中只会有一个初始位置。玩家到达这一方格后，下一步可以向上下左右四个方向相邻的任意一个非'#'方格移动一格；
'T': 玩家的目标位置，地图中只会有一个目标位置。玩家到达这一方格后，可以选择完成任务，也可以选择不完成任务继续移动。如果继续移动下一步可以向上下左右四个方向相邻的任意一个非'#'方格移动一格。
此外，玩家不能移动出地图。
请找出满足下面两个性质的方格个数：
1. 玩家可以从初始位置移动到此方格；
2. 玩家不可以从此方格移动到目标位置。
输入格式
输入的第一行包括两个整数R 和C，分别表示地图的行和列数。(1 ≤ R, C ≤ 50)。
接下来的R行每行都包含C个字符。它们表示地图的格子。地图上恰好有一个'S'和一个'T'。
输出格式
如果玩家在初始位置就已经不能到达终点了，就输出“I'm stuck!”（不含双引号）。否则的话，输出满足性质的方格的个数。
样例输入

5 5
--+-+
..|#.
..|##
S-+-T
####.

样例输出
2

样例说明
如果把满足性质的方格在地图上用'X'标记出来的话，地图如下所示：
--+-+
..|#X
..|##
S-+-T
####X
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
vector<pair<int, int> > recordPairs;
vector<vector<char> > map;
vector<vector<bool> > isRecorded;

bool isInMap(int i, int j,int rowNum,int colNum) {
	if (i<0 || j<0 || i>=rowNum || j>=colNum)
		return false;
	return true;
}
bool canStepIn(int i, int j, int rowNum, int colNum) {
	return (
		isInMap(i, j, rowNum, colNum) // 先判断越界
		&& map[i][j] != '#'
		&& !isRecorded[i][j]
		);
}
void findTarget(int i, int j, int rowNum, int colNum, bool isSecondSearch ) {
	isRecorded[i][j] = true;
	if (!isSecondSearch) {
		if (map[i][j] != 'T' && map[i][j] != 'S') {
			recordPairs.push_back(make_pair(i, j));
		}
	}
	if (map[i][j] == 'S' || map[i][j] == 'T' || map[i][j] == '+') {
		if (canStepIn(i - 1, j, rowNum, colNum)) {
			findTarget(i - 1, j, rowNum, colNum, isSecondSearch);
		}
		if (canStepIn(i + 1, j, rowNum, colNum)) {
			findTarget(i + 1, j, rowNum, colNum, isSecondSearch);
		}
		if (canStepIn(i, j - 1, rowNum, colNum)) {
			findTarget(i, j - 1, rowNum, colNum, isSecondSearch);
		}
		if (canStepIn(i, j + 1, rowNum, colNum)) {
			findTarget(i, j + 1, rowNum, colNum, isSecondSearch);
		}
		return;
	}

	if (map[i][j] == '-') {
		if (canStepIn(i, j - 1, rowNum, colNum)) {
			findTarget(i, j - 1, rowNum, colNum, isSecondSearch);
		}
		if (canStepIn(i, j + 1, rowNum, colNum)) {
			findTarget(i, j + 1, rowNum, colNum, isSecondSearch);
		}
		return;
	}
	if (map[i][j] == '|') {
		if (canStepIn(i - 1, j, rowNum, colNum)) {
			findTarget(i - 1, j, rowNum, colNum, isSecondSearch);
		}
		if (canStepIn(i + 1, j, rowNum, colNum)) {
			findTarget(i + 1, j, rowNum, colNum, isSecondSearch);
		}
		return;
	}	
	if (map[i][j] == '.') {
		if (canStepIn(i + 1, j, rowNum, colNum)) {
			findTarget(i + 1, j, rowNum, colNum, isSecondSearch);
		}
		return;
	}
	return;
}

int main() {
	int R, C;
	cin >> R >> C; //(1 ≤ R, C ≤ 50)
	int Si, Sj, Ti, Tj;
	map = vector<vector<char> > (R, vector<char>(C));
	isRecorded = vector<vector<bool> > (R, vector<bool>(C));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'S') {
				Si = i;
				Sj = j;
			}
			if (map[i][j] == 'T') {
				Ti = i;
				Tj = j;
			}
		}
	}
	int rowNum = map.size();
	int colNum = map[0].size();
	findTarget(Si, Sj, rowNum, colNum, false);
	if (isRecorded[Ti][Tj]) {
		int my_count = 0;
		for (vector<pair<int, int> >::iterator itor = recordPairs.begin();
		itor < recordPairs.end(); itor++) {
			isRecorded = vector<vector<bool> >(R, vector<bool>(C));
			findTarget((*itor).first, (*itor).second, rowNum, colNum, true);
			if (isRecorded[Ti][Tj] == false)
				my_count++;
		}
		cout << my_count;
	}
	else {
		cout << "I'm stuck";
	}
	return 0;
}