/**
* ����
* ���ϻ�˵����СHi��СHo�÷ǳ�׾�ӡ�������˵�ֲڵ��ֶ�ɽկ����һ���������վ�������վ���Լ����ĳ�����˵����й�ͬ�����б�����͵�һ����˭��Զ������������������һЩ����ļ�������˹�������˵������Ϣ�����Ҵ��һ��СС����վ��Ӧ����������˷�������
* �����������������󵽵ġ�������һ���򵥵��㷨������֧��ס�ǳ���ķ����������԰���СHi��СHo��ǰ���޷�����ѡ��
* ��һ�ǹ����Ϊ����ķ�������ͨ����߼�������ܵķ�ʽ���������󡪡���СHi��СHo��û����ô���Ǯ��������ǸĽ����ǵ��㷨��ͨ����߼�������ܵ����������������󡪡���������ƺ����������ӿ��ס�
* ����Ϊ�����ǵ�һ�����߲�Ʒ��˳��������СHi������СHo���н���ѵ�������úõ��޸�һ�����ǵ��㷨��
* ��Ϊ�˸��õ���СHo����������⣬СHi���������������������ӣ�������СHo����֪����N�Ը��ӹ�ϵ�������׺Ͷ��ӵ����֣�������N�Ը��ӹ�ϵ���漰�������˶�ӵ��һ����ͬ�����ȣ�������ȳ�������N�Ը��ӹ�ϵ�У�������Ҫ����СHi�����ɴ����ʡ���ÿ������Ϊ�����˵����֣��������˵�������֮ǰ�ĸ��ӹ�ϵ�г��ֹ���������СHi�������˵����й�ͬ�����б�����͵�һ����˭��
*
* ����
* ÿ�����Ե㣨�����ļ������ҽ���һ��������ݡ�
* ÿ��������ݵĵ�1��Ϊһ������N��������ǰ��������
* ÿ��������ݵĵ�2~N+1�У�ÿ�зֱ�����һ�Ը��ӹ�ϵ�����е�i+1��Ϊ�����ɴ�Сд��ĸ��ɵ��ַ���Father_i, Son_i���ֱ��ʾ���׵����ֺͶ��ӵ����֡�
* ÿ��������ݵĵ�N+2��Ϊһ������M����ʾСHi�ܹ�ѯ�ʵĴ�����
* ÿ��������ݵĵ�N+3~N+M+2�У�ÿ�зֱ�����һ��ѯ�ʣ����е�N+i+2��Ϊ�����ɴ�Сд��ĸ��ɵ��ַ���Name1_i, Name2_i���ֱ��ʾСHiѯ���е��������֡�
* ����100%�����ݣ�����N<=10^5��M<=10^5, �������������漰�������в���������������ͬ���ˣ�������Ψһ��ȷ����һ���ˣ�������ѯ���г��ֹ������־���֮ǰ��������N�Ը��ӹ�ϵ�г��ֹ�����һ�����ֵ�������ȷ�����������������˵Ĺ������ȡ�
* ���
* ����ÿ��������ݣ�����ÿ��СHi��ѯ�ʣ������������г��ֵ�˳�򣬸����һ�У���ʾ��ѯ�Ľ�������ǵ����й�ͬ�����б�����͵�һ���˵����֡�
* ��������
* 4
* Adam Sam
* Sam Joey
* Sam Micheal
* Adam Kevin
* 3
* Sam Sam
* Adam Sam
* Micheal Kevin
* �������
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
	//�õݹ���ʵ�����������ӵ׵��ϵ�һ����£�
	if (node.ancestor != node.name) {
		temp->ancestor = find_LCA(peoples[temp->ancestor]);
	}
	//���ʹ��whileѭ��������ֻ���޸�node��ancestor�������Ͳ���ʵ�����������ĸ����ˣ�
	//�����������ͻᳬʱ��
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