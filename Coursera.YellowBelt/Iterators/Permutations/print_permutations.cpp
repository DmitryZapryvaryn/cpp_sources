#include "print_permutations.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>

ostream& operator << (ostream& out, const vector<int>& v) {
	for (auto i : v) out << i << ' ';
	return out;
}

void PrintPermutations(int N)
{
	vector<int> vec(N);
	iota(vec.rbegin(), vec.rend(), 1);
	
	do {
		cout << vec << endl;
	} while (prev_permutation(vec.begin(), vec.end()));
}
