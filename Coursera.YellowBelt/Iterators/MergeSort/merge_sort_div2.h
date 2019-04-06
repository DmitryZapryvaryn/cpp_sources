#pragma once
#include <vector>
#include <algorithm>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
	if (range_end - range_begin < 2) {
		return;
	}

	vector<typename RandomIt::value_type> elements(range_begin, range_end);
	RandomIt middle = elements.begin() + elements.size() / 2;

	MergeSort(elements.begin(), middle);
	MergeSort(middle, elements.end());

	merge(elements.begin(), middle, middle, elements.end(), range_begin);
}
