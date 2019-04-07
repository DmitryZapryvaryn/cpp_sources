#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end,
	string prefix) {

	if (range_begin == range_end) return { range_begin, range_end };

	// all strings starting with prefix more or equal [ prefix ]
	const auto first = lower_bound(range_begin, range_end, prefix);

	// to find uppper bound we need to change prefix to next lexicographical string
	string upper_bound_prefix = prefix;
	++upper_bound_prefix[prefix.length() - 1];
	const auto last = lower_bound(range_begin, range_end, upper_bound_prefix);

	return { first, last };
}