#include <iostream>
#include <string>

using namespace std;

// TODO: opertor enum + - * /
// TODO: 

int main() {
	int x, N;
	char operation;

	string expression;

	cin >> x >> N;
	expression = '(' + to_string(x) + ')';
	for (int i = 0; i < N; ++i) {
		cin >> operation >> x;
		if (i == N - 1) {
			expression = expression + ' ' + operation + ' ' + to_string(x);
		}
		else {
			expression = '(' + expression + ' ' + operation + ' ' + to_string(x) + ')';
		}
	}

	cout << expression << endl;
	return 0;
}