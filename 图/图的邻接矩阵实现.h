#include<iostream>
#include<vector>
#include<queue>

#ifndef MaxValue
#define MAX_VALUE 10000
#endif

using namespace std;

class Graph {
private:
	vector<string> vertexs;
	vector<vector<int> > edgeMatrix;
	
public:
	Graph(int vertexsNum);
	void insertVertex(int num, string vertex);
	void insertEdge(int src, int desc, int weight);
	queue<int> ShortestPath(int src, int desc);
};
