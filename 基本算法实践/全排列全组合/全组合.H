#include<vector>
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Subsets{
private:
	string chars;
	int length;
public:
	Subsets() {
		//init
		getline(cin, chars);
		sort(chars.begin(), chars.end());
		length = chars.size();
	}
	void allSets() {
		int kinds = (int)pow(2, length) - 1;
		for (int i = 1; i < kinds; i++) {
			for (int j = 0; j < length; j++) {
				if ((1 << j) & i) {
					cout << chars[j] << " ";
				}
			}
			cout << endl;
		}
	}
};