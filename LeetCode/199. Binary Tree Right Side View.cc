/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
 /**
当一个节点弹出队列之前，将其所有子节点入队列，当last指针指向的节点弹出队列之后，队列中最后一个节点就是下一行的最后一个节点，将last指向其即可。
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        TreeNode *pNode, *last = root;
		vector<int> arr;
		deque<TreeNode*> _queue;
		
		if(root)
		    _queue.push_back(root);
		
		while(!_queue.empty()){
			pNode = _queue.front();
			if(pNode->left)
				_queue.push_back(pNode->left);
			if(pNode->right)
				_queue.push_back(pNode->right);
			if(pNode == last){
				arr.push_back(pNode->val);
				last = _queue.back();
			}
			_queue.pop_front();
			
		}
		return arr;
    }
};