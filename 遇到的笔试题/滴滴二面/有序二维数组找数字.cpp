#include<iostream>
#include<vector>

using namespace std;
int n = 5;
int m = 4;

bool search(vector<vector<int> >&arr, int value) {
	int i = 0;
	int j = m - 1;
	while (i >= 0 && j >= 0 && i<n && j<m) {
		//cout<<value<<endl;
		if (arr[i][j] == value) {
			cout << value;
			return true;
		}
		if (arr[i][j]>value) {
			j--;
			if (j<0) {
				j = m;
				i--;
			}
		}
		else {
			i++;
			if (i >= n) {
				i = 0;
				j++;
			}
		}
	}
	return false;
}


int main() {
	int n = 5;
	int m = 4;
	vector<vector<int> > arr(n, vector<int>(m));
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<m; j++) {
			arr[i][j] = i + j;
		}
	}

	for (int i = 0; i<n; i++) {
		for (int j = 0; j<m; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
	int des = 5;
	if (search(arr, des)) { cout << "found"; }
	return 0;
}