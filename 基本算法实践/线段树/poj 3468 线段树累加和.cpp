/**
* Description
* You have N integers, A1, A2, ... , AN. You need to deal with two kinds of operations. One type of operation is to add some given number to each number in a given interval. The other is to ask for the sum of numbers in a given interval.
* Input
* The first line contains two numbers N and Q. 1 ≤ N,Q ≤ 100000.
* The second line contains N numbers, the initial values of A1, A2, ... , AN. -1000000000 ≤ Ai ≤ 1000000000.
* Each of the next Q lines represents an operation.
* "C a b c" means adding c to each of Aa, Aa+1, ... , Ab. -10000 ≤ c ≤ 10000.
* "Q a b" means querying the sum of Aa, Aa+1, ... , Ab.
* Output
* You need to answer all Q commands in order. One answer in a line.
* Sample Input
* 10 5
* 1 2 3 4 5 6 7 8 9 10
* Q 4 4
* Q 1 10
* Q 2 4
* C 3 6 3
* Q 2 4
* Sample Output
* 4
* 55
* 9
* 15
* Hint
* The sums may exceed the range of 32-bit integers.
**/

#include<vector>
#include<iostream>
#include<algorithm>
#include<cmath>
#define leftChild rt << 1, l, m
#define rightChild rt << 1 | 1, m + 1, r

using namespace std;

//原题 http://poj.org/problem?id=3468
//课件 http://acm.pku.edu.cn/summerschool/gw_interval_tree.pdf
//维基 https://zh.wikipedia.org/wiki/%E7%BA%BF%E6%AE%B5%E6%A0%91
class POJ_3468 {
private:
	vector<long long int> tree;
	vector<long long int> lazy;
	int N, Q; //N是数字个数，Q是操作个数

	void push_up(int rt) {
		tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
	}

	void push_down(int rt, int l, int r) {
		int length = r - l + 1;
		lazy[rt << 1] += lazy[rt];
		tree[rt << 1] += lazy[rt] * (length - (length >> 1));
		lazy[rt << 1 | 1] += lazy[rt];
		tree[rt << 1 | 1] += lazy[rt] * (length >> 1);
		lazy[rt] = 0;
	}

	void buildTree(int rt, int l, int r) {
		int m = (l + r) >> 1;
		if (l == r) {
			cin >> tree[rt];
			return;
		}
		buildTree(leftChild);
		buildTree(rightChild);
		push_up(rt);
	}

	//L,R表示批量添加的线段的范围；l,r表示当前节点表示的线段范围，两者进行比较匹配
	void add(int L, int R, long long delta, int rt, int l, int r) {
		if (L <= l && r <= R) {
			tree[rt] += (r - l + 1)*delta;
			lazy[rt] += delta;
			return;
		}
		if (lazy[rt]) {
			push_down(rt, l, r);
		}
		int m = (l + r) >> 1;
		if (L <= m) add(L, R, delta, leftChild);
		if (R > m) add(L, R, delta, rightChild);
		push_up(rt);
	}

	long long query(int L, int R, int rt, int l, int r) {
		if (L <= l && r <= R)
			return tree[rt];
		if (lazy[rt])
			push_down(rt, l, r);
		int m = (l + r) >> 1;
		long long ret = 0;
		if (L <= m) ret += query(L, R, leftChild);
		if (R > m) ret += query(L, R, rightChild);
		return ret;
	}

public:
	POJ_3468() {}
	void init() {
		cin >> N >> Q;
		int TreeHeight = (int)ceil(log2(N)) + 1;
		int assignNum = (int)pow(2, TreeHeight);
		tree.assign(assignNum, 0);
		lazy.assign(assignNum, 0);
		buildTree(1, 1, N);
	}
	void enter() {
		char cmd;
		int L, R, v;
		for (int i = 0; i < Q; i++) {
			cin >> cmd;
			if (cmd == 'C') {
				cin >> L >> R >> v;
				add(L, R, v, 1, 1, N);
			}
			else {
				cin >> L >> R;
				cout << query(L, R, 1, 1, N) << endl;
			}
		}
	}
};

int main() {
	POJ_3468 poj_3468;
	poj_3468.init();
	poj_3468.enter();
	return 0;
}