#include "poj 1611 The Suspects.h"
#include<iostream>
using namespace std;

typedef struct s {
	int i;
	int * p;
}S;
int main()
{
	S s;
	int *p = &s.i;
	p[0] = 4;
	p[1] = 3;
	s.p = p;
	s.p[1] = 1;
	s.p[0] = 2;
	return 0;
}

//
//int main() {
//	suspects _suspects;
//	_suspects.func();
//	return 0;
//}