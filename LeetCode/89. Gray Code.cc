/**
89. Gray Code  
Question
Editorial Solution 
My Submissions 

Total Accepted: 72770
Total Submissions: 188929
Difficulty: Medium
Contributors: Admin 

The gray code is a binary numeral system where two successive values differ in only one bit.
Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
00 - 0
01 - 1
11 - 3
10 - 2
*/

class Solution {
public:
    vector<int> grayCode(int n) {
		vector<int> arr;
		arr.push_back(0);
		int length;
		for(int i = 0;i < n; i++){
		    length = arr.size()-1;
			for(int k = length; k>=0;k--){
				arr.push_back(arr[k] + (1<<i));
			}
		}
		return arr;
    }
};