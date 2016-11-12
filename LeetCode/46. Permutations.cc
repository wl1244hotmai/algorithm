//非递归实现全排列
class Solution {
public:
	// 1 2 3 5 4
	bool next_permutation(vector<int>& nums){
		unsigned int i = nums.size() - 1;
		while(i>=1 && nums[i] < nums[i-1]) i--;
		if(i==0) return false;
		int idx = i-1;
		int min_idx;
		int _min = INT_MAX;
		for(int k = i;k<nums.size();k++){
			if(nums[idx] < nums[k])
				if(_min > nums[k]){
					_min = nums[k];
					min_idx = k;
				}
		}
		swap(nums[idx],nums[min_idx]);
		i = idx+1;
		unsigned int j = nums.size()-1;
		while(i<j){
			swap(nums[i],nums[j]);
			i++;j--;
		}
		return true;
	}
    vector<vector<int>> permute(vector<int>& nums) {
        sort(nums.begin(),nums.end());
		vector<vector<int>> permutation;
		do{
			permutation.push_back(nums);
			for(auto i : nums){
			    cout<<i<<' ';
			}
			cout<<endl;
		}while(next_permutation(nums));
		return permutation;
    }
};