class Solution {
public:
    unordered_map<char,string > _map = {
        {'2',"abc"},
        {'3',"def"},
        {'4',"ghi"},
        {'5',"jkl"},
        {'6',"mno"},
        {'7',"pqrs"},
        {'8',"tuv"},
        {'9',"wxyz"}
    };
    vector<string> letterCombinations(string digits) {
        vector<string> output(0);
        for(string::iterator digits_itor = digits.begin(); 
			digits_itor!=digits.end(); 
			digits_itor++){
			
			if(digits_itor == digits.begin()){
			    for(string::iterator letter_itor = _map[*digits_itor].begin();
				letter_itor!= _map[*digits_itor].end();
				letter_itor++){
				    string temp;
				    temp.push_back(*letter_itor);
					output.push_back(temp);
				}
			}
			else
			{
    		    for(vector<string>::iterator itor = output.begin(); itor!=output.end(); itor++){
    				string lastStr = *itor;
    				for(string::iterator letter_itor = _map[*digits_itor].begin();
    					    letter_itor< _map[*digits_itor].end();
    					    letter_itor++){
    					string tempStr = lastStr;
    					if(letter_itor == _map[*digits_itor].begin()) {
    						(*itor).push_back(*letter_itor);
    					}
    					else{
    					    tempStr.push_back(*letter_itor);
    					    itor++;
    						itor = output.insert(itor,tempStr);

    					}
    				}

    			}
			}
		}
        return output;
    }
};
