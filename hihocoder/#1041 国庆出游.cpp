/*

ʱ������:1000ms
����ʱ��:1000ms
�ڴ�����:256MB
����
СHi��СHo׼�������ڼ�ȥA�����Ρ�A���ĳǼʽ�ͨ�Ƚ�����ɫ��������n������(���1-n)������֮��ǡ����n-1����·�������γ�һ�����ι�·����СHi�ƻ���A���׶�(1�ų���)�������Լݱ������г��У����Ҿ���ÿһ����·ǡ�����Ρ������ظ�һ�Ρ���������·���Եľ�ɫ����������
��СHi���յ�������С���СHoϣ������ĳ���ض���˳����������m�����С����簴3-2-5��˳��������3�����С�(����������Ҫ�󣺵�һ�ε���3�ų��бȵ�һ�ε���2�ų����磬���ҵ�һ�ε���2�ų��бȵ�һ�ε���5�ų�����)��
СHi��֪���Ƿ���һ���Լ�˳������СHo��Ҫ��
����
�����һ����һ������T(1<=T<=20)������������ݵ�������
ÿ�����ݵ�һ����һ������n(1 <= n <= 100)�����������Ŀ��
֮��n-1��ÿ����������a��b (1 <= a, b <= n)����ʾab֮���й�·������
֮��һ�а���һ������m (1 <= m <= n)
���һ�а���m����������ʾСHoϣ��������˳��
���
YES����NO����ʾ�Ƿ���һ���Լ�˳������СHo��Ҫ��
��������
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
�������
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
		/** ���Ĳ��� */
		//�Ӹ��ڵ�(1)�ĺ��ӽڵ㿪ʼ�������鿴�ĸ����ӽڵ���ͨ��order[0]�����У����߽��ýڵ㣬
		//��ȫ�ֱ���cnt++��ע�� val == fa��ʱ���������ڵ������ϵĽڵ㣬�˴�ֻ���������ߣ�����contiune;
		//���ϻ��ߵ�ģ�⣬�ǲ��õݹ�˼·��һ������·����һ������û���ˣ�
		//�ʹӽ�����·֮ǰ�Ľڵ����ѡ�������ڵ������ߣ��൱������������֮�������ϻ�ͷ
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