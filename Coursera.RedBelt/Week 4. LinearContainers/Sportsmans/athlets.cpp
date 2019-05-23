#include <list>
#include <iostream>
#include <vector>
#include <array>
using namespace std;

constexpr int N = 100'000;

int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	size_t n;
	cin >> n;

	list<int> sportsmens;
	array<list<int>::iterator, N + 1> positions;
	positions.fill(sportsmens.end());
	for (size_t i = 0; i < n; ++i) {
		int new_number, pos_number;
		cin >> new_number >> pos_number;

		positions[new_number] = sportsmens.insert(positions[pos_number], new_number);
	}

	for (auto it = sportsmens.begin(); it != sportsmens.end(); ++it) {
		cout << *it << " ";
	}

	return 0;
}