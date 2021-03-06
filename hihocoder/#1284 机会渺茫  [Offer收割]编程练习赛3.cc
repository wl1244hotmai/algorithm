/*
时间限制:5000ms
单点时限:1000ms
内存限制:256MB

描述
小Hi最近在追求一名学数学的女生小Z。小Z其实是想拒绝他的，但是找不到好的说辞，于是提出了这样的要求：对于给定的两个正整数N和M，小Hi随机选取一个N的约数N'，小Z随机选取一个M的约数M'，如果N'和M'相等，她就答应小Hi。
小Z让小Hi去编写这个随机程序，到时候她review过没有问题了就可以抽签了。但是小Hi写着写着，却越来越觉得机会渺茫。那么问题来了，小Hi能够追到小Z的几率是多少呢？
输入
每个输入文件仅包含单组测试数据。
每组测试数据的第一行为两个正整数N和M，意义如前文所述。
对于40%的数据，满足1<=N,M<=106
对于100%的数据，满足1<=N,M<=1012
输出
对于每组测试数据，输出两个互质的正整数A和B（以A分之B表示小Hi能够追到小Z的几率）。
样例输入
3 2
样例输出
4 1

*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int Gcd(int a, int b)
{
    if(b == 0)
        return a;
    return Gcd(b, a % b);
}
int main(int argv,char *argc[]){
	long long int m,n;
	cin>>m>>n;
	long long int sqrtM = sqrt(m),sqrtN = sqrt(n);
	vector<long long int> divisorM;
	vector<long long int> divisorN;
	for(int i=1;i<=sqrtM;i++){
		if(m%i==0){
				divisorM.push_back(i);
				divisorM.push_back(m/i);
		}
	}
	for(int i=1;i<=sqrtN;i++){
		if(n%i==0){
				divisorN.push_back(i);
				divisorN.push_back(n/i);
		}
	}
	int count =0;
	int max = divisorM.size() * divisorN.size();
	for(unsigned int i=0;i<divisorM.size();i++){
		for(unsigned int j=0;j<divisorN.size();j++){
			if(divisorM[i] == divisorN[j]){
				count++;
				break;
			}
		}
	}
	cout<<max/Gcd(max,count)<<" "<<count/Gcd(max,count);
	return 0;
}