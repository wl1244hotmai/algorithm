/*

时间限制:1000ms
单点时限:1000ms
内存限制:256MB
描述
小Hi和小Ho准备国庆期间去A国旅游。A国的城际交通比较有特色：它共有n座城市(编号1-n)；城市之间恰好有n-1条公路相连，形成一个树形公路网。小Hi计划从A国首都(1号城市)出发，自驾遍历所有城市，并且经过每一条公路恰好两次——来回各一次——这样公路两旁的景色都不会错过。
令小Hi苦恼的是他的小伙伴小Ho希望能以某种特定的顺序游历其中m个城市。例如按3-2-5的顺序游历这3座城市。(具体来讲是要求：第一次到达3号城市比第一次到达2号城市早，并且第一次到达2号城市比第一次到达5号城市早)。
小Hi想知道是否有一种自驾顺序满足小Ho的要求。
输入
输入第一行是一个整数T(1<=T<=20)，代表测试数据的数量。
每组数据第一行是一个整数n(1 <= n <= 100)，代表城市数目。
之后n-1行每行两个整数a和b (1 <= a, b <= n)，表示ab之间有公路相连。
之后一行包含一个整数m (1 <= m <= n)
最后一行包含m个整数，表示小Ho希望的游历顺序。
输出
YES或者NO，表示是否有一种自驾顺序满足小Ho的要求。
样例输入
2
7
1 2
1 3
2 4
2 5
3 6
3 7
3
3 7 2
7
1 2
1 3
2 4
2 5
3 6
3 7
3
3 2 7
样例输出
YES
NO

*/
#include<iostream>
#include<vector>
#include<bitset>
using namespace std;

struct vertex {
	int id;
	vector<int> connectors;
	bitset<101> reaches;
	bool visited;
	vertex() : id(-1) {};
	vertex(int nid) : id(nid) {};
};
class undirectGraph {
private:
	vector<vertex> vertexs;
	vector<int> order;
	int cnt = 0;
public:
	undirectGraph(int n) { 
		vertexs = vector<vertex>(n+1,vertex());
	}
	undirectGraph() {}
	~undirectGraph() {}
	void resetCntandVisit() {
		cnt = 0;
		for (unsigned int i = 0; i < vertexs.size(); i++) {
			vertexs[i].visited = false;
		}
	}
	void addEdge(int from, int to) {
		vertexs[from].connectors.push_back(to);
		vertexs[to].connectors.push_back(from);
	}
	void addOrder() {
		int order;
		cin >> order;
		this->order.push_back(order);
	}
	void reach_dfs(int cur, int fa) {
		vertexs[cur].reaches[cur] = 1;
		for (unsigned int i = 0; i < vertexs[cur].connectors.size(); i++) {
			int val = vertexs[cur].connectors[i];
			if (val == fa)
				continue;
			reach_dfs(val, cur);
			vertexs[cur].reaches |= vertexs[val].reaches;
		}
	}
	bool solve_dfs(int cur, int fa) {
		if (order[cnt] == cur)
			cnt++;
		if (cnt == order.size())
			return true;
		/** 核心部分 */
		//从根节点(1)的孩子节点开始遍历，查看哪个孩子节点能通向order[0]，如有，则走进该节点，
		//且全局变量cnt++，注意 val == fa的时候代表这个节点是向上的节点，此处只讨论往下走，所以contiune;
		//往上回走的模拟，是采用递归思路，一旦这条路走了一半下面没有了，
		//就从进这条路之前的节点继续选择其他节点往下走，相当于是往下走了之后又往上回头
		/*int temp;
		do {
			temp = cnt;
			for (unsigned int i = 0; i < vertexs[cur].connectors.size(); i++) {
				int val = vertexs[cur].connectors[i];
				if (val == fa)
					continue;
				if (vertexs[val].reaches[order[cnt]] == 1 && !vertexs[val].visited) {
					vertexs[val].visited = true;
					if (solve_dfs(val, cur) == true) return true;
				}
			}
			if (temp == cnt)
				break;
		} while (temp != cnt);*/
		while (cnt<order.size()) {
			int temp = cnt;
			for (unsigned int i = 0; i < vertexs[cur].connectors.size(); i++) {
				int val = vertexs[cur].connectors[i];
				if (val == fa)
					continue;
				if (vertexs[val].reaches[order[cnt]] == 1 && !vertexs[val].visited) {
					vertexs[val].visited = true;
					if (solve_dfs(val, cur) == true) return true;
				}
			}
			if (temp == cnt)
				break;
		}
		return false;
	}
};
int main(int argv, char* argc[]) {
	int T,m;
	cin >> T;
	vector<vector<int> > orders(T);
	vector<undirectGraph> graphs(T);
	int n;
	int x, y;
	for (int i = 0; i < T; i++) {
		cin >> n;
		graphs[i] = undirectGraph(n);
		for (int j = 0; j < n-1; j++) {
			cin >> x >> y;
			graphs[i].addEdge(x, y);
		}
		cin >> m;
		for (int j = 0; j< m; j++) {
			graphs[i].addOrder();
		}
	}

	for (int i = 0; i < T; i++) {
		graphs[i].reach_dfs(1, -1);
		graphs[i].resetCntandVisit();
		if (graphs[i].solve_dfs(1, -1))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}