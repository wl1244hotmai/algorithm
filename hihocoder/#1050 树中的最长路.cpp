/**
ʱ������:10000ms
����ʱ��:1000ms
�ڴ�����:256MB
����
�ϻ�˵����СHo�õ���һ�ö�������ߣ�����������С���ľ�����������ģ����ڲ�ƴ���Ĺ����У�СHo����������������ƴ�ճ�һ�ö�������������ƴ�ճ�һ�ö���������ðɣ���ʵ���Ǹ�Ϊƽ���������ѡ�
���ǲ�����ô˵��СHoϲ������������������ˣ����������Ӱ������֣���ʵ˵����С���ľ����ʲô������ǰ�= =����СHo���е���������������N��С���N-1��ľ��ƴ�ն��ɣ���N��С�򶼱�СHo�����˲�ͬ�����֣�������Щ���ֶ��ǳ���1..N�ķ�Χ֮�ڣ�ÿ��ľ����������������ͬ��С�򣬲��ұ�֤��������С��䶼������������ͬ��·�����Ի��ൽ��ܶ���֮����һ���൱������������
����СHi�Ƽ�СHo������ӣ������������������в�����һ�����£�����Ѱ˼�����ҵ�����������˼��˼������������СHi��ˮ׼����Ȼ���ֵ���������
��������ʳ���緹��СHi������������������Ĳ����ֺ���СHo��������˵������������������Ҿ�����һ�����⣬������ɷ�֪������
�����ã���СHo�붼����ľܾ��ˡ�
������ͼ�����ɣ�һ��ع���ʱ���Ҳ���������~��СHi�������
������������˵��˵���������ء���һ��ϰ���ڿ�������ģʽ��СHo�̲�ס�ˣ����Ϻ�����
СHi����ĵ��˵�ͷ���漴˵��������Ŷ���ҵ�����ܼ򵥣����ǡ���������������������֮��ľ��������Ȼ������ľ�����ָ��һ������ߵ���һ����㾭����ľ���������� 
��������СHo��ͷ���˿������������������ˡ�
��ʾһ��·�����۵㣬·��Ҳ�����⣡   
����
ÿ�����Ե㣨�����ļ������ҽ���һ��������ݡ�
ÿ��������ݵĵ�һ��Ϊһ������N��������ǰ��������
ÿ��������ݵĵ�2~N�У�ÿ�зֱ�����һ��ľ�������е�i+1��Ϊ��������Ai��Bi����ʾ��i��ľ�����ӵ�����С��ı�š�
����20%�����ݣ�����N<=10��
����50%�����ݣ�����N<=10^3��
����100%�����ݣ�����N<=10^5��1<=Ai<=N, 1<=Bi<=N
СHi��Tip����Щ������洢���ߵļǵ�Ҫ��������СŶ��
���
����ÿ��������ݣ����һ������Ans����ʾ������������о�����Զ���������֮������ľ��롣
��������
8
1 2
1 3
1 4
4 5
3 6
6 7
7 8
�������
6
*/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
private:
	struct node {
		pair<int, int> childMax;
		vector<node*> childs;
	};
	void getMinTwoDistance(node* pNode,node* parent) {
		if (pNode->childs.size() == 1 && pNode->childs[0] == parent) return;

		for (node* childNode : pNode->childs) {
			if (parent!=NULL && parent == childNode) continue;
			getMinTwoDistance(childNode,pNode);
			int distance = childNode->childMax.first + 1;
			if (distance > pNode->childMax.first) {
				//��ԭ����first����second���
				pNode->childMax.second = pNode->childMax.first;
				pNode->childMax.first = distance;
			}
			else if (distance > pNode->childMax.second) {
				pNode->childMax.second = distance;
			}
		}
		return;
	}
public:
	int maxDistance(int nodeNum, vector<pair<int, int> > &edges) {
		vector<node> nodes(nodeNum);
		node* root;
		for (int i = 0; i < nodeNum - 1; i++) {
			nodes[edges[i].first - 1].childs.push_back(&nodes[edges[i].second - 1]);
			nodes[edges[i].second - 1].childs.push_back(&nodes[edges[i].first - 1]);
		}

		root = &nodes[0];

		getMinTwoDistance(root,NULL);
	
		int minDistance = 0;
		for (node this_node : nodes) {
			int sum = this_node.childMax.first + this_node.childMax.second;
			minDistance = minDistance < sum ? sum : minDistance;
		}
		
		return minDistance;
	}
};

int main(int argv, char* argc[]) {
	int n;
	pair<int, int> edge;
	vector<pair<int, int> > edges;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> edge.first >> edge.second;
		edges.push_back(edge);
	}
	cout << Solution().maxDistance(n, edges);
	return 0;
}