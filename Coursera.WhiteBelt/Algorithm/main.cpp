#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

void PrintVector(const vector<string>& vec) {
	for (const auto& i : vec) cout << i << " ";
}

int main() {
	int n;
	cin >> n;

	vector<string> a(n);
	for (auto& i : a) {
		cin >> i;
	}

	sort(begin(a), end(a),
		[](const string& l, const string& r)
	{ 	return lexicographical_compare(
		begin(l), end(l),
		begin(r), end(r),
		[](char cl, char cr) { return tolower(cl) < tolower(cr); });
	});

	PrintVector(a);
}