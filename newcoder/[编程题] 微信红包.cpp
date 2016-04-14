#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Gift {
public:
	int getValue(vector<int> gifts, int n) {
		// write code here
		unordered_map<int, int> giftsNum;
		for (int i = 0; i<n; i++) {
			giftsNum[gifts[i]]++;
			if (giftsNum[gifts[i]] > n / 2)
				return gifts[i];
		}
	}
};