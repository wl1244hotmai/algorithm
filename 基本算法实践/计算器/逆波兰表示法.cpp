/**
* 先用调度场算法把中缀转换为逆波兰（后缀），
* 然后按照逆波兰表达式的求法得到结果
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

/**调度场算法
* 3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3
* 1. 从左向右读，数字直接输出到流；
* 2. 读到符号o1，从符号栈中取出最上面的o2，两者比较优先级；
*	  若o1是左符号，则o1优先级小于等于o2的情况下，o2出栈、输出，
*    若o1是右符号，则o1优先级小于o2的情况下，o2出栈、输出，
*    循环2步骤，循环结束后o1进栈；
* 3. 遇到左括号，压栈，遇到右括号，弹栈，一直到找到又括号，把右括号前面的其他符号输出；
*    若栈为空还是没有找到左括号，说明输入有错；
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
					//从右至左的符号
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
* 逆波兰（后缀）表达式的计算方式
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