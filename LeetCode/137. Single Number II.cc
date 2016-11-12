//Given an array of integers, every element appears three times except for one. Find that single one. 
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int one = 0,two = 0,three = 0;
        for(auto i : nums){
            two |= one & i;
            one^=i;
            three = one & two;
            one = one & ~three;
            two = two & ~three;
        }
        return one;
    }
};