#include<iostream>
#include<vector>
#include<string>
#include"[编程题] 微信红包.cpp"
using namespace std;
class GrayCode {
public:
	void addChar(vector<string>::iterator grayItor, int begin, int end, char code,bool isFirstHalf) {
		int middle = (end - begin + 1) / 2;
		for (int i = begin; i <= end; i++) {
			(*(grayItor+i)).push_back(code);
		}
		if (end == begin) return;
		if (isFirstHalf) {
			addChar(grayItor, begin, begin + middle - 1, '0',true);
			addChar(grayItor, begin + middle, end, '1',false);
		}
		else {
			addChar(grayItor, begin, begin + middle - 1, '1', true);
			addChar(grayItor, begin + middle, end, '0', false);
		}
	}
	vector<string> getGray(int n) {
		// write code here
		vector<string> grayArray;
		if (n == 0) return grayArray;
		int grayLength = 1 << n;
		grayArray = vector<string>(grayLength);
		vector<string>::iterator grayItor = grayArray.begin();
		addChar(grayItor, 0, grayLength / 2 - 1, '0', true );
		addChar(grayItor, grayLength / 2, grayLength - 1,'1', false);
		return grayArray;
	}
};
/**
int main() {
	//GrayCode graycodeInstance;
	//vector<string> grayArray = graycodeInstance.getGray(3);
	Gift gift;
	cout << gift.getValue({ 1,2,3,2,2 }, 5);
	return 0;
}
*/