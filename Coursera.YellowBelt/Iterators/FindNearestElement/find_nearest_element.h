#pragma once

#include <set>

using namespace std;

set<int>::const_iterator FindNearestElement(
	const set<int>& numbers,
	int border);