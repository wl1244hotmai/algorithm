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
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> _stack;
        vector<int> pre_order;
        TreeNode* pNode = root;
        while(pNode || !_stack.empty()){
			//·ÇµÝ¹éÏÈÐò±éÀú
            while(pNode){
              _stack.push(pNode);
              pre_order.push_back(pNode->val);
              cout<<pNode->val<<' ';
              pNode = pNode->left;
            }
			if(!_stack.empty()){
				pNode = _stack.top()->right;
				_stack.pop();
			}
        }
		return pre_order;
    }
};