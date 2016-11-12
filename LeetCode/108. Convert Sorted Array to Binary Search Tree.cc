/**
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
	TreeNode* sortedArrayToBST(vector<int>& nums,int s,int e) {
		if(s>e || s<0 || e>=nums.size()) return NULL;
		int mid = (s+e)/2;
		TreeNode* root = new TreeNode(nums[mid]);
		root->left = sortedArrayToBST(nums,s,mid-1);
		root->right = sortedArrayToBST(nums,mid+1,e);
		return root;
	}
    TreeNode* sortedArrayToBST(vector<int>& nums) {
		return sortedArrayToBST(nums,0,nums.size()-1);
    }
};