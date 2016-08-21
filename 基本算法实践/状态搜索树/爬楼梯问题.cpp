#include<iostream>
#include<functional>
#include<vector>
#include<deque>
#include<algorithm>
using namespace std;

//n层楼梯,每次往上爬二层，或往下掉一层，一共多少方法爬到楼梯。

class solution_climb_stair {
private:
	int inCount = 0;
public:
	bool checkOnAction(const int& stairs, const int& newState, deque<int>& steps) {
		if (stairs == newState) {
			inCount++;
			return false;
		}
		deque<int>::iterator it = steps.end();
		//check visited
		it = find_if(steps.begin(), steps.end(),bind2nd(equal_to<int>(),newState));
		if (it == steps.end()) {
			steps.push_back(newState);
			return true;
		}
		else
			return false;
	}
	void getChoices(const int& stairs, deque<int> steps) {
		int current = steps.back();
		if (current == stairs) {
			inCount++; 
			return;
		};
		// check valid
		if (current + 2 > stairs && current - 1 < 0)
			return;
		if (current + 2 <= stairs) {
			if (checkOnAction(stairs, current + 2, steps)) {
				getChoices(stairs, steps);
			}
		}
		if (current - 1 >= 0) {
			if (checkOnAction(stairs, current - 1, steps)) {
				getChoices(stairs, steps);
			}
		}
	}
	void func() {
		int stairs;
		cin >> stairs;
		deque<int> steps;
		steps.push_back(0);
		getChoices(stairs, steps);
		cout << inCount;
	}
};