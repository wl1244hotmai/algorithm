#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;

// 错误
#define NO_ERROR        0
#define SYTAX_ERROR     1

class calculator {
private:
	typedef enum {
		TOKENIZER_ERROR,        // Error
		TOKENIZER_ENDOFINPUT,   // End of input
		TOKENIZER_NUMBER,       // number
		TOKENIZER_PLUS = '+',         // +
		TOKENIZER_MINUS = '-',        // -
		TOKENIZER_ASTR = '*',         // *
		TOKENIZER_SLASH = '\\',        // /
		TOKENIZER_LPAREN = '(',       // (
		TOKENIZER_RPAREN = ')',       // )
	} token_t;
	token_t current_token;
	char ch;
	istringstream is;

	void error(int i) {
		switch (i) {
		case SYTAX_ERROR:
			cout << "SYTAX_ERROR" << endl;
		}
		current_token = TOKENIZER_ERROR;
	}

	void accept(token_t token) {
		if (tokenizer_token() != token)
			error(SYTAX_ERROR);
		tokenizer_next();
	}

	void tokenizer_next() {
		while (is && is >> ch && ch == ' ')
			is >> ch;

		if (ch >= '0' && ch <= '9')
			is.putback(ch);
		current_token = TOKENIZER_NUMBER;
		switch (ch) {
		case '+':
			current_token = TOKENIZER_PLUS;
			break;
		case '-':
			current_token = TOKENIZER_MINUS;
			break;
		case '*':
			current_token = TOKENIZER_ASTR;
			break;
		case '/':
			current_token = TOKENIZER_SLASH;
			break;
		case '(':
			current_token = TOKENIZER_LPAREN;
			break;
		case ')':
			current_token = TOKENIZER_RPAREN;
			break;
		}
	}
	
	token_t tokenizer_token() {
		return current_token;
	}

	int factor() {
		token_t op;
		int i;
		op = tokenizer_token();
		switch (op) {
		case TOKENIZER_NUMBER:
			is >> i;
			tokenizer_next();
			return i;
		case TOKENIZER_LPAREN:
			accept(TOKENIZER_LPAREN);
			i = expr();
			tokenizer_next();
			accept(TOKENIZER_RPAREN);
			return i;
		default:
			error(SYTAX_ERROR);
			return 0;
		}
	}

	int term() {
		int f1, f2 = 0;
		token_t op;
		f1 = factor();
		op = tokenizer_token();
		while (op == TOKENIZER_ASTR || op == TOKENIZER_SLASH) {
			tokenizer_next();
			f2 = factor();
			switch (op) {
			case TOKENIZER_ASTR:
				f1 *= f2;
				break;
			case TOKENIZER_SLASH:
				f1 /= f2;
				break;
			}
			op = tokenizer_token();
		}
		return f1;
	}

	int expr() {
		int t1, t2 = 0;
		token_t op;
		t1 = term();
		op = tokenizer_token();
		// 操作符只能是加或者减(同一优先级)
		while (op == TOKENIZER_PLUS || op == TOKENIZER_MINUS)
		{
			// 下一个token
			tokenizer_next();
			// 第二个操作数
			t2 = term();
			switch (op)
			{
			case TOKENIZER_PLUS:
				t1 = t1 + t2;
				break;
			case TOKENIZER_MINUS:
				t1 = t1 - t2;
				break;
			}
			op = tokenizer_token();
		}
		return t1;
	}

public:
 	int calc(string str) {
		is = istringstream(str);
		tokenizer_next();
		return expr();
	}
};

//int main() {
//	int N;
//	cin >> N; getchar();
//	calculator calc;
//	string expr;
//	for (int i = 0; i < N; i++) {
//		getline(cin, expr);
//		cout << calc.calc(expr) << endl;
//	}
//	return 0;
//}