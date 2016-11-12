#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>
using namespace std;
istringstream is;
int value;
struct Node {
	int value;
	Node* left;
	Node* right;
	Node(int value) {
		this->value = value;
	}
};
void insertLeft(Node* pNode);
void insertRight(Node* pNode);
// 5 3 2 1 # # 4 # # 7 6 # # 8 # #

void insertLeft(Node* pNode) {
	is >> value;
	if (value == -1)
		return;
	pNode->left = new Node(value);
	pNode = pNode->left;
	insertLeft(pNode);
	insertRight(pNode);

}

void insertRight(Node* pNode) {
	is >> value;
	if (value == -1)
		return;
	pNode->right = new Node(value);
	pNode = pNode->right;
	insertLeft(pNode);
	insertRight(pNode);

}


//for test
void display(Node* root) {
	if (root == NULL) return;
	cout << root->value;
	display(root->left);
	display(root->right);
}

Node* createBST() {
	string _str = { "5 3 2 1 -1 -1 -1 4 -1 -1 7 6 -1 -1 8 -1 -1" };
	is.str(_str);
	is >> value;
	Node* root = new Node(value);
	Node* pNode = root;
	insertLeft(pNode);
	insertRight(pNode);
	display(root);
	return root;
}

int depth(Node* node) {
	if (node == NULL) return 0;
	return 1 + max(depth(node->left), depth(node->right));
}

bool judge(Node* node) {
	if (!node) return true;
	// cout<<node->value;
	if (!judge(node->left)) return false;
	if (!judge(node->right)) return false;
	int depthLeft = depth(node->left);
	int depthRight = depth(node->right);
	// cout<<abs(depthLeft-depthRight);
	if (abs(depthLeft - depthRight)>1) {
		return false;
	}
	return true;
}

int main() {

	//BST 
	Node* root = createBST();
	cout << endl;
	if (judge(root)) {
		cout << "是平衡树";
	}
	else {
		cout << "不是平衡树";
	}
	return 0;
}