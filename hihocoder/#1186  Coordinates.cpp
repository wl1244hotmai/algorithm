#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> getDivisors(int N) {
	vector<int> divisors;
	if (N == 1) {
		divisors.push_back(1);
		return divisors;
	}
	divisors.push_back(1);
	divisors.push_back(N);
	vector<int>::iterator itorLeft = divisors.begin() + 1;
	for (int i = 2; i <= sqrt(N); i++) {
		if (N%i == 0) {
			itorLeft = divisors.insert(itorLeft, i);
			itorLeft++;
			if (i != N / i) {
				itorLeft = divisors.insert(itorLeft, N / i);
			}
		}
	}
	return divisors;
}
int main(int argv, char* argc[]) {
	int N, M;
	cin >> N >> M;
	vector<int> divisorsN;
	vector<int> divisorsM;
	divisorsN = getDivisors(N);
	divisorsM = getDivisors(M);
	for (vector<int>::iterator itorN = divisorsN.begin(); itorN < divisorsN.end(); itorN++) {
		for (vector<int>::iterator itorM = divisorsM.begin(); itorM < divisorsM.end(); itorM++) {
			cout << *itorN << " " << *itorM<<endl;
			//if ((itorN == divisorsN.end() - 1) && itorM == divisorsM.end() - 1) {

			//}
			//else {
			//}
		}
	}
	return 0;
}