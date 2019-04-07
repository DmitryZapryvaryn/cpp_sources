#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// heterogeneous comparison:
struct Comp
{
	bool operator() (const string& s, const char i) const { return s.front() < i; }
	bool operator() (const char i, const string& s) const { return i < s.front(); }
};

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end,
	char prefix) {

	const auto left = lower_bound(range_begin, range_end, string(1, prefix));

	char next_char = static_cast<char>(prefix + 1);

	const auto left = lower_bound(range_begin, range_end, string(1, next_char));

	return equal_range(range_begin, range_end, prefix, Comp{});
}