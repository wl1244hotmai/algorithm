#include <unordered_map>
#include <iostream>

using namespace std;
struct LRUCache_Node {
	int key;
	int value;
	LRUCache_Node* left;
	LRUCache_Node* right;
	LRUCache_Node() {}
	LRUCache_Node(int key, int value, LRUCache_Node* left, LRUCache_Node* right) {
		this->key = key;
		this->value = value;
		this->left = left;
		this->right = right;
	}
};
/**
* 当我们通过键值来访问类型为T的数据时，调用Get函数。如果键值为key的数据已经在
* Cache中，那就返回该数据，同时将存储该数据的结点移到双向链表头部。
* 如果我们查询的数据不在Cache中，我们就可以通过Put接口将数据插入双向链表中。 如果此时的Cache还没满，那么我们将新结点插入到链表头部，
* 同时用哈希表保存结点的键值及结点地址对。如果Cache已经满了， 我们就将链表中的最后一个结点(注意不是尾结点)的内容替换为新内容，
* 然后移动到头部，更新哈希表。
**/
class LRUCache {
private:
	unordered_map <int, LRUCache_Node> nodesMap;
	unordered_map <int, LRUCache_Node>::iterator it;
	LRUCache_Node *head, *tail;
	unsigned int capacity;
public:
	LRUCache(int capacity) {
		this->capacity = capacity;
		head = new LRUCache_Node(0, 0, NULL, NULL);
		tail = new LRUCache_Node(0, 0, NULL, NULL);
		head->right = tail;
		tail->left = head;
	}
	~LRUCache() { delete head; delete tail; }

	int get(int key) {
		it = nodesMap.find(key);
		if (it == nodesMap.end()) {
			return -1;
		}
		else {
			LRUCache_Node* found_node = &it->second;
			found_node->left->right = found_node->right;
			found_node->right->left = found_node->left;
			LRUCache_Node* temp = head->right;
			head->right = found_node;
			found_node->left = head;
			temp->left = found_node;
			found_node->right = temp;
			return it->second.value;
		}
	}

	void set(int key, int value) {
		if (get(key) != -1) {
			it->second.value = value;
		}
		else {
			nodesMap[key] = LRUCache_Node(key, value, NULL, NULL);
			if (nodesMap.size() > capacity) {
				LRUCache_Node* temp = tail->left;
				temp->left->right = tail;
				tail->left = temp->left;
				temp->left = NULL;
				temp->right = NULL;
				nodesMap.erase(temp->key);
			}
			LRUCache_Node* temp = head->right;
			head->right = &nodesMap[key];
			head->right->left = head;
			temp->left = head->right;
			head->right->right = temp;
		}

	}
};


int main() {
	LRUCache lru_cache(1);
	lru_cache.set(2, 1);
	cout<<lru_cache.get(2);
	lru_cache.set(3, 2);
	cout << lru_cache.get(2);
	cout << lru_cache.get(3);
	return 0;
}