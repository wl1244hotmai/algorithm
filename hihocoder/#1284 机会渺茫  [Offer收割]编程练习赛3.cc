/*
ʱ������:5000ms
����ʱ��:1000ms
�ڴ�����:256MB

����
СHi�����׷��һ��ѧ��ѧ��Ů��СZ��СZ��ʵ����ܾ����ģ������Ҳ����õ�˵�ǣ����������������Ҫ�󣺶��ڸ���������������N��M��СHi���ѡȡһ��N��Լ��N'��СZ���ѡȡһ��M��Լ��M'�����N'��M'��ȣ����ʹ�ӦСHi��
СZ��СHiȥ��д���������򣬵�ʱ����review��û�������˾Ϳ��Գ�ǩ�ˡ�����СHiд��д�ţ�ȴԽ��Խ���û�����ã����ô�������ˣ�СHi�ܹ�׷��СZ�ļ����Ƕ����أ�
����
ÿ�������ļ�����������������ݡ�
ÿ��������ݵĵ�һ��Ϊ����������N��M��������ǰ��������
����40%�����ݣ�����1<=N,M<=106
����100%�����ݣ�����1<=N,M<=1012
���
����ÿ��������ݣ�����������ʵ�������A��B����A��֮B��ʾСHi�ܹ�׷��СZ�ļ��ʣ���
��������
3 2
�������
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