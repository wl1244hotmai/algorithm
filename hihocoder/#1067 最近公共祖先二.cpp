/**
* 描述
* 上上回说到，小Hi和小Ho用非常拙劣——或者说粗糙的手段山寨出了一个神奇的网站，这个网站可以计算出某两个人的所有共同祖先中辈分最低的一个是谁。远在美国的他们利用了一些奇妙的技术获得了国内许多人的相关信息，并且搭建了一个小小的网站来应付来自四面八方的请求。
* 但正如我们所能想象到的……这样一个简单的算法并不能支撑住非常大的访问量，所以摆在小Hi和小Ho面前的无非两种选择：
* 其一是购买更为昂贵的服务器，通过提高计算机性能的方式来满足需求——但小Hi和小Ho并没有那么多的钱；其二则是改进他们的算法，通过提高计算机性能的利用率来满足需求——这个主意似乎听起来更加靠谱。
* 于是为了他们第一个在线产品的顺利运作，小Hi决定对小Ho进行紧急训练——好好的修改一番他们的算法。
* 而为了更好的向小Ho讲述这个问题，小Hi将这个问题抽象成了这个样子：假设现小Ho现在知道了N对父子关系——父亲和儿子的名字，并且这N对父子关系中涉及的所有人都拥有一个共同的祖先（这个祖先出现在这N对父子关系中），他需要对于小Hi的若干次提问——每次提问为两个人的名字（这两个人的名字在之前的父子关系中出现过），告诉小Hi这两个人的所有共同祖先中辈分最低的一个是谁？
*
* 输入
* 每个测试点（输入文件）有且仅有一组测试数据。
* 每组测试数据的第1行为一个整数N，意义如前文所述。
* 每组测试数据的第2~N+1行，每行分别描述一对父子关系，其中第i+1行为两个由大小写字母组成的字符串Father_i, Son_i，分别表示父亲的名字和儿子的名字。
* 每组测试数据的第N+2行为一个整数M，表示小Hi总共询问的次数。
* 每组测试数据的第N+3~N+M+2行，每行分别描述一个询问，其中第N+i+2行为两个由大小写字母组成的字符串Name1_i, Name2_i，分别表示小Hi询问中的两个名字。
* 对于100%的数据，满足N<=10^5，M<=10^5, 且数据中所有涉及的人物中不存在两个名字相同的人（即姓名唯一的确定了一个人），所有询问中出现过的名字均在之前所描述的N对父子关系中出现过，第一个出现的名字所确定的人是其他所有人的公共祖先。
* 输出
* 对于每组测试数据，对于每个小Hi的询问，按照在输入中出现的顺序，各输出一行，表示查询的结果：他们的所有共同祖先中辈分最低的一个人的名字。
* 样例输入
* 4
* Adam Sam
* Sam Joey
* Sam Micheal
* Adam Kevin
* 3
* Sam Sam
* Adam Sam
* Micheal Kevin
* 样例输出
* Sam
* Adam
* Adam
*/

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<algorithm>

using namespace std;

enum Status{
	white, gray, black
};

struct people {
	string name = "";
	vector<people*> children;
	string ancestor;
	Status status = Status::white;
};

struct query {
	string name;
	string LCA;
};

int N, M;
people* root;
unordered_map<string,people> peoples;
vector<query> q1, q2;
unordered_map<string, vector<query*> > queries;

string find_LCA(people& node) {
	people* temp = &node;
	//用递归来实现整个子树从底到上的一起更新！
	if (node.ancestor != node.name) {
		temp->ancestor = find_LCA(peoples[temp->ancestor]);
	}
	//如果使用while循环来做，只能修改node的ancestor，这样就不能实现整个子树的更新了，
	//大批量操作就会超时！
	return temp->ancestor;
}

void dfs(people* node,people* parent) {
	node->status = Status::gray;
	node->ancestor = node->name;

	if (queries.find(node->name) != queries.end()) {
		for_each(queries[node->name].begin(), queries[node->name].end(),
			[&](query* q) {
			switch (peoples[q->name].status) {
			case Status::white:
				break;
			case Status::gray:
				q->LCA = q->name;
				break;
			case Status::black:
				q->LCA = find_LCA(peoples[q->name]);
				break;
			}
		});
	}

	for_each(node->children.begin(),node->children.end(),
		[&](people* child) {
		dfs(child,node);
	});

	node->ancestor = parent->name;
	node->status = Status::black;
}

void init() {

	cin >> N;
	string name_1, name_2;
	for (int i = 0; i < N; i++) {
		cin >> name_1 >> name_2;
		if (peoples.find(name_1) == peoples.end()) {
			peoples[name_1].name = name_1;
		}
		peoples[name_2].name = name_2;
		peoples[name_1].children.push_back(&peoples[name_2]);
		if (i == 0) {
			root = &peoples[name_1];
		}
	}
	cin >> M;
	q1.assign(M, query());
	q2.assign(M, query());
	for (int i = 0; i < M; i++) {
		cin >> name_1 >> name_2;
		q1[i].name = name_2;
		q2[i].name = name_1;
		queries[name_1].push_back(&q1[i]);
		queries[name_2].push_back(&q2[i]);
	}
	
}

void display() {
	for (int i = 0; i < M; i++) {
		if (q1[i].LCA != "")
			cout << q1[i].LCA << endl;
		else
			cout << q2[i].LCA << endl;
	}
}

int main(int argv, char* arc[]) {
	init();
	dfs(root, root);
	display();
	return 0;
}