#include<iostream>
#include<vector>

using namespace std;
vector<int> getShorestWord(vector<int> array){
	vector<int> temp = array;
	int tmpNum = temp.back();
	temp.pop_back();
	while(temp.size()>0 && tmpNum > temp.back()){
		tmpNum = temp.back();
		temp.pop_back();
	}
	if(temp.size() == 0){
		temp.push_back(1);
	}
	return temp;
}
int main(int argv,char *argc[]){
	int N;
	cin>>N;
	vector<int> array(N);
	for(unsigned int i=0;i<N;i++){
		cin>>array[i];
	}
	vector<int> result = getShorestWord(array);
	for(unsigned int i=0;i<result.size();i++){
		cout<<result[i];
		if(i!=result.size()){
			cout<<" ";
		}
	}
	return 0;
}