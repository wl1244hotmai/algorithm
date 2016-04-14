//#include<iostream>
//#include<vector>
//#include<string>
//#include<cmath>
//#include<algorithm>
//
//using namespace std;
//
//void process(int N, int P, int W, int H,vector<int> a) {
//	int S = W < H ? W : H;
//	int sum = 0;
//	for (vector<int>::iterator itor = a.begin(); itor < a.end(); itor++) {
//		sum += *itor;
//	}
//	int temp = (int)sqrt(W*H*P / sum + 1);
//	S = S < temp ? S : temp;
//	int wNum;
//	int hNum;
//	int sum2;
//	for (int i = S; i >= 1; i--) {
//		sum2 = 0;
//		wNum = W / i;
//		hNum = H / i;
//		for (vector<int>::iterator itor = a.begin(); itor < a.end(); itor++) {
//			sum2 += ((int)ceil((double)*itor / (double)wNum));
//		}
//		if (sum2 <= (hNum*P)) {
//			cout << i << endl;
//			return;
//		}
//	}
//}
//
//int main(int argv, char* argc[]) {
//	int TASKS;
//	cin >> TASKS;
//	vector<int> N(TASKS), P(TASKS), W(TASKS), H(TASKS);
//	vector<vector<int> > a(TASKS);
//	for (int i = 0; i < TASKS; i++) {
//		cin >> N[i] >> P[i] >> W[i] >> H[i];
//		a[i] = vector<int>(N[i]);
//		for (int j = 0; j < N[i]; j++) {
//			cin >> a[i][j];
//		}
//	}
//	for (int i = 0; i < TASKS; i++) {
//		process(N[i], P[i], W[i], H[i], a[i]);
//	}
//	return 0;
//}