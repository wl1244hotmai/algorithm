/** 
	hihocoder #1036 tireͼ

	����

	ÿ�������ļ����ҽ���һ��������ݡ�

	ÿ���������ݵĵ�һ��Ϊһ������N����ʾ��з�ʵ�Ĵ�С��

	��������N�У�ÿһ��Ϊһ����СдӢ����ĸ��ɵĺ�з���

	��������һ�У�Ϊһƪ���Ȳ�����M����СдӢ����ĸ��ɵ����¡�

	����60%�����ݣ����к�з����ĳ����ܺ�С��10, M<=10

	����80%�����ݣ����к�з����ĳ����ܺ�С��10^3, M<=10^3

	����100%�����ݣ����к�з����ĳ����ܺ�С��10^6, M<=10^6, N<=1000

	���

	����ÿ��������ݣ����һ��"YES"����"NO"����ʾ�������Ƿ��к�з���

	��������

	6
	aaabc
	aaac
	abcc
	ac
	bcd
	cd
	aaaaaaaaaaabaaadaaac

	�������

	YES

 */

/**
	Trieͼ�Ľ�����
	�Ƚ���Trie����
	��Trie�����п�����ȱ�����ͨ��qunue����

	���ÿ���ڵ��ǰ׺�ڵ㣨abcd��ǰ׺��bcd���ڵ�d����
	root�ڵ��ǰ׺�ڵ㻹��root��root�ڵ�ĺ��ӵ�ǰ׺�ڵ�Ҳ��root��
	�����ڵ��ǰ׺�ڵ㣬Ϊ�丸�ڵ��ǰ׺�ڵ����������ߵ���ĵĵ㣬
	����abcd��ǰ׺����abc�е�c��ǰ׺�ڵ㣨bc��������d�����ߣ�����bcd��

	Ȼ��ȫÿ���ڵ�����бߡ�
	����abcd��dֻ��aһ���ߣ�����b,c,d,ÿ����ָ����ǰ׺�ڵ㾭�������ߣ�
	��abcb�����ߣ�Ϊabc��ǰ׺�ڵ�(bc)��d�����ߣ�����bcd��
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
	//ʹ�ö��н��п������������
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