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
	RandomIt first_third = elements.begin() + elements.size() / 3;
	RandomIt second_third = elements.end() - elements.size() / 3;

	MergeSort(elements.begin(), first_third);
	MergeSort(first_third, second_third);
	MergeSort(second_third, elements.end());

	vector<typename RandomIt::value_type> tmp;
	merge(elements.begin(), first_third, first_third, second_third, back_inserter(tmp));
	merge(tmp.begin(), tmp.end(), second_third, elements.end(), range_begin);
}
