/*
ʱ������:5000ms
����ʱ��:1000ms
�ڴ�����:256MB
����
СHi��СHo���б�СHiǿ������СZ��׼����Ӳμ�һ�������������������ù����ƣ�����N���ؿ����ڵ�i���ؿ��У�СHi������Ҫ���Ai��������ܹ�������һ�ء�ÿһ�صķ������Ƕ�������ģ���ʹ��һ�ص��л�ó�����Ҫ�ķ�����Ҳ����Ժ���Ĺؿ�����Ӱ�졣
СHi���ǿ���ͨ�������÷��������һ������S����������һ������T������������е�N���ؿ��У�СHi����һ����M�δ�����ᡣ��ÿ���ؿ��У����������ۼƴ������������M�������ʹ������εĴ�����ᡣ
��ô�����������ˣ����ڸ�����N��M��S��T��A��СHi����������Ҫ��Զ��ٵ���Ŀ���ܹ�������еĹؿ��أ�
����
ÿ�������ļ���������������ݣ���ÿ�������ļ��ĵ�һ��Ϊһ������Q����ʾ�������ݵ�������
ÿ��������ݵĵ�һ��Ϊ�ĸ�������N��M��S��T��������ǰ��������
�ڶ���ΪN�����������ֱ��ʾA1~AN��
����40%�����ݣ�����1<=N,M<=100
����100%�����ݣ�����1<=N,M<=1000,1<=T<S<=10,1<=Ai<=50
����100%�����ݣ�����1<=Q<=100
���
����ÿ��������ݣ����СHi�����ܹ�˳����ɹؿ��������һ������Ans����ʾСHi����������Ҫ��Ե���Ŀ�������������No��
��������
1
2 10 9 1
12 35 
�������
5
*/
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
struct question {
	int N, M, S, T;
	vector<int> points;
};
int processData(question mQuestion) {
	vector<int> tempPoints = mQuestion.points;
	vector<int>minSNum(mQuestion.M + 1, 2000);
	//if minSNum[i][j] == 2000, it means "No";
	int leastNum;
	for (int i = 1; i <= mQuestion.N; i++) {
		for (int j = mQuestion.M; j >= 0; --j) {
			/*
			�������,
			j<leastNum<jostNum;
			leastNum<=j<mostNum;
			j>=mostNum;
			*/
			leastNum = (int)ceil((double)tempPoints[i - 1] / (double)mQuestion.S);
			//mostNum = ceil((double)tempPoints[i] / (double)mQuestion.T);
			minSNum[j] = 2000;
			if (leastNum > j) {
				//ʣ����Ŀ�����������ʱ���jѭ��������
				continue;
			}
			if (i == mQuestion.N && j != mQuestion.M) break; //���һ��ѭ��ֻ���� j = M;
			int leastTNum;
			for (int sNum = leastNum; sNum >= 0; sNum--) {
				leastTNum = (int)ceil((double)(tempPoints[i - 1] - sNum*mQuestion.S) / (double)mQuestion.T);
				leastTNum = leastTNum <= 0 ? 0 : leastTNum;
				if (leastTNum + sNum > j) break; //��������������Ŀ��������M��ѭ������;
				//��minSNum[i - 1][j - sNum - leastTNum] == 2000��˵�����sNum�����߲�ͨ��
				if (i!=1 && minSNum[j - sNum - leastTNum] == 2000) break;
				//����minSNum[i][j]�����minSNum[i][j]==2000��˵����ʱΪNo;
				if (i == 1) {
					minSNum[j] = min(minSNum[j], sNum);
				}
				minSNum[j] = min(minSNum[j], sNum + minSNum[j - sNum - leastTNum]);
			}
		}
	}
	return minSNum[mQuestion.M];
}

int main(int argv, char *argc[]) {
	int Q;
	int temp;
	cin >> Q;
	vector<question> mQuestions(Q);
	for (int i = 0; i<Q; i++) {
		cin >> mQuestions[i].N >> mQuestions[i].M >> mQuestions[i].S >> mQuestions[i].T;
		for (int j = 0; j<mQuestions[i].N; j++) {
			cin >> temp;
			mQuestions[i].points.push_back(temp);
		}
		int res = processData(mQuestions[i]);
		if (res >= 2000 || res == -1) {
			cout << "No" << endl;
		}
		else {
			cout << res << endl;
		}
	}

	return 0;
}
