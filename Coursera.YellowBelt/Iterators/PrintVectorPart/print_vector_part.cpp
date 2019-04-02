#include "print_vector_part.h"
#include <algorithm>
#include <iostream>

void PrintVectorPart(const vector<int>& numbers) {

	auto it = find_if(numbers.begin(), numbers.end(), [](int x) {return x < 0; });

	for (auto i = it; i != numbers.begin(); ) {
		cout << *(--i) << " ";
	}
}