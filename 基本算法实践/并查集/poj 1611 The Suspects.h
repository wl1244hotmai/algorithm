/**
��*	�кܶ���ѧ������ͬһ�����ѧ��������Ӵ���Ҳ�����µ�ͬѧ�ļ��롣
  *	����SARS�Ǻ����״�Ⱦ�ģ�ֻҪ�ڸ�����һλͬѧ��ȾSARS��
  *	��ô���������ͬѧ������Ϊ����SARS��
  *	���ڵ������Ǽ�����ж���λѧ����ȾSARS�ˡ�
  *	�ٶ����Ϊ0��ͬѧ�ǵ���SARS�ġ�����num[]�洢�ü�����Ԫ�ظ�����
  *	���ڼ��Ϻϲ�ʱ����num[]���ɡ�
  *	Ȼ���ҳ�0���ڵļ��ϵĸ��ڵ�x��
  *	��ˣ�num[x]����answer�ˡ�
  *
  *	Case
  *	Input
  *	The input file contains several cases.Each test case begins with two integers n and m in a line, where n is the number of students, and m is the number of groups.You may assume that 0 < n <= 30000 and 0 <= m <= 500. Every student is numbered by a unique integer between 0 and n?1, and initially student 0 is recognized as a suspect in all the cases.This line is followed by m member lists of the groups, one line per group.Each line begins with an integer k by itself representing the number of members in the group.Following the number of members, there are k integers representing the students in this group.All the integers in a line are separated by at least one space.
  *	A case with n = 0 and m = 0 indicates the end of the input, and need not be processed.
  *	Output
  *	For each case, output the number of suspects in one line.
  *	Sample Input
  *	100 4
  *	2 1 2
  *	5 10 13 11 12 14
  *	2 0 1
  *	2 99 2
  *	200 2
  *	1 5
  *	5 1 2 3 4 5
  *	1 0
  *	0 0
  *	Sample O
  *	4
  *	1
  *	1
  */

#include<iostream>

using namespace std;

class suspects {
private:
	int n, m, k, t, f, p[30001], rank[30001], a, b;

	int find(int x) {
		if (x == p[x]) return x;
		else return p[x] = find(p[x]);
	}

	void un(int x, int y) {
		a = find(x);
		b = find(y);
		if (a == b)
			return;
		if (rank[a] > rank[b])
			p[b] = a;
		else {
			p[a] = b;
			if (rank[a] == rank[b])
				rank[b]++;
		}
	}

public:
	void func() {
		int i, sum;
		while (cin >> m >> n && (m || n)) {
			for (i = 0; i < m; i++) {
				p[i] = i;
				rank[i] = 0;
			}
			for (i = 0; i < n; i++) {
				cin >> k;
				if (k >= 1)
					cin >> f;
				for (int j = 1; j < k; j++) {
					cin >> t;
					un(f, t);
				}
			}
			sum = 1;
			for (i = 1; i < m; i++) {
				if (find(i) == find(0))
					sum++;
			}
			cout << sum << endl;
		}
		return;
	}
};