// given a string, find the length of the longest substring 
// without repeating characters. 
// for example, the longest substring without repeating 
// letters for "abcabcbb" is "abc", 
// which the length is 3. for "bbbbb" the longest substring is "b", 
// with the length of 1.
// tags��hash table two pointers string  

#include<iostream>
#include<string>
#include<algorithm>    // std::max
#include<unordered_map>

using namespace std;

int lengthOfLongestSubstring(string s) {
	unordered_map<char, int> my_Map;
	int maxLength = 0;
	//˫ָ�� itor��itorBegin��
	//itor����string,itorBegin����ظ�Ԫ��
	string::iterator itorMaxBegin = s.begin();
	string::iterator itorBegin = s.begin();
	int length = 0;
	for (string::iterator itor = s.begin(); itor < s.end();itor++) {
		if (my_Map.find(*itor) != my_Map.end()) {
			if (maxLength < length) {
				maxLength = length;
				itorMaxBegin = itorBegin;
			}
			length = distance(s.begin(), itor) + 1 - my_Map[*itor];
			while (*itorBegin != *itor) {
				my_Map.erase(*itorBegin);
				itorBegin++;
			}
			itorBegin++; //��һ�β��ظ��ַ��Ŀ�ʼ
		}
		else {
			length++;
		}
		my_Map[*itor] = distance(s.begin(), itor) + 1;
	}
	if (maxLength < length) {
		maxLength = length;
		itorMaxBegin = itorBegin;
	}
	for (string::iterator itor = itorMaxBegin; itor < itorMaxBegin + maxLength; itor++) {
		cout << *itor << " ";
	}
	cout << endl;
	return maxLength;
}

int main() {
	string s;
	cin >> s;
	cout << lengthOfLongestSubstring(s);
	system("pause");
	return 0;
}