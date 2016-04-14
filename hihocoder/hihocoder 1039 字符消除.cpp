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
	//ʹ��ifstream cin�ض���cin�����׼��������
	//ifstream cin("cin.txt");

	/*
	���⣬Ҳ���Խ��������е�buf�ȱ��棬��file��buf����cin�������¸���
	std::ifstream in("in.txt");
	// ��֮ǰ����������������
	std::streambuf *cinbuf = std::cin.rdbuf();
	// �ض���������
	std::cin.rdbuf(in.rdbuf());

	std::ofstream out("out.txt");
	// ��֮ǰ���������������
	std::streambuf *coutbuf = std::cout.rdbuf();
	// �ض��������
	std::cout.rdbuf(out.rdbuf());

	// �ָ�ԭ�������������
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