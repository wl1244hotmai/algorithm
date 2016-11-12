/**
Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

Example 1 
Input: "2-1-1".
((2-1)-1) = 0
(2-(1-1)) = 2
Output: [0, 2]

Example 2 
Input: "2*3-4*5"
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10
Output: [-34, -14, -10, -10, 10]
*/
class Solution {
vector<int> arr;
public:
    vector<int> diffWaysToCompute(string input) {
		vector<int> res;
		int cnt = 0;
		for(auto c : input){
			if(c=='+' || c=='-' || c=='*'){
				vector<int> a1 = diffWaysToCompute(input.substr(0,cnt));
				vector<int> a2 = diffWaysToCompute(input.substr(cnt+1));
			}
			for(auto i : a1){
				for(auto j : a2){
					switch(c){
					case '+':
						res.push_back(i+j);
						break;
					case '-':
						res.push_back(i-j);
						break;
					case '*':
						res.push_back(i*j);
						break;
					}
				}
			}
			cnt++;
		}
		if(res.empty()){
			res.push_back(atoi(input.c_str()));
		}
		return res;
    }
};