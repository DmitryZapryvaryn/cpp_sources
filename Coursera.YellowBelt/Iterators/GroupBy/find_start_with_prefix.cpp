#include <utility>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// heterogeneous comparison:
struct Comp
{
	bool operator() (const string& s, const string& i) const { return s.substr(0, i.length()) < i; }
	bool operator() (const string& i, const string& s) const { return i.substr(0, s.length()) < s; }
};

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
	RandomIt range_begin, RandomIt range_end,
	string prefix) {
	if (range_begin == range_end) return make_pair(range_begin, range_end);
	return equal_range(range_begin, range_end, prefix, Comp{});
}

int main() {
	const vector<string> sorted_strings = { "moscow", "motovilikha", "murmansk" };

	const auto mo_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
	for (auto it = mo_result.first; it != mo_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto mt_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
	cout << (mt_result.first - begin(sorted_strings)) << " " <<
		(mt_result.second - begin(sorted_strings)) << endl;

	const auto na_result =
		FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
	cout << (na_result.first - begin(sorted_strings)) << " " <<
		(na_result.second - begin(sorted_strings)) << endl;

	return 0;
}