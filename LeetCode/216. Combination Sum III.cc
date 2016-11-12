/**
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.

Example 1:
Input: k = 3, n = 7
Output: 

[[1,2,4]]


Example 2:
Input: k = 3, n = 9
Output: 

[[1,2,6], [1,3,5], [2,3,4]]
*/
class Solution {
vector<vector<int> > matrix;
public:
	void combination(int s,int k,int n,vector<int> arr){
	    cout<<n<<endl;
		if(k==0){
			if(n==0){
				matrix.push_back(arr);
			}
			return;
		}
		for(int i = s;i<=10-k;i++){
			arr.push_back(i);
			combination(i+1,k-1,n-i,arr);
			arr.pop_back();
		}
	}
    vector<vector<int>> combinationSum3(int k, int n) {
		vector<int> arr;
		combination(1,k,n,arr);
		return matrix;
    }
};