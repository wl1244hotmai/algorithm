#include<iostream>
#include<vector>
#include<string>

#include"图的邻接矩阵实现.h"

using namespace std;

int main(int argv, char* argc[]) {
	cout << "input number of vertexs ";
	int n;
	string tempVertexString;
	cin >> n;
	Graph mGraph = Graph(n);
	for (int i = 0; i < n; i++) {
		cout << "input vertex ";
		cin>>tempVertexString;
		mGraph.insertVertex(i, tempVertexString);
	}
	cout << "input number of edges ";
	int e;
	cin >> e;
	for (int i = 0; i < e; i++) {
		cout << "input src desc and weight ";
		int src, desc, weight;
		cin >> src >> desc >> weight;
		mGraph.insertEdge(src, desc, weight);
	}
	cout << "input shotest path of src and desc ";
	int src, desc;
	cin >> src >> desc;
	mGraph.ShortestPath(src, desc);

	return 0;
}