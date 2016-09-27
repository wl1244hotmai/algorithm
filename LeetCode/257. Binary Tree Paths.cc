/**
Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:

["1->2->5", "1->3"]
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
    void dfs(TreeNode* node,vector<string>& str, queue<int> path){
        if(!node) return;
        path.push(node->val);
        if(!node->left && !node->right) {
            ostringstream os;
            while(!path.empty()){
                os<<path.front();
                //cout<<path.front();
                path.pop();
                if(!path.empty()) os<<"->";
            }
            str.push_back(os.str());
        }
        else{
             if(node->left) dfs(node->left,str,path);
             if(node->right) dfs(node->right,str,path); 
        }
    }
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> str;
        queue<int> path;
        dfs(root,str,path);
        return str;
    }
};