#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

struct line {
	int x1, y1, x2, y2;
};
struct point {
	int x, y;
	bool operator==(point p2) {
		return (this->x == p2.x && this->y == p2.y);
	}
};
struct rectangle {
	vector<line> lines = vector<line>(4);
};
bool isRectangle(rectangle this_rectangle) {
	point temp;
	vector<point> points;
	for (int i = 0; i < 4; i++) {
		temp.x = this_rectangle.lines[i].x1;
		temp.y = this_rectangle.lines[i].y1;
		if (find(points.begin(),points.end(),temp) == points.end()) {
			points.push_back(temp);
		}
		temp.x = this_rectangle.lines[i].x2;
		temp.y = this_rectangle.lines[i].y2;
		if (find(points.begin(), points.end(), temp) == points.end()) {
			points.push_back(temp);
		}
	}
	if (points.size() != 4) return false;
	line f_line = this_rectangle.lines[0];
	for (int i = 1; i < 4; i++) {
		line other_line = this_rectangle.lines[i];
		if ((other_line.y2 - other_line.y1)*(f_line.x2 - f_line.x1) - (other_line.x2 - other_line.x1)*(f_line.y2 - f_line.y1) != 0
			&& (other_line.y2 - other_line.y1)*(f_line.y2 - f_line.y1) + (other_line.x2 - other_line.x1)*(f_line.x2 - f_line.x1) != 0) {
			return false;
		}
	}
	return true;
}
int main(int argv, char* argc[]) {
	int T;
	cin >> T;
	vector<rectangle> rectangles(T);
	for (int i = 0; i < T; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> rectangles[i].lines[j].x1
				>> rectangles[i].lines[j].y1
				>> rectangles[i].lines[j].x2
				>> rectangles[i].lines[j].y2;
		}
	}
	for (int i = 0; i < T; i++) {
		if (isRectangle(rectangles[i]))
			cout << "YES"<<endl;
		else
			cout << "NO"<<endl;
	}
	return 0;
}