#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;

int getScore(string str) {
	if (str.size() == 0) return 0;
	int score = 0;
	int deffIndex = 0;
	str.append(",");
	string newStr;
	for (unsigned int i = 1; i < str.size(); i++) {
		if (str[i] != str[i - 1]) {
			if (deffIndex == i - 1) {
				newStr += str[i - 1];
			}
			deffIndex = i;
		}
	}
	if (str.size() == newStr.size() + 1) return 0;
	return str.size() - 1 - newStr.size() + getScore(newStr);
}

int getMaxScore(string str) {
	int score = 0;
	string newStr;
	for (unsigned int i = 0; i <= str.size(); i++) {
		for (int j = 0; j < 3; j++) { //A or B or C
			newStr = str.substr(0, i);
			switch (j) {
			case 0:
				newStr.append("A");
				break;
			case 1:
				newStr.append("B");
				break;
			case 2:
				newStr.append("C");
				break;
			}
			newStr.append(str.substr(i));
			//cout << newStr << endl;
			score = max(score, getScore(newStr));
		}
	}
	return score;
}

int main() {
	//使用ifstream cin重定向cin这个标准输入流；
	//ifstream cin("cin.txt");

	/*
	此外，也可以将输入流中的buf先保存，将file的buf传给cin后，再重新给他
	std::ifstream in("in.txt");
	// 把之前的输入流保存起来
	std::streambuf *cinbuf = std::cin.rdbuf();
	// 重定向输入流
	std::cin.rdbuf(in.rdbuf());

	std::ofstream out("out.txt");
	// 把之前的输出流保存起来
	std::streambuf *coutbuf = std::cout.rdbuf();
	// 重定向输出流
	std::cout.rdbuf(out.rdbuf());

	// 恢复原来的输入输出流
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);

	*/
	ifstream in("cin.txt");
	streambuf * backup;
	backup = cin.rdbuf();
	cin.rdbuf(in.rdbuf());

	int N;
	cin >> N;
	vector<string> myStr(N);
	for (int i = 0; i < N; i++) {
		cin >> myStr[i];
	}
	for (int i = 0; i < N; i++) {
		cout << getMaxScore(myStr[i]) << endl;
	}
	return 0;
}