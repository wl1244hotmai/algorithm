#include<iostream>
#include<vector>

using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	vector<int> num;
	vector<int>::iterator itor1 = nums1.begin();
	vector<int>::iterator itor2 = nums2.begin();
	while (itor1 != nums1.end() || itor2 != nums2.end()) {
		if (nums1.size() == 0) {
			num = nums2;
			break;
		}
		if (nums2.size() == 0) {
			num = nums1;
			break;
		}
		if (itor1 == nums1.end()) {
			num.push_back(*itor2);
			itor2++;
			continue;
		}
		if (itor2 == nums2.end()) {
			num.push_back(*itor1);
			itor1++;
			continue;
		}
		if (*itor1 > * itor2) {
			num.push_back(*itor2);
			itor2++;
		}
		else if (*itor1 <= *itor2) {
			num.push_back(*itor1);
			itor1++;
		}
	}
	double result;
	int size = num.size();
	if (size % 2 == 1) {
		size /= 2;
		result = num[size];
	}
	else {
		size /= 2;
		result = ((double)num[size - 1] + (double)num[size]) / 2.0;
	}
	return result;
}

int main() {
	vector<int> nums1(2,2);
	vector<int> nums2(2,2);
	nums1[1] = 3;
	cout << findMedianSortedArrays(nums1,nums2);
}