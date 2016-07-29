//Test case:
//9
//p1 8
//p2 5
//p3 6 p1 p2
//p4 4 p3
//p5 7 p2
//p6 7 p4 p5
//p7 4 p1
//p8 3 p7
//p9 4 p4 p8

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

struct edge {
	// 起点u包含改边引用
	int costTime = 0;
	int desc; //终点v
							 //  活动最早开始时间 eeTime = u.sTime;
							 //  活动最晚开始时间 leTime = v.sTime - costTime;
	edge(int costTime,int desc) {
		this->costTime = costTime;
		this->desc = desc;
	}
};

struct vertex {
	string name;
	int eeTime = 0;
	int leTime = INT_MAX;
	int index = 0;
	int inCount = 0; //入度
	int costTime = 0;
	vector<string> precusorNames;
	vector<edge> edges;
	vertex() {}
	vertex(string _name) {
		this->name = _name;
	}
};

class mycomparison
{
public:
	mycomparison(){}
	bool operator() (const vertex& lhs, const vertex& rhs) const
	{
		return lhs.eeTime > rhs.eeTime;
	}
};

class Graph {
private:
	std::vector<vertex> vertexes;
	std::vector<vertex*> TopoSortedNodes;
	unordered_map<string, int> NameVertexMap;
public:
	Graph() {
		vertexes.push_back(vertex("start"));
		vertexes.push_back(vertex("end"));
	}
	~Graph() {
		vertexes.clear();
		TopoSortedNodes.clear();
		NameVertexMap.clear();
	}

	void InputParameter() {
		{
			int N;
			cin >> N;
			vector<vertex> data(N);
			string lineInput;
			istringstream sin;
			getchar();
			for (int i = 0; i < N; i++) {
				getline(cin, lineInput);
				sin = istringstream(lineInput);
				sin >> data[i].name
					>> data[i].costTime;
				string precusorName;
				while (sin && sin >> precusorName && precusorName != "") {
					data[i].precusorNames.push_back(precusorName);
				}
				NameVertexMap[data[i].name] = i + 1;
			}
			vertexes.insert(vertexes.begin() + 1, data.begin(), data.end());
			for (int i = 1; i < N + 1; i++) {
				if (vertexes[i].precusorNames.size() == 0) {
					vertexes[0].edges.push_back(edge(vertexes[i].costTime, i));
					vertexes[i].inCount++;
				}
				for_each(vertexes[i].precusorNames.begin(),
					vertexes[i].precusorNames.end(),
					[&](string nodeName) {
					vertexes[NameVertexMap[nodeName]].edges.push_back(edge(vertexes[i].costTime, i));
					vertexes[i].inCount++;
				});
			}
			for_each(vertexes.begin() + 1, vertexes.end() - 1, [&](vertex& node) {
				if (node.edges.size() == 0) {
					node.edges.push_back(edge((vertexes.end() - 1)->costTime, vertexes.size() - 1));
					(vertexes.end() - 1)->inCount++;
				}
			});
			int index = 0;
			for_each(vertexes.begin(), vertexes.end(), [&](vertex& node) {
				node.index = index++;
			});
			return;
		}
	}
	void TopoSeque() {
		{
			priority_queue<vertex, vector<vertex>, mycomparison> nodePriorityQueue;
			nodePriorityQueue.push(vertexes[0]);
			while (!nodePriorityQueue.empty()) {
				vertex node = nodePriorityQueue.top();
				TopoSortedNodes.push_back(&vertexes[node.index]);
				nodePriorityQueue.pop();
				for_each(node.edges.begin(), node.edges.end(), [&](edge& edge) {
					vertexes[edge.desc].inCount--;
					vertexes[edge.desc].eeTime = max(vertexes[edge.desc].eeTime, node.eeTime + edge.costTime);
					if (vertexes[edge.desc].inCount == 0) {
						nodePriorityQueue.push(vertexes[edge.desc]);
					}
				});
			}
			return;
		}
	}
	void cal_Path(queue<edge*> edges, vertex* node) {
		//边（活动）的最早开始时间e = eeTime;
		//边（活动）的最晚开始时间l = letime(v) - cost(u,v);
		if (node->edges.size() == 0) {
			while (!edges.empty()) {
				cout << edges.front()->desc<<" ";
				edges.pop();
			}
			cout << endl;
		}

		for_each(node->edges.begin(), node->edges.end(), [&](edge& edge) {
			if (node->eeTime == vertexes[edge.desc].leTime - edge.costTime) {
				//Critical Activity
				edges.push(&edge);
				cal_Path(edges, &vertexes[edge.desc]);
			}
		});
		return;
	}
	void Critical_Path() {
		//调用TopoSeque，
		//Step1: 首先构造拓扑序列，并在构造过程中，
		//Step2: 计算出eeTime;
		//est[0] = 0; est[n] = max{est[i]+cost[i,n],...}
		TopoSeque();
		//Step3: 计算leTime;
		//lst[n] = est[n];
		//lst[i] = min{lst[j] - cost[i,j],...}
		(*(TopoSortedNodes.rbegin()))->leTime = (*(TopoSortedNodes.rbegin()))->eeTime;
		for_each(TopoSortedNodes.rbegin(),
			TopoSortedNodes.rend(),
			[&](vertex* node) {
			for_each(node->edges.begin(), node->edges.end(), [&](edge& edge) {
				node->leTime
					= min(node->leTime, vertexes[edge.desc].eeTime - edge.costTime);
			});
		});
		queue<edge*> result;
		vertex* node = *(TopoSortedNodes.begin());
		cal_Path(result, node);
		return;
	}
};



#endif