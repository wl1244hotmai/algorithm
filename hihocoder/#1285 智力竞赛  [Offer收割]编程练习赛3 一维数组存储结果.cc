/*
时间限制:5000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi、小Ho还有被小Hi强拉来的小Z，准备组队参加一个智力竞赛。竞赛采用过关制，共计N个关卡。在第i个关卡中，小Hi他们需要获得Ai点分数才能够进入下一关。每一关的分数都是独立计算的，即使在一关当中获得超过需要的分数，也不会对后面的关卡产生影响。
小Hi他们可以通过答题获得分数。答对一道题获得S点分数，答错一道题获得T点分数。在所有的N个关卡中，小Hi他们一共有M次答题机会。在每个关卡中，都可以在累计答题次数不超过M的情况下使用任意次的答题机会。
那么现在问题来了，对于给定的N、M、S、T和A，小Hi他们至少需要答对多少道题目才能够完成所有的关卡呢？
输入
每个输入文件包含多组测试数据，在每个输入文件的第一行为一个整数Q，表示测试数据的组数。
每组测试数据的第一行为四个正整数N、M、S和T，意义如前文所述。
第二行为N个正整数，分别表示A1~AN。
对于40%的数据，满足1<=N,M<=100
对于100%的数据，满足1<=N,M<=1000,1<=T<S<=10,1<=Ai<=50
对于100%的数据，满足1<=Q<=100
输出
对于每组测试数据，如果小Hi他们能够顺利完成关卡，则输出一个整数Ans，表示小Hi他们至少需要答对的题目数量，否则输出No。
样例输入
1
2 10 9 1
12 35 
样例输出
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
			三种情况,
			j<leastNum<jostNum;
			leastNum<=j<mostNum;
			j>=mostNum;
			*/
			leastNum = (int)ceil((double)tempPoints[i - 1] / (double)mQuestion.S);
			//mostNum = ceil((double)tempPoints[i] / (double)mQuestion.T);
			minSNum[j] = 2000;
			if (leastNum > j) {
				//剩余题目数量不够，故本次j循环结束；
				continue;
			}
			if (i == mQuestion.N && j != mQuestion.M) break; //最后一次循环只计算 j = M;
			int leastTNum;
			for (int sNum = leastNum; sNum >= 0; sNum--) {
				leastTNum = (int)ceil((double)(tempPoints[i - 1] - sNum*mQuestion.S) / (double)mQuestion.T);
				leastTNum = leastTNum <= 0 ? 0 : leastTNum;
				if (leastTNum + sNum > j) break; //若本道题所答题目数量超过M，循环结束;
				//若minSNum[i - 1][j - sNum - leastTNum] == 2000，说明答对sNum个题走不通。
				if (i!=1 && minSNum[j - sNum - leastTNum] == 2000) break;
				//更新minSNum[i][j]，如果minSNum[i][j]==2000，说明此时为No;
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
