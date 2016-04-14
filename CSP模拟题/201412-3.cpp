#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip> 
#include<algorithm>
using namespace std;

struct operation {
	string action;
	double price;
	int num;
};

int main(int argv, char* argc[]) {
	ifstream cin("cin.txt");
	string tempStr="";
	vector<operation> operations;
	vector<operation> newOperations;
	int cancelIndex=0;
	int buyNum=0;
	int sellNum=0;
	int sumBuyNum = 0;
	int sumSellNum = 0;
	int maxNum=0; // == min(buyNum,sellNum)
	double maxPrice=0;
	while (cin) {
		operation Operation;
		cin >> Operation.action;
		if (Operation.action == "") break;
		if (Operation.action == "cancel") {
			cin >> cancelIndex;
			operations.erase(operations.begin() + cancelIndex - 1);
			continue;
		}
		cin >> Operation.price >> Operation.num;
		operations.push_back(Operation);
	}
	for (vector<operation>::iterator itor = operations.begin(); itor < operations.end();
	itor++) {
		vector<operation>::iterator newItor = newOperations.begin();
		while (newOperations.size()!=0
			&& newItor != newOperations.end()
			&& (*newItor).price < (*itor).price) {
			newItor++;
		}
		newOperations.insert(newItor, *itor);
		if ((*itor).action == "buy") {
			buyNum += (*itor).num;
		}
	}
	maxPrice = newOperations.begin()->price;
	for (vector<operation>::iterator itor = newOperations.begin(); itor < newOperations.end();
	itor++) {
		if (itor+1 == newOperations.end() || (*itor).price < (*(itor + 1)).price) {
			if ((*itor).action == "buy") {
				buyNum -= sumBuyNum;
				buyNum -= (*itor).num;
				sellNum += sumSellNum;
				sumSellNum = 0;
				sumBuyNum = 0;
				if (maxNum <= min(buyNum, sellNum)) {
					maxPrice = (*itor).price;
					maxNum = min(buyNum, sellNum);
				}
			}
			if ((*itor).action == "sell") {
				sellNum += sumSellNum;
				sellNum += (*itor).num;
				buyNum -= sumBuyNum;
				sumBuyNum = 0;
				sumSellNum = 0;
				if (maxNum <= min(buyNum, sellNum)) {
					maxPrice = (*itor).price;
					maxNum = min(buyNum, sellNum);
				}
			}
		}
		else { // (*itor).price == (*(itor + 1)).price
			if ((*itor).action == "buy") {
				sumBuyNum += (*itor).num;
			}
			if ((*itor).action == "sell") {
				sumSellNum += (*itor).num;
			}
		}
	}
	cout << fixed << showpoint;
	cout << setprecision(2)<< maxPrice<<" "<<maxNum;
	//#include <iomanip> 
	//setprecision(n) 输出n位精度（setprecision(3) 1.1111 -> 1.11)
	return 0;
}