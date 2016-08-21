/**
Description
Farmer John completed his new barn just last week, complete with all the latest milking technology.Unfortunately, due to engineering problems, all the stalls in the new barn are different.For the first week, Farmer John randomly assigned cows to stalls, but it quickly became clear that any given cow was only willing to produce milk in certain stalls.For the last week, Farmer John has been collecting data on which cows are willing to produce milk in which stalls.A stall may be only assigned to one cow, and, of course, a cow may be only assigned to one stall.
Given the preferences of the cows, compute the maximum number of milk - producing assignments of cows to stalls that is possible.
Input
The input includes several cases.For each case, the first line contains two integers, N(0 <= N <= 200) and M(0 <= M <= 200).N is the number of cows that Farmer John has and M is the number of stalls in the new barn.Each of the following N lines corresponds to a single cow.The first integer(Si) on the line is the number of stalls that the cow is willing to produce milk in(0 <= Si <= M).The subsequent Si integers on that line are the stalls in which that cow is willing to produce milk.The stall numbers will be integers in the range(1..M), and no stall will be listed twice for a given cow.
Output
For each case, output a single line with a single integer, the maximum number of milk - producing stall assignments that can be made.
Sample Input
5 5
2 2 5
3 2 3 4
2 1 5
3 1 2 5
1 2
Sample Output
4
Source
*/

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<iomanip>
#define loop(n) for(int i=0;i<n;i++)
using namespace std;

class solution_hungary_match {
public:
	struct GRAPH_MATCH {
		int n;
		int** edge;
		bool *onPath;
		int *path;
		int max_match;
		GRAPH_MATCH(int n) {
			this->n = n;
			edge = new int*[n];
			loop(n) {
				edge[i] = new int[n];
				memset(edge[i], -1, sizeof(int)*n);
			}
			onPath = new bool[n];
			path = new int[n];

			memset(onPath, 0, sizeof(bool)*n);
			memset(path, -1, sizeof(int)*n);

			max_match = 0;
		}
		~GRAPH_MATCH() {
			loop(this->n) {
				delete[]edge[i];
			}
			delete[]edge;
			delete[]onPath;
			delete[]path;
		}
		void clearOnPathSign() {
			memset(onPath, 0, sizeof(bool)*n);
		}
	};

	bool findAugmentPath(GRAPH_MATCH *pMatch, int xi) {
		for (int yj = 0; yj < pMatch->n; yj++) {
			if (pMatch->edge[xi][yj] == 1 && !pMatch->onPath[yj]) {
				pMatch->onPath[yj] = true;
				if (pMatch->path[yj] == -1 || findAugmentPath(pMatch, pMatch->path[yj])) {
					pMatch->path[yj] = xi;
					return true;
				}
			}
		}
		return false;
	}

	bool Hungary_Match(GRAPH_MATCH* pMatch) {
		for (int xi = 0; xi < pMatch->n; xi++) {
			if (findAugmentPath(pMatch, xi)) {
				pMatch->max_match++;
			}
			pMatch->clearOnPathSign();
		}
		return (pMatch->max_match == pMatch->n);
	}

	void func() {
		int n;
		cin >> n;
		GRAPH_MATCH graph_path(n);
		getchar();
		loop(n) {
			string input;
			int temp;
			getline(cin, input);
			istringstream is(input);
			while (is) {
				is >> temp;
				graph_path.edge[i][temp - 1] = 1;
			}
		}
		cout << Hungary_Match(&graph_path) ? "完美匹配" : "没有完美匹配";
		int *path = new int[n];
		loop(n) {
			path[graph_path.path[i]] = i;
		}
		loop(n) {
			cout << i << setw(6) << path[i] << endl;
		}
		return;
	}
};
