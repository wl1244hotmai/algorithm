/**
 The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place forms a binary tree". It will automatically contact the police if two directly-linked houses were broken into on the same night. 
Determine the maximum amount of money the thief can rob tonight without alerting the police. 
Example 1:
     3
    / \
   2   3
    \   \ 
     3   1
Maximum amount of money the thief can rob = 3 + 3 + 1 = 7. 

Example 2:
     3
    / \
   4   5
  / \   \ 
 1   3   1
Maximum amount of money the thief can rob = 4 + 5 = 9. 
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
private:
	//用指针作为key
	unordered_map<long,int[2]> _map;
public:
	int rob(TreeNode* root, int x){
		if(!root) return 0;
		if(_map[(long)root][x]!=0)
			return _map[(long)root][x];
		if(x){
			_map[(long)root][1] = root->val + rob(root->left,0) + rob(root->right,0);
			cout<<_map[(long)root][1]<<endl;
			return _map[(long)root][1];
		}else{
			_map[(long)root][0] = max(rob(root->left,0),rob(root->left,1))
				  +max(rob(root->right,0),rob(root->right,1));
            cout<<_map[(long)root][0]<<endl;
			return _map[(long)root][0];
		}
	}
    int rob(TreeNode* root) {
		return max(rob(root,0),rob(root,1));
    }
};