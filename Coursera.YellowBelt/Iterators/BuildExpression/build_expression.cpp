#include <iostream>
#include <string>
#include <deque>

using namespace std;

// TODO: opertor enum + - * /
// TODO: 

int main() {
	int x, N;
	char operation;

	deque<string> expression;

	cin >> x >> N;
	expression.push_back(to_string(x));
	for (int i = 0; i < N; ++i) {
		cin >> operation >> x;
		if (operation == '+' || operation == '-' || operation == '*' || operation == '/') {
			expression.push_front("(");
			expression.push_back(")");
			expression.push_back(" ");
			expression.push_back(string(1, operation));
			expression.push_back(" ");
			expression.push_back(to_string(x));
		}
	}

	for (auto item : expression) {
		cout << item;
	}
	cout << endl;
	return 0;
}