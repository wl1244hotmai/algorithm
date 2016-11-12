/**
Given a binary tree 
    struct TreeLinkNode {
      TreeLinkNode *left;
      TreeLinkNode *right;
      TreeLinkNode *next;
    }

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
Initially, all next pointers are set to NULL.
Note: 
You may only use constant extra space.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

For example,
Given the following perfect binary tree,
         1
       /  \
      2    3
     / \  / \
    4  5  6  7

After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL
*/


/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
private:
	TreeLinkNode *last, *node;
	deque<TreeLinkNode*> _queue;
public:
    void connect(TreeLinkNode *root) {
        last = root;
		if(root) _queue.push_back(root);
		while(!_queue.empty()){
			node = _queue.front();
			_queue.pop_front();
			if(node->left) _queue.push_back(node->left);
			if(node->right) _queue.push_back(node->right);
			if(node == last){
				last = _queue.back();
				node->next = NULL;
			}
			else{
				node->next = _queue.front();
			}

		}
    }
};