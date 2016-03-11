#include <iostream>
#include <string>
#define ALPHABET_SIZE 26
using namespace std;

struct trie_node
{
	int count;   // 记录该节点代表的单词的个数
	trie_node *children[ALPHABET_SIZE]; // 各个子节点
};

trie_node* create_trie_node() {
    trie_node *pNode = new trie_node();
    pNode->count = 0;
    for(int i = 0; i<ALPHABET_SIZE ; ++i)
        pNode->children[i] = NULL;
    return pNode;
}

void insert_trie_node(trie_node *root, char *str){
    trie_node *node = root;
    for(char *p=str;*p;++p){
        if(node->children[*p -'a'] == NULL)
            node->children[*p -'a'] = create_trie_node();
        node = node->children[*p -'a'];
        node->count++;
    }
}

int query_trie_node(trie_node *root, char *str){
    trie_node *node = root;
    for(char *p=str;*p;++p){
        if (node->children[*p-'a'] == NULL)
            return 0;
        else
            node = node->children[*p -'a'];
    }
    return node->count;
}

int main(){
    int wordNum=0;
    int queryNum=0;
    cin>>wordNum;
    char **words = new char*[wordNum];
    for(int i=0;i<wordNum;i++){
    	words[i] = new char[10];
    }
    trie_node *root = create_trie_node();
    for (int i = 0; i<wordNum; ++i){
        cin>>words[i];
        insert_trie_node(root, words[i]);
    }
    cin>>queryNum;
    char **queryWords = new char*[queryNum];
    for(int i=0;i<queryNum;i++){
    	queryWords[i] = new char[10];
    }
    for (int i = 0; i<queryNum; ++i){
        cin>>queryWords[i];
    }

    for (int i = 0; i<queryNum; ++i){
        cout<<query_trie_node(root,queryWords[i])<<endl;
    }


    return 0;
}