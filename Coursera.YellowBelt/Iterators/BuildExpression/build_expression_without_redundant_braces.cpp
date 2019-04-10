#include <iostream>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
	int x, N;
	char operation;

	deque<string> expression;

	cin >> x >> N;
	expression.push_back(to_string(x));
	char prev_oper = '*';
	for (int i = 0; i < N; ++i) {
		cin >> operation >> x;
		
		bool braces = (operation == '/' || operation == '*') && (prev_oper == '-' || prev_oper == '+');
		if (braces) {
			expression.push_front("(");
			expression.push_back(")");
		}
		expression.push_back(" ");
		expression.push_back(string(1, operation));
		expression.push_back(" ");
		expression.push_back(to_string(x));

		prev_oper = operation;
	}

	for (auto item : expression) {
		cout << item;
	}
	cout << endl;
	return 0;
}