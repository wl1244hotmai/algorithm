/**
Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0. 
Example:
Given a / b = 2.0, b / c = 3.0. 
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? . 
return [6.0, 0.5, -1.0, 1.0, -1.0 ]. 
The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>. 
According to the example above: 
equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
*/

//思路 模仿floyd算法 矩阵存放彼此关系；
//a/b -> _map[a][b]
//a/c -> a/b * b/c
class Solution {
private:
	unordered_map<string, unordered_map<string,double> > _map;
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        int i = 0;
		for(auto p : equations){
			_map[p.first][p.first] = 1;
			_map[p.second][p.second] = 1;
			_map[p.first][p.second] = values[i];
			_map[p.second][p.first] = 1 / values[i];
			i++;
		}
		
		for(auto k : _map){
			for(auto i : k.second){
				for(auto j : k.second){
					_map[i.first][j.first] = _map[i.first][k.first] * _map[k.first][j.first];
				}
			}
		}
		vector<double> res;
		for(auto p : queries){
			res.push_back(_map[p.first][p.second]==0?-1:_map[p.first][p.second]);
		}
		
		return res;
    }
};