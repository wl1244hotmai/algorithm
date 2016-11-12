/*
问题描述：对于给定的整数N找到一个整数M，使得N*M中只含有0与1
解法：假设N = 6
		  1
	   /     \
	 10       11
	/  \     /  \
  100  101  110 111

  初始化dp[1] = {0}; 即1被任何大于1的N除，都余1；
  接着从10^i开始，10^i mod 6 = 4;
  如果dp[4] 为空，则赋值；不为空则不处理，保留之前最小的那个数（此处就是10）；
  然后利用 (X+Y)%N = ( (X%N) + (Y%N) ) % N；
  遍历当前dp[k]不为空，对应dp[(k+j)%N]为空,并且此时i大于dp[k]最大位，就可以更新dp[(k+j)%N]
*/
#include<vector>
#include<iostream>

using namespace std;

void printVec(const vector<int> &vec)
{
	int temp = -1;
	for (int i = vec.size() - 1; i >= 0; i--) {//高次幂决定1的位置
		cout << "1";
		temp = vec[i];
		while (i>0 && --temp != vec[i - 1])//防止越界，弹出循环时下标指向第一个元素
			cout << "0";
	}
	while (temp--)
		cout << "0";
	cout << endl;
}
void findInt(int N)
{
	int M = -1;
	vector<vector<int>>BigInt;
	for (int i = 0; i<N; i++) {//初始化BigInt二维数组
		vector<int> temp;
		temp.clear();
		BigInt.push_back(temp);
	}
	BigInt[1].push_back(0);//10^0=1,1对任何正整数数取余都等于1,接下来最小符合条件正整数从10开始
	int i, j;
	int noUpdate = 0;
	for (i = 1, j = 10 % N; ; i++, j = (j * 10) % N) {//开始从10^1遍历，i表示10的幂次位数，j表示当前幂次对N的取余信息
		bool updateFlag = false;
		if (BigInt[j].size() == 0) {//初始化
			updateFlag = true;
			BigInt[j].clear();
			BigInt[j].push_back(i);
		}
		/**核心代码**/
		for (int k = 0; k<BigInt.size(); k++) {//遍历所有计数数组
			if (BigInt[k].size()>0 && BigInt[(j + k) % N].size() == 0 && i>BigInt[k][BigInt[k].size() - 1]) {//更新条件,注意最后一个条件的含义在于从10跳到100而不是跳到20
				updateFlag = true;
				BigInt[(j + k) % N] = BigInt[k];
				BigInt[(j + k) % N].push_back(i);
			}
		}
		//循环迭代N次都没有计数数组的数据被更新，说明无解；或是BigInt[0].size()>0找到了解，跳出循环
		if (updateFlag == false)//每一轮迭代，只要没有更新数据就计数加1
			noUpdate++;
		if (noUpdate == N || BigInt[0].size()>0) {
			break;
		}
	}
	if (BigInt[0].size() > 0) {//找到解
		printVec(BigInt[0]);
		return;
	}
	else {
		cerr << "M not exit !" << endl;
		return;
	}
}

int main()
{
	findInt(6);
	return 0;
}
