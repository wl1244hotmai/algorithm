/**
* ���õ��ȳ��㷨����׺ת��Ϊ�沨������׺����
* Ȼ�����沨�����ʽ���󷨵õ����
* http://yutianx.info/2014/10/20/2014-10-20-Polish-notation/
*/

#include<iostream>
#include<stack>
#include<string>
#include<sstream>
#include<cassert>
#include <iomanip>
using namespace std;

int operation_priority(const char ch) {
	switch (ch) {
	case '!':	case '^':
		return 3;
	case '*': 	case '/':	case '%':
		return 2;
	case '+': case '-':
		return 1;
	default:
		return 0;
	}
}

/**���ȳ��㷨
* 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3
* 1. �������Ҷ�������ֱ�����������
* 2. ��������o1���ӷ���ջ��ȡ���������o2�����߱Ƚ����ȼ���
*	  ��o1������ţ���o1���ȼ�С�ڵ���o2������£�o2��ջ�������
*    ��o1���ҷ��ţ���o1���ȼ�С��o2������£�o2��ջ�������
*    ѭ��2���裬ѭ��������o1��ջ��
* 3. ���������ţ�ѹջ�����������ţ���ջ��һֱ���ҵ������ţ���������ǰ����������������
*    ��ջΪ�ջ���û���ҵ������ţ�˵�������д�
*/
string ShuntingYard(string infixStr) {
	istringstream is(infixStr);
	ostringstream os;
	string suffixStr;
	stack<char> operations;
	int num;
	char ch;
	while (is && is >> ch) {
		if (ch == ' ') continue;
		else if (ch >= '0' && ch <= '9') {
			is.putback(ch);
			is >> num;
			os << num << ' ';
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
			ch == '^' || ch == '!') {
			int prio = operation_priority(ch);

			while (!operations.empty()) {
				char prev_ch = operations.top();
				int prev_prio = operation_priority(prev_ch);
				if (ch == '^' || ch == '!') {
					//��������ķ���
					if (prio < prev_prio) {
						operations.pop();
						os << prev_ch << ' ';
					}
					else {
						break;
					}
				}
				else {
					if (prio <= prev_prio) {
						operations.pop();
						os << prev_ch << ' ';
					}
					else {
						break;
					}
				}
			}

			operations.push(ch);
		}
		else if (ch == '(') {
			operations.push(ch);
		}
		else if (ch == ')') {
			assert(!operations.empty());
			char prev_ch;
			do {
				prev_ch = operations.top();
				operations.pop();
				if (prev_ch != '(') {
					os << prev_ch << ' ';
				}
			} while (prev_ch != '(');
		}
		else assert(0);
	}
	while (!operations.empty()) {
		os << operations.top() << ' ';
		operations.pop();
	}
	return os.str();
}

/*
* �沨������׺�����ʽ�ļ��㷽ʽ
*/
double RPNclac(string suffixStr) {
	istringstream is(suffixStr);
	char ch; int num;
	stack<double> nums;
	while (is && is >> ch) {
		if (ch >= '0'&&ch <= '9') {
			is.putback(ch);
			is >> num;
			nums.push((double)num);
		}
		else {
			double t1 = 0, t2 = 0;
			assert(!nums.empty());
			t1 = nums.top();
			nums.pop();
			if (ch != '!') {
				assert(!nums.empty());
				t2 = nums.top();
				nums.pop();
			}
			switch (ch) {
			case '+':
				t2 += t1;
				nums.push(t2);
				break;
			case '-':
				t2 -= t1;
				nums.push(t2);
				break;
			case '*':
				t2 *= t1;
				nums.push(t2);
				break;
			case '/':
				t2 /= t1;
				nums.push(t2);
				break;

			case '^':
				t2 = (int)pow(t2, t1);
				nums.push(t2);
				break;
			case '!':
				t2 = 1;
				while (t2 == t1) {
					t2 *= t2++;
				}
				nums.push(t2);
				break;
			}
		}
	}
	assert(nums.size() == 1);
	double output = nums.top();
	nums.pop();
	return output;
}

int main() {
	string expr;
	while (cin && getline(cin, expr) && expr != "0"){
		string RPNexpr = ShuntingYard(expr);
		//cout << "RPN expr is " << RPNexpr << endl;
		cout << fixed << setprecision(2) << RPNclac(RPNexpr) << endl;
	}
	return 0;
}