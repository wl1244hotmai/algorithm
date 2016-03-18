#include<iostream>
using namespace std;

int main() {
	int n;
	int max = 1;
	int numOfMax = 0;
	cin >> n;
	int s[1000];
	int num[10001] = { 0 };
	for (int i = 0; i<n; i++) {
		cin >> s[i];
		num[s[i]]++;
		if (num[s[i]] > numOfMax) {
			numOfMax = num[s[i]];
			max = s[i];
		}
		if (num[s[i]] == numOfMax
			&& s[i] < max) {
			max = s[i];
		}
	}
	cout << max;
	return 0;
}