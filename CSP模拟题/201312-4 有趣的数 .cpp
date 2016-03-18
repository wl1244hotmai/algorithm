/*��������
���ǰ�һ������Ϊ��Ȥ�ģ����ҽ�����
1. ��������ֻ����0, 1, 2, 3�������ĸ����ֶ����ֹ�����һ�Ρ�
2. ���е�0�����������е�1֮ǰ�������е�2�����������е�3֮ǰ��
3. ���λ���ֲ�Ϊ0��
��ˣ��������Ƕ������С����Ȥ������2013���������⣬4λ����Ȥ��������������2031��2301��
�����ǡ����nλ����Ȥ�����ĸ��������ڴ𰸿��ܷǳ���ֻ��Ҫ����𰸳���1000000007��������
�����ʽ
����ֻ��һ�У�����ǡ��һ��������n (4 �� n �� 1000)�� 
�����ʽ
���ֻ��һ�У�����ǡ��n λ����������Ȥ�����ĸ�������1000000007�������� 
��������
4
�������
3
*/
#include<iostream>
#include<vector>
using namespace std;
const long long mod = 1000000007;
/*
��λһ����2������2�Ѵ��ڣ�
������������8�������6�ֺϷ���
���ڣ�Y/N)	0	1	3			��һ����-״̬
״̬0		N   N   N			2-state0,0-state2,3-state1
״̬1		N	N	Y			0-state3,3-state1
			N	Y	N ������
			N	Y	Y ������
״̬2		Y	N	N			0-state2,1-state4,2-state2,3-state3
״̬3		Y	N	Y			0-state3,1-state5,3-state3
״̬4		Y	Y	N			1-state4,2-state4,3-state5
״̬5		Y	Y	Y			1-state5,3-state5
*/
int main() {
	int n;
	cin >> n;
	vector<vector<long long>> state(n,vector<long long> (6));	
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			for (int j = 0; j < 6; j++) {
				state[0][j] = 0;
			}
			state[0][0] = 1;
			continue;
		}
		state[i][0] = state[i - 1][0] % mod;
		state[i][1] = (state[i - 1][0] + state[i - 1][1]) %mod;
		state[i][2] = (state[i - 1][0] + state[i - 1][2] * 2) % mod;
		state[i][3] = (state[i - 1][1] + state[i - 1][2] + state[i - 1][3] * 2) % mod;
		state[i][4] = (state[i - 1][2] + state[i - 1][4] * 2) % mod;
		state[i][5] = (state[i - 1][3] + state[i - 1][4] + state[i - 1][5] * 2) % mod;
	}
	cout << state[n - 1][5];
	return 0;
}