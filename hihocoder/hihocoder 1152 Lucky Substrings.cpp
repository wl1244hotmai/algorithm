#include<iostream>
#include<vector>
#include<string>
using namespace std;
bool fibonacciNumber[22];


struct trie_node {
	trie_node *children[26];
	bool isFinal;
};

void addTrieNode(string subStr,trie_node* root) {
	trie_node *node = root;
	for (string::iterator itor = subStr.begin(); itor < subStr.end();itor++) {
		if (node->children[*itor - 'a'] == NULL)
			node->children[*itor - 'a'] = new trie_node();
		node = node->children[*itor - 'a'];
	}
	node->isFinal = true;
}

bool isFibonacci(string subStr) {
	int letterNumbers[26] = { 0 };
	for (string::iterator itor = subStr.begin(); itor < subStr.end(); itor++) {
		letterNumbers[*itor - 'a']++;
	}
	int count = 0;
	for (int i = 0; i < 26; i++) {
		if (letterNumbers[i] != 0) {
			count++;
		}
	}
	if (fibonacciNumber[count])
		return true;
	else
		return false;
}
void displayStrings(trie_node* root,string subStr) {
	string tempStr;
	if (root->isFinal) {
		cout << subStr << endl;
	}
	for (int i = 0; i < 26; i++) {
		if (root->children[i] != NULL) {
			tempStr = subStr + (char)(i + 'a');
			displayStrings(root->children[i], tempStr);
		}
	}

}
int main(int argv, char* argc[]) {
	string myStr;
	cin >> myStr;
	fibonacciNumber[1] = true;
	fibonacciNumber[2] = true;
	fibonacciNumber[3] = true;
	fibonacciNumber[5] = true;
	fibonacciNumber[8] = true;
	fibonacciNumber[13] = true;
	fibonacciNumber[21] = true;
	trie_node* root = new trie_node();
	for (unsigned int i = 0; i < myStr.length(); i++) {
		for (unsigned int j = 1; j < myStr.length()-i+1; j++) {
			string subStr = myStr.substr(i, j);
			if (isFibonacci(subStr)) {
				addTrieNode(subStr, root);
			}
		}
	}
	displayStrings(root,"");
	return 0;
}