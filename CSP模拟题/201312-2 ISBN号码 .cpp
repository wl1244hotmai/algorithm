#include<iostream>
using namespace std;

int main() {
	char ISBN[14];
	// cin >> ISBN;
	int cnt = 1;
	int sum = 0;
	for (int i = 0; i < 11; i++) {
		char tmpStr = ISBN[i];
		if (ISBN[i] == '-')
			continue;
		else {
			sum += cnt * (ISBN[i] - '0');
			cnt++;
		}
	}
	sum %= 11;
	if (ISBN[12] == 'X' && sum == 10
		|| ISBN[12] - '0' == sum)
		cout << "Right";
	else
	{
		if (sum == 10) {
			ISBN[12] = 'X';
		}
		else {
			ISBN[12] = sum + '0';
		}
		cout << ISBN;
	}
	system("pause");
	return 0;
}