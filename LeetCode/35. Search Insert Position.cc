/**
35. Search Insert Position  

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
You may assume no duplicates in the array.
Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0 
*/

class Solution {
  public:
    int searchInsert(vector<int>& nums, int target) {
      int l = 0, r = nums.size();
      while (l < r) {
        int mid = (l + r) >> 1;
        if (nums[mid] >= target) r = mid;
        else l = mid + 1;
      }
      return l;
    }
};


class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1, mid = (l + r) / 2;
		while(nums[mid] != target){
			if(nums[mid] > target){
				if(mid==0 || nums[mid-1]<target){
					break;
				}
				r = mid-1;
			}
			else{
				if(mid == nums.size()-1 || nums[mid+1]>target){
					mid++;
					break;
				}
				l = mid+1;
			}
			mid = (l+r)/2;
		}
		return mid;
    }
};