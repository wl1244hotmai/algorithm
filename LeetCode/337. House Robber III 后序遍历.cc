/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //递归加由底向上？
class Solution {
	unordered_map<long,int[2]> dp;
public:
	void inorder(TreeNode* root){
		stack<TreeNode*> _stack;
		TreeNode* pNode = root;
		TreeNode* pre = NULL;
		_stack.push(root);
		while(!_stack.empty()){
			pNode = _stack.top();
			if(!pNode) return;
			if( (!pNode->left && !pNode->right)
			  ||(pre && (pre==pNode->left || pre==pNode->right)) ){
				if(!pNode->left && !pNode->right){
					dp[(long)pNode][1] = pNode->val;
					dp[(long)pNode][0] = 0;
				} else {
					dp[(long)pNode][1] = pNode->val + 
						dp[(long)pNode->left][0] + dp[(long)pNode->right][0];
					dp[(long)pNode][0] =
						max(dp[(long)pNode->left][0],dp[(long)pNode->left][1])
					   +max(dp[(long)pNode->right][0],dp[(long)pNode->right][1]);
				}
				cout<<dp[(long)pNode][1]<<' '<<	dp[(long)pNode][0]<<endl;
				
				_stack.pop();
				pre = pNode;
			}
			else{
			    if(pNode->right)
					_stack.push(pNode->right);	
				if(pNode->left)
					_stack.push(pNode->left);
			}
		}
	}
    int rob(TreeNode* root) {
        inorder(root);
		return max(dp[(long)root][0],dp[(long)root][1]);
    }
};