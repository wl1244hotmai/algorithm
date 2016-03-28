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
	vector<vector<int> >minSNum(mQuestion.N+1, vector<int>(mQuestion.M + 1,2000));
	int leastNum;
	minSNum[0] = vector<int>(mQuestion.M + 1, 0);
	for (int i = 1; i <= mQuestion.N; i++) {
		for (int j = mQuestion.M; j >= 0; --j) {
			/*
			三种情况,
			j<leastNum<jostNum;
			leastNum<=j<mostNum;
			j>=mostNum;
			*/
			leastNum = (int)ceil((double)tempPoints[i-1] / (double)mQuestion.S);
			//mostNum = ceil((double)tempPoints[i] / (double)mQuestion.T);
			if (leastNum > j) {
				//minSNum[i][j] = 2000; //2000 means "No"
				break;
			}
			if (i == mQuestion.N && j != mQuestion.M) break;
			int leastTNum;
			minSNum[i][j] = 2000;
			for (int sNum = leastNum; sNum >= 0; sNum--) {
				leastTNum = (int)ceil((double)(tempPoints[i-1] - sNum*mQuestion.S) / (double)mQuestion.T);
				leastTNum = leastTNum <= 0 ? 0 : leastTNum;
				if (leastTNum + sNum > j) break;
				if (minSNum[i - 1][j - sNum - leastTNum] == 2000) break;
				minSNum[i][j] = min(minSNum[i][j], sNum + minSNum[i-1][j-sNum- leastTNum]);
			}
		}
	}
	return minSNum[mQuestion.N][mQuestion.M];
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