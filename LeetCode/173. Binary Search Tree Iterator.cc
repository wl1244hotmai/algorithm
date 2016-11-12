/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
private:
	TreeNode* pNode;
	stack<TreeNode*> _queue;
public:
    void search(){
		while(pNode){
			_queue.push(pNode);
			pNode = pNode->left;
		}
    }
    BSTIterator(TreeNode *root) {
		pNode = root;
        search();
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !_queue.empty();
    }

    /** @return the next smallest number */
    int next() {
        pNode = _queue.top();
		_queue.pop();
		pNode = pNode->right;
		search();
		return pNode->val;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */