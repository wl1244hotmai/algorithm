#include<iostream>
using namespace std;

int main() {
	int n;
	int height[1000];
	int maxArea = 0;
	int minHeight = 0;
	int maxWidth[10001] = { 0 };
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> height[i];
	}
	for (int i = 0; i < n; i++) {
		minHeight = height[i];
		for (int j = i; j < n; j++) {
			if (height[j] < minHeight) {
				minHeight = height[j];
			}
			maxArea = maxArea >= ((j - i + 1) * minHeight)? maxArea: ((j - i + 1) * minHeight);
		}
	}
	cout << maxArea;
	return 0;
}