//#include<iostream>
//#include<vector>
//#include<string>
//#include<fstream>
//#include<cstdio>
//#define NO_OPTION 0;
//#define NO_PARA 1;
//#define HAS_PARA 2;
//using namespace std;
////×Ö·û´®·Ö¸îº¯Êý
//std::vector<std::string> split(std::string str, std::string pattern);
//std::vector<std::string> split(std::string str);
//struct Option {
//	bool isVald=false;
//	bool hasPara= false;
//	string para="";
//};
//vector<Option> process(vector<string> cmdOption, int* LowerLetter) {
//	vector<Option> myOption(26);
//	for (vector<string>::iterator itor = cmdOption.begin() + 1; itor < cmdOption.end(); itor++) {
//		if ((*itor).length() == 2 && (*itor)[0] == '-') {
//			if (LowerLetter[(*itor)[1] - 'a'] == 0)
//				return myOption;
//			if (LowerLetter[(*itor)[1] - 'a'] == 1) {
//				myOption[(*itor)[1] - 'a'].isVald = true;
//			}
//			if (LowerLetter[(*itor)[1] - 'a'] == 2) {
//				myOption[(*itor)[1] - 'a'].isVald = true;
//				myOption[(*itor)[1] - 'a'].hasPara = true;
//				myOption[(*itor)[1] - 'a'].para = *(itor + 1);
//				itor++;
//			}
//		}
//		else {
//			return myOption;
//		}
//	}
//	return myOption;
//}
//int main(int argv, char* argc[]) {
//	ifstream cin("cin.txt");
//	int lowerLetters[26] = { 0 };
//	string formatStr;
//	cin >> formatStr;
//	for (string::iterator itor = formatStr.begin(); itor < formatStr.end(); itor++) {
//		if (*itor == ':') continue;
//		if (itor<formatStr.end() - 1 && *(itor + 1) == ':')
//			lowerLetters[*itor - 'a'] = 2;
//		else
//			lowerLetters[*itor - 'a'] = 1;
//	}
//	int N;
//	cin >> N;
//	vector<string> options(N);
//	getline(cin, options[0], '\n');
//	for (int i = 0; i < N; i++) {
//		getline(cin, options[i], '\n');
//	}
//	for (int i = 0; i < N; i++) {
//		vector<Option> res = process(split(options[i]), lowerLetters);
//		cout << "Case " << i + 1 << ":";
//		int cnt = 0;
//		for (vector<Option>::iterator itor = res.begin(); itor < res.end(); itor++) {
//			if ((*itor).isVald) {
//				cout << " " <<"-"<< (char)('a' + cnt);
//			}
//			if ((*itor).hasPara) {
//				cout << " "<<(*itor).para;
//			}
//			cnt++;
//		}
//		cout << endl;
//	}
//	return 0;
//}
//std::vector<std::string> split(std::string str) {
//	return split(str, " ");
//}
//std::vector<std::string> split(std::string str, std::string pattern)
//{
//	int pos;
//	std::vector<std::string> result;
//	str += pattern;//À©Õ¹×Ö·û´®ÒÔ·½±ã²Ù×÷
//	int size = str.size();
//
//	for (int i = 0; i<size; i++)
//	{
//		pos = str.find(pattern, i);
//		if (pos<size)
//		{
//			std::string s = str.substr(i, pos - i);
//			result.push_back(s);
//			i = pos + pattern.size() - 1;
//		}
//	}
//	return result;
//}