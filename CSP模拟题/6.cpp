///**
//����������
//�� N �������Ҹ�����ͬ�������������һ����������������ж��ٶ��෴��(a �� - a Ϊһ���෴��)��
//�����ʽ
//��һ�а���һ�������� N��(1 �� N �� 500)��
//�ڶ���Ϊ N ���õ����ո�����ķ�������, ÿ�����ľ���ֵ������1000, ��֤��Щ����������ͬ��
//�����ʽ
//ֻ���һ������, ���� N �����а������ٶ��෴����
//��������
//5
//1 2 3 - 1 - 2
//�������
//2
//*/
//
//#include<iostream>
//#include<vector>
//using namespace std;
//int calDiverseNum(vector<int> input, vector<int> num) {
//	int count = 0;
//	int tmp = 0;
//	for (vector<int>::iterator itor = input.begin(); itor < input.end(); itor++) {
//		if (*itor > 0) {
//			tmp = *itor;
//		}
//		else{
//			tmp = -*itor;
//		}
//		num[tmp]++;
//		if (num[tmp] == 2) {
//			count++;
//		}
//	}
//	return count;
//}
//int main(int argv, char* argc[]) {
//	int N;
//	cin >> N;
//	vector<int> input(N,0);
//	vector<int> num(1000, 0);
//	for (int i = 0; i < N; i++) {
//		cin >> input[i];
//	}
//	cout << calDiverseNum(input,num);
//	return 0;
//}