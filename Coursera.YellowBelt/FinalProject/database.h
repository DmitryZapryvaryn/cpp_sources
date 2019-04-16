#pragma once

#include "date.h"

#include <string>
#include <vector>
#include <set>
#include <map>
#include <ostream>
#include <algorithm>

using namespace std;

/* struct Enrty {Date date, string event} */
using Enrty = pair<Date, string>;

class Database {
public:
	void Add(const Date& date, const string& event);
	
	template<typename PredicateFunc>
	int RemoveIf(PredicateFunc predicate);

	template<typename PredicateFunc>
	vector<Enrty> FindIf(PredicateFunc date) const;

	Enrty Last(const Date& date) const;

	void Print(ostream& out) const;

private:
	map<Date, vector<string>> events;
	set<Enrty> unique_events;
};

template<typename PredicateFunc>
int Database::RemoveIf(PredicateFunc predicate)
{
	int count = 0;
	for (auto it = events.begin(); it != events.end();) {

		const auto& date = it->first;
		auto remove_point = stable_partition(it->second.begin(), it->second.end(), [date, predicate] /* or [=] */(const auto& event) { return !predicate(date, event); });

		int rem_number = it->second.end() - remove_point;

		for (int i = 0; i < rem_number; ++i) {
			unique_events.erase({ date,  it->second.back() });
			it->second.pop_back();
		}

		count += rem_number;

		// cpp idiom: erase from container while iterating through it
		if (it->second.empty()) events.erase(it++);
		else ++it;

	}

	return count;
}

template<typename PredicateFunc>
vector<Enrty> Database::FindIf(PredicateFunc predicate) const
{
	vector<Enrty> result;
	for (const auto& item : events) {
		for (const auto& event : item.second) {
			if (predicate(item.first, event)) result.push_back({ item.first, event });
		}
	}

	return result;
}

ostream& operator<< (ostream& out, Enrty de);

void TestDatabase();