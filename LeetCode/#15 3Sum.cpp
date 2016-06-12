#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
	void adjustMaxHeap(vector<int>& nums, unsigned int i, unsigned int arr_len) {
		int curParent = nums[i];
		unsigned int child = 2 * i + 1;
		while (child<arr_len) {
			if (child + 1<arr_len && nums[child] < nums[child + 1]) {
				child++;
			}
			if (curParent<nums[child]) {
				nums[i] = nums[child];
				i = child;
				child = 2 * i + 1;
			}
			else break;
		}
		nums[i] = curParent;
	}
	void sort_array(vector<int>& nums) {
		//heap_sort
		unsigned int arr_len = nums.size();
		for (int i = arr_len / 2 - 1; i >= 0; i--) {
			adjustMaxHeap(nums, i, arr_len);
		}
		for (int i = arr_len - 1; i >= 0; i--) {
			int max = nums[0];
			nums[0] = nums[i];
			nums[i] = max;

			adjustMaxHeap(nums, 0, i);
		}
	}
	bool isEqual(int two_sum, vector<int> & nums, vector<int>::iterator leftIndex, vector<int>::iterator rightIndex) {
		if (*leftIndex + *rightIndex == two_sum)
			return true;

	}
	vector<vector<int> > threeSum(vector<int>& nums) {
		if (nums.size() == 0) return vector<vector<int> >(0);
		sort_array(nums);
		vector<vector<int> > result;
		int two_sum;
		vector<int>::iterator leftIndex;
		vector<int>::iterator rightIndex;
		int currentValue = *nums.begin();
		for (vector<int>::iterator itor = nums.begin(); itor != nums.end(); itor++) {
			if (itor == nums.begin() || currentValue == *itor) continue;
			two_sum = - *itor;
			leftIndex = itor + 1;
			rightIndex = nums.end() - 1;
			while (leftIndex < rightIndex) {
				if ((*leftIndex) + (*rightIndex) == two_sum) {
					vector<int> this_arr = { *itor,*leftIndex,*rightIndex };
					if(find(result.begin(),result.end(), this_arr) == result.end())
					result.push_back(this_arr);
					leftIndex++;
					rightIndex--;
				}
				else if ((*leftIndex) + (*rightIndex) > two_sum) {
					rightIndex--;
				}
				else {
					leftIndex++;
				}
			}
			currentValue = *itor;
		}
		return result;
	}
};

int main() {
	Solution mSolution;
	vector<int>  para = { 7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6};
	mSolution.threeSum(para);
	return 0;
}