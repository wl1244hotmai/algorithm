// ʱ������:10000ms
// ����ʱ��:1000ms
// �ڴ�����:256MB

// ����
// ����������ȣ�СHo����լ�ڼ���������������Ե�һ�Ҳ͹�һ����N����Ʒ���۸�ֱ���A1, A2, ... ANԪ��������������ܼ���XԪ�����������Żݡ�СHo��һ����޶��ë�����˹�����ˣ���ϣ��ѡ�����ɵ���ͬ�Ĳ�Ʒ��ʹ���ܼ��ڲ�����XԪ��ͬʱ�����͡�
// ���������һ��СHo�������Ѷ���Ԫ��
// ����
// ��һ�а�����������N��X��(1 <= N <= 20, 1 <= X <= 100)
// �ڶ��а���N������A1, A2, ...�� AN��(1 <= Ai <= 100)
// ���
// ������ٵ����ѡ����СHo��N���˶����˻����ܴﵽXԪ���Żݱ�׼�����-1��
// ��������
// 10 50
// 9 9 9 9 9 9 9 9 9 8
// �������
// 53

#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxInt = 2147483647;

void solution_1(){
	int N, X;
	cin >> N >> X;
	vector<int> foods(N + 1, 0);
	for (int i = 1; i <= N; i++) {
		cin >> foods[i];
	}
	vector<vector<int> > best(N+1,vector<int>(X+1, maxInt));
	int sum = 0;
	for (int i = 1; i <= N; i++) {
		sum += foods[i];
		for (int j = 1; j <= X; j++) {
			if (j > sum) {
				break;
			}
			if (j <= foods[i]) {
				best[i][j] = min(best[i - 1][j], foods[i]);
			}
			else if (best[i - 1][j] == maxInt) {
				best[i][j] = best[i - 1][j - foods[i]] + foods[i];
			}	
			else {
				best[i][j] = min(best[i - 1][j], best[i - 1][j - foods[i]] + foods[i]);
			}
		}
	}
	if (best[N][X] == maxInt)
		cout << -1;
	else
		cout << best[N][X]<<endl;
	return;
}