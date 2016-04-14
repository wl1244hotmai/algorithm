//#include<iostream>
//#include<vector>
//#include<fstream>
//using namespace std;
//void displayZ(vector<vector<int> > matrix, int i, int j, int n, int status) {
//	while (i + 1 < n || j + 1 < n) {
//		cout << matrix[i][j]<<" ";
//		switch (status) {
//		case 0:
//			j++;
//			status = 1;
//			break;
//		case 1:
//			if (i + 1 >= n) {
//				j++;
//				status = 2;
//			}
//			else if (j - 1 < 0) {
//				i++;
//				status = 2;
//			}
//			else {
//				i++;
//				j--;
//				status = 1;
//			}
//			break;
//		case 2:
//			if (j + 1 >= n) {
//				i++;
//				status = 1;
//				break;
//			}
//			else if (i - 1 < 0) {
//				j++;
//				status = 1;
//			}
//			else {
//				i--;
//				j++;
//				status = 2;
//			}
//			break;
//		}
//	}
//	cout << matrix[n - 1][n - 1];
//}
//int main(int argv, char* argc[]) {
//	ifstream cin("cin.txt");
//	int n;	
//cin >> n;
//	vector<vector<int> > matrix(n, vector<int>(n));
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			cin >> matrix[i][j];
//		}
//	}
//	displayZ(matrix, 0, 0, n, 0);
//	return 0;
//}