/**
Given an encoded string, return it's decoded string. 
The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.
Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4]. 
Examples: 
s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
*/

// 2[a]3[b]]
// 2[a3[b]]
// 递归
class Solution {
public:
	string decodeString(string& s,int& i){
		int cnt = 0;string out;
		while(i<s.size() && s[i]!=']'){
			if(isdigit(s[i])){
				cnt = cnt*10 + s[i] - '0';
			}
			else if(s[i]=='['){
				i++;
				string tmp = decodeString(s,i);
				for(int k=0;k<cnt;k++){
					out.append(tmp);
				}
				cnt = 0;
			}
			else{
			    out.push_back(s[i]);
			}
			i++;
		}
		cout<<out<<endl;
		return out;
	}
    string decodeString(string s) {
        int i = 0;
		return decodeString(s,i);
    }
};