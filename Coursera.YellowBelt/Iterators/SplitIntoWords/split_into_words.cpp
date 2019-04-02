#include "split_into_words.h"
#include <algorithm>

vector<string> SplitIntoWords(const string & s)
{
	if (s.empty()) return {};

	vector<string> result;
	for (auto it = s.begin(); it != s.end(); ++it) {
		auto new_it = find(it, s.end(), ' ');
		result.push_back({it, new_it});

		if (new_it == s.end())
			it = --new_it;
		else it = new_it;
	}

	return result;
}
