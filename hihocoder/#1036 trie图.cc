/** 
	hihocoder #1036 tire图

	输入

	每个输入文件有且仅有一组测试数据。

	每个测试数据的第一行为一个整数N，表示河蟹词典的大小。

	接下来的N行，每一行为一个由小写英文字母组成的河蟹词语。

	接下来的一行，为一篇长度不超过M，由小写英文字母组成的文章。

	对于60%的数据，所有河蟹词语的长度总和小于10, M<=10

	对于80%的数据，所有河蟹词语的长度总和小于10^3, M<=10^3

	对于100%的数据，所有河蟹词语的长度总和小于10^6, M<=10^6, N<=1000

	输出

	对于每组测试数据，输出一行"YES"或者"NO"，表示文章中是否含有河蟹词语。

	样例输入

	6
	aaabc
	aaac
	abcc
	ac
	bcd
	cd
	aaaaaaaaaaabaaadaaac

	样例输出

	YES

 */

/**
	Trie图的建立：
	先建立Trie树，
	对Trie树进行宽度优先遍历（通过qunue），

	求出每个节点的前缀节点（abcd的前缀是bcd所在的d），
	root节点的前缀节点还是root，root节点的孩子的前缀节点也是root，
	其他节点的前缀节点，为其父节点的前缀节点再走这条边到达的的点，
	例如abcd的前缀，是abc中的c的前缀节点（bc），再走d这条边（到达bcd）

	然后补全每个节点的所有边。
	例如abcd的d只有a一条边，则补齐b,c,d,每条边指向其前缀节点经过这条边，
	如abcb这条边，为abc的前缀节点(bc)走d这条边，到达bcd。
 */
#include<iostream>
#include<queue>
#define Loop(i,c,n) for(int i=c;i<n;i++)
#define ALPHBET_LENGTH 26
using namespace std;

struct trieNode {
	trieNode* suffixNode;
	trieNode* next[26];
	bool isFinalChar;
};

trieNode* createNewNode() {
	trieNode* pNode = new trieNode();
	pNode->isFinalChar = false;
	Loop(i, 0, ALPHBET_LENGTH) {
		pNode->next[i] = NULL;
	}
	return pNode;
}

class trieGraph {
private:
	trieNode* rootNode;
public:
	trieGraph() {
		rootNode = createNewNode();
		rootNode->suffixNode = rootNode;
	}
	void generateTrieTree(char** input, int strNum);
	void generateTrieGraph();
	bool queryArticle(char* mArcitle);
};

void trieGraph::generateTrieTree(char** input, int strNum) {
	trieNode* pNode;
	Loop(i, 0, strNum) {
		pNode = rootNode;
		for (char* p = input[i]; *p; p++) {
			if (pNode->next[*p - 'a'] == NULL) {
				pNode->next[*p - 'a'] = createNewNode();
			}
			pNode = pNode->next[*p - 'a'];
		}
		pNode->isFinalChar = true;
	}
}

void trieGraph::generateTrieGraph() {
	//使用队列进行宽度优先搜索。
	trieNode * pNode;
	queue<trieNode*> trieGraphQueue;
	trieGraphQueue.push(rootNode);
	while (!trieGraphQueue.empty()) {
		pNode = trieGraphQueue.front();
		trieGraphQueue.pop();
		Loop(i, 0, ALPHBET_LENGTH) {
			if (pNode->next[i] != NULL) {
				trieGraphQueue.push(pNode->next[i]);
				if (pNode == rootNode) {
					pNode->next[i]->suffixNode = pNode;
				}
				else {
					pNode->next[i]->suffixNode = pNode->suffixNode->next[i];
				}
			}
			else {
				if (pNode == rootNode) {
					pNode->next[i] = rootNode;
				}
				else {
					pNode->next[i] = pNode->suffixNode->next[i];
				}
			}
		}
	}
}

bool trieGraph::queryArticle(char* mArticle) {
	trieNode* pNode = rootNode;
	for (char* p = mArticle; *p; p++) {
		pNode = pNode->next[*p - 'a'];
		if (pNode->isFinalChar) {
			return true;
		}
	}
	return false;
}

int main(int argv, char** argc) {
	int N;
	cin >> N;
	char **input = new char*[N];
	char* mArticle = new char[1000001];
	Loop(i, 0, N) {
		input[i] = new char[1000000];
		cin >> input[i];
	}
	trieGraph mTrieGraph;
	mTrieGraph.generateTrieTree(input, N);
	mTrieGraph.generateTrieGraph();
	cin >> mArticle;
	if (mTrieGraph.queryArticle(mArticle)) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}
	Loop(i, 0, N) {
		delete[] input[i];
	}
	system("pause");	
	return 0;
}