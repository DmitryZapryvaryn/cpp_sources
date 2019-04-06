#include "find_nearest_element.h"
#include <set>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border)
{
	const auto lower = numbers.lower_bound(border);

	if (lower == numbers.begin()) {
		return lower;
	}

	const auto prev_lower = prev(lower);
	if (lower == numbers.end()) {
		return prev_lower;
	}

	
	return (*lower - border) < (border - *prev_lower) ? lower : prev_lower;
	
}
