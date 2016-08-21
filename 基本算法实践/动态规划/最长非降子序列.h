#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class solution_LIS {
	//4, 5, 7, 8, 3, 2, 6, 7, 33, 4
	stack<int> getLIS(vector<int> nums) {
		vector<int> prev(nums.size(), -1); //指向前面一个数字
		vector<int> dp(nums.size(), 1); //dp[i]表示以i结尾的LIS的长度
		int maxIndex = 0;
		for (unsigned int i = 0; i < nums.size(); i++) {

			for (unsigned int j = 0; j < i; j++) {
				if (nums[i] >= nums[j]) {
					if (dp[i] < dp[j] + 1) {
						dp[i] = dp[j] + 1;
						prev[i] = j;
					}
					if (dp[i] == dp[j] + 1) {
						if (nums[prev[i]] >= nums[j]) {
							dp[i] = dp[j] + 1;
							prev[i] = j;
						}
					}
				}
			}

			if (dp[i] > dp[maxIndex] || dp[i] == dp[maxIndex] && nums[i]<nums[maxIndex]) {
				maxIndex = i;
			}
		}

		int p = maxIndex;
		stack<int> output;
		while (p != -1) {
			output.push(nums[p]);
			p = prev[p];
		}
		return output;
	}

	int func_LIS() {
		vector<int> arr;
		int temp;
		while (cin >> temp) {
			arr.push_back(temp);
			if (cin.get() == '\n') break;
		}
		stack<int> result = getLIS(arr);
		while (!result.empty()) {
			cout << result.top() << " ";
			result.pop();
		}
		return 0;
	}
};
