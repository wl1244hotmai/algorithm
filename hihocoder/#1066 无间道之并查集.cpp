#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;

map<string, string> represents;

string find(string& name) {
	string x = name;
	while (represents[x].compare(x)) {
		x = represents[x];
	}
	represents[name] = x;
	return x;
}

int main() {
	int N;
	cin >> N;
	int op;
	string name_1, name_2;
	for (int i = 0; i < N; i++) {
		cin >> op >> name_1 >> name_2;
		if (represents.find(name_1) == represents.end()) {
			represents[name_1] = name_1;
		}
		if (represents.find(name_2) == represents.end()) {
			represents[name_2] = name_2;
		}
		if (op) {
			cout << (find(name_1).compare(find(name_2)) == 0 ? "yes" : "no")<<endl;
		}
		else {
			
			string A = find(name_1),
				B = find(name_2);
			if (A.compare(B)!=0) {
				represents[A] = B;
			}
		}
	}

	return 0;
}