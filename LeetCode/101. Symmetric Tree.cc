/**
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 * 
 */
class Solution {
public:
    bool isMirror(TreeNode* root1,TreeNode* root2){
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;
        return root1->val == root2->val && isMirror(root1->left,root2->right) && isMirror(root1->right,root2->left);
    }
    bool isSymmetric(TreeNode* root) {
        return isMirror(root,root);
    }
};
