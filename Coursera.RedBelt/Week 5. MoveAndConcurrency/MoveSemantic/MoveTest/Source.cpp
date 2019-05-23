#include <string>
#include <utility>
#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<string> strings;
	string str = "abcdef";

	cout << "Before | " << str << "\n";
	strings.push_back(str.replace(2, 1, 1, 'x'));
	cout << "After | " << str << "\n";

}