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
* ������ͨ����ֵ����������ΪT������ʱ������Get�����������ֵΪkey�������Ѿ���
* Cache�У��Ǿͷ��ظ����ݣ�ͬʱ���洢�����ݵĽ���Ƶ�˫������ͷ����
* ������ǲ�ѯ�����ݲ���Cache�У����ǾͿ���ͨ��Put�ӿڽ����ݲ���˫�������С� �����ʱ��Cache��û������ô���ǽ��½����뵽����ͷ����
* ͬʱ�ù�ϣ������ļ�ֵ������ַ�ԡ����Cache�Ѿ����ˣ� ���Ǿͽ������е����һ�����(ע�ⲻ��β���)�������滻Ϊ�����ݣ�
* Ȼ���ƶ���ͷ�������¹�ϣ��
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