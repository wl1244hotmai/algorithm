/*
�������ƣ� I��m stuck!
ʱ�����ƣ� 1.0s
�ڴ����ƣ� 256.0MB
����������
��������
����һ��R��C�еĵ�ͼ����ͼ��ÿһ�����������'#', '+', '-', '|', '.', 'S', 'T'�߸��ַ��е�һ�����ֱ��ʾ������˼��
'#': �κ�ʱ����Ҷ������ƶ����˷���
'+': ����ҵ�����һ�������һ�����������������ĸ��������ڵ�����һ����'#'�����ƶ�һ��
'-': ����ҵ�����һ�������һ�����������������������ڵ�һ����'#'�����ƶ�һ��
'|': ����ҵ�����һ�������һ�����������������������ڵ�һ����'#'�����ƶ�һ��
'.': ����ҵ�����һ�������һ��ֻ�������ƶ�һ������������ڵķ���Ϊ'#'������Ҳ������ƶ���
'S': ��ҵĳ�ʼλ�ã���ͼ��ֻ����һ����ʼλ�á���ҵ�����һ�������һ�����������������ĸ��������ڵ�����һ����'#'�����ƶ�һ��
'T': ��ҵ�Ŀ��λ�ã���ͼ��ֻ����һ��Ŀ��λ�á���ҵ�����һ����󣬿���ѡ���������Ҳ����ѡ�������������ƶ�����������ƶ���һ�����������������ĸ��������ڵ�����һ����'#'�����ƶ�һ��
���⣬��Ҳ����ƶ�����ͼ��
���ҳ����������������ʵķ��������
1. ��ҿ��Դӳ�ʼλ���ƶ����˷���
2. ��Ҳ����ԴӴ˷����ƶ���Ŀ��λ�á�
�����ʽ
����ĵ�һ�а�����������R ��C���ֱ��ʾ��ͼ���к�������(1 �� R, C �� 50)��
��������R��ÿ�ж�����C���ַ������Ǳ�ʾ��ͼ�ĸ��ӡ���ͼ��ǡ����һ��'S'��һ��'T'��
�����ʽ
�������ڳ�ʼλ�þ��Ѿ����ܵ����յ��ˣ��������I'm stuck!��������˫���ţ�������Ļ�������������ʵķ���ĸ�����
��������

5 5
--+-+
..|#.
..|##
S-+-T
####.

�������
2

����˵��
������������ʵķ����ڵ�ͼ����'X'��ǳ����Ļ�����ͼ������ʾ��
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
		isInMap(i, j, rowNum, colNum) // ���ж�Խ��
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
	cin >> R >> C; //(1 �� R, C �� 50)
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