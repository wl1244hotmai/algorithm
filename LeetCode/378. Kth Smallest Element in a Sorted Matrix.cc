/**
Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.
Note that it is the kth smallest element in the sorted order, not the kth distinct element. 
Example: 
matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.

Note: 
You may assume k is always valid, 1 ≤ k ≤ n2.
*/

/** 思路
优先级队列/最小堆，以某一行/某一列构建，之后减去一个加入一个。
*/
class Solution {
public:
	struct Node{
		int val;
		int i;
		int j;
		bool operator<(const Node& other) const{
			return this->val < other.val;
		}
		bool operator>(const Node& other) const{
			return this->val > other.val;
		}
		Node(){}
		Node(int v,int i,int j):val(v),i(i),j(j) {}
	};
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<Node,vector<Node>,greater<Node> > _queue;
		for(int i = 0;i<matrix.size();i++){
			_queue.push(Node(matrix[0][i],0,i));
		}
		Node node;
		while(k){
			k--;
			node = _queue.top();
			_queue.pop();
			cout<<node.val<<endl;
			int i = node.i;
			int j = node.j;
			if(i<matrix.size()-1){
				_queue.push(Node(matrix[i+1][j],i+1,j));
			}
		}
		return node.val;
    }
};