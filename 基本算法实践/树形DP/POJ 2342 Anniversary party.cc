/**
Description
There is going to be a party to celebrate the 80-th Anniversary of the Ural State University. The University has a hierarchical structure of employees. It means that the supervisor relation forms a tree rooted at the rector V. E. Tretyakov. In order to make the party funny for every one, the rector does not want both an employee and his or her immediate supervisor to be present. The personnel office has evaluated conviviality of each employee, so everyone has some number (rating) attached to him or her. Your task is to make a list of guests with the maximal possible sum of guests' conviviality ratings.
Input
Employees are numbered from 1 to N. A first line of input contains a number N. 1 <= N <= 6 000. Each of the subsequent N lines contains the conviviality rating of the corresponding employee. Conviviality rating is an integer number in a range from -128 to 127. After that go N – 1 lines that describe a supervisor relation tree. Each line of the tree specification has the form: 
L K 
It means that the K-th employee is an immediate supervisor of the L-th employee. Input is ended with the line 
0 0 
Output
Output should contain the maximal sum of guests' ratings.
Sample Input
7
1
1
1
1
1
1
1
1 3
2 3
6 4
7 4
4 5
3 5
0 0
Sample Output
5
*/

#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
#include <cstring>
using namespace std;

#define MAX_RANGE 6001

int w[MAX_RANGE];
int dp[MAX_RANGE][2];
vector<int> g[MAX_RANGE];

/**
 * x: 该人序号；
 * s: 该人状态：0未选，1选中；
 * fa: 父节点；
 */
int get_dp(int x,int s,int fa){
	if(dp[x][s]!=-1)
		return dp[x][s];
	dp[x][s] = 0;
	if(s){
		dp[x][s] = w[x];
		for (size_t i = 0; i < g[x].size(); i++){
			if(g[x][i]!=fa){
				dp[x][s] += get_dp(g[x][i],0,x);
			}
		}
	}else{
		for (size_t i = 0; i < g[x].size(); i++){
			if(g[x][i]!=fa){
				dp[x][s] += max(get_dp(g[x][i],0,x),
				get_dp(g[x][i],1,x));
			}
		}
	}
	return dp[x][s];
}

int main(){
	int N;
	cin>>N;
	memset(dp,-1,sizeof(dp));
	for(int i = 1;i<=N;i++){
		scanf("%d",&w[i]);
	}
	int u,v;
	while(scanf("%d%d",&u,&v),u||v){
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cout<<max(get_dp(1,0,-1),get_dp(1,1,-1));
	return 0;
}