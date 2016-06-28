#include "图的邻接矩阵实现.h"

Graph::Graph(int v) {
	vertexs = vector<string>(v, "");
	edgeMatrix = vector<vector<int> >(v, vector<int>(v, MAX_VALUE));
}

void Graph::insertVertex(int num, string vertex)
{
	vertexs[num] = vertex;
}

void Graph::insertEdge(int src, int desc, int weight) {
	edgeMatrix[src][desc] = weight;
}

queue<int> Graph::ShortestPath(int src, int desc) {
	queue<int> ShortestPath;
	//初始化 
	vector<int> Shortest_Path_Length(vertexs.size(), MAX_VALUE);
	vector<bool> unvisited(vertexs.size(), true);
	Shortest_Path_Length[0] = 0;
	int this_time_visit = 0;
	int next_time_visit = 0;
	vector<int> this_edge;
	while (find(unvisited.begin(), unvisited.end(),true) != unvisited.end()) {
		this_time_visit = next_time_visit;
		this_edge = edgeMatrix[this_time_visit];
		unvisited[this_time_visit] = false;
		int ShortestEdge = MAX_VALUE;
		for (unsigned int i = 0; i < this_edge.size();i++) {
			//松弛
			if (this_edge[i] != MAX_VALUE) {
				if (Shortest_Path_Length[this_time_visit] + this_edge[i] < Shortest_Path_Length[i]) {
					Shortest_Path_Length[i] = Shortest_Path_Length[this_time_visit] + this_edge[i];
				}
				if (Shortest_Path_Length[i] < ShortestEdge) {
					next_time_visit = i;
					ShortestEdge = Shortest_Path_Length[i];
				}
			}				
		}
	}
	return ShortestPath;
}
