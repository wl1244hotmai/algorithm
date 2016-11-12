/**
	template < class ForwardIterator, class T >
	ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T & val) {
		ForwardIterator it;
		iterator_traits < ForwardIterator > :: difference_type count, step;
		count = distance(first, last);
		while (count > 0) {
			it = first;
			step = count / 2;
			advance(it, step);
			if ( * it < val) { // or: if (comp(*it,val)), for version (2)
				first = ++it;
				count -= step + 1;
			} else
				count = step;
		}
		return first;
}
*/

/**
	int func(int l,int r,const int& val,vector<int>& dp){
		int mid;
		while(l<r){
			mid = (l + r) / 2;
			if(dp[mid] < val){
				l = mid + 1;
			}
			else{
				r = mid;
			}
		}
		return l;
	}
*/

class Solution {
public:
/**
 * dp数组存放长度为 1 - L 的序列中，末尾可以的最小值
 */

    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp;
		for(auto i : nums){
			if(dp.empty() || i>dp.back()){
				dp.push_back(i);
			}
			else if(i<dp[0]){
				dp[0] = i;
			}
			else{
				*lower_bound(dp.begin(),dp.end(),i) = i;
			}
		}
		return dp.size();
    }
	
	/**
	输出最后一组出现的LIS
	利用pos数组存储nums每个元素在LIS中的位置；
	然后从后向前遍历pos，依次得到各个位置最后出现的数字。
	
	int lengthOfLIS(vector < int >  & nums) {
		vector < int > dp;
		vector < int > pos;
		for (auto i : nums) {
			if (dp.empty() || i > dp.back()) {
				dp.push_back(i);
				pos.push_back(dp.size() - 1);
			} else if (i < dp[0]) {
				dp[0] = i;
				pos.push_back(0);
			} else {
				auto it = lower_bound(dp.begin(), dp.end(), i);
				* it = i;
				pos.push_back(it - dp.begin());
			}
		}
		int cur = dp.size() - 1;
		stack < int > _stack;
		for (int i = nums.size() - 1; i >= 0; i--) {
			if (pos[i] == cur) {
				_stack.push(nums[i]);
				cur--;
			}
		}
		while (!_stack.empty()) {
			cout << _stack.top() << ' ';
			_stack.pop();
		}
		return dp.size();
	}
	*/

};