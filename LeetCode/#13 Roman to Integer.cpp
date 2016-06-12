#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
	int romanToInt(string s) {

		int result = 0;
		unordered_map<char, int> _map = {
			{ 'I',1 },
			{ 'V',5 },
			{ 'X',10 },
			{ 'L',50 },
			{ 'C',100 },
			{ 'D',500 },
			{ 'M',1000 }
		};

		int count;
		for (unsigned int i = 0; i < s.size(); i++) {
			count = 1;
			while (i<s.size() && s[i] == s[i + 1]) {
				count++;
				i++;
			}
			if (_map[s[i]] < _map[s[i + 1]])
				result -= count*_map[s[i]];
			else
				result += count*_map[s[i]];
		}
		return result;
	}
};

int main() {
	Solution solution = Solution();
	cout << solution.romanToInt("MCMXCVI");
	return 0;
}