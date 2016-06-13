#include <iostream>
#include <vector>
#include <string>
using namespace std;

/**
 * pre_order: ABDEGHCFIJ;
 * in_order: DBGEHACIJF;
 * so the root is A
 */


string getPostOrder(string pre_order, string in_order) {
	if (pre_order.length() == 0) {
		return "";
	}
	string post_order_str;
	char root = pre_order[0];
	int rootIndex = in_order.find(root);
	post_order_str.insert(post_order_str.begin(), root);
	if (pre_order.length() == 1) {
		return post_order_str;
	}
	string pre_order_child_1 = pre_order.substr(1, rootIndex);
	string in_order_child_1 = in_order.substr(0, rootIndex);
	string pre_order_child_2 = pre_order.substr(rootIndex + 1);
	string in_order_child_2 = pre_order.substr(rootIndex + 1);
	post_order_str.insert(0, getPostOrder(pre_order_child_2, in_order_child_2));
	post_order_str.insert(0, getPostOrder(pre_order_child_1, in_order_child_1));
	return post_order_str;
}

int main(int argv, char* argc[]) {
	string pre_order, in_order;
	cin >> pre_order >> in_order;
	cout << getPostOrder(pre_order, in_order);

	return 0;
}