#include "database.h"

#include <iostream>

using std::cout, std::endl;

void Database::Add(const Date & date, const string & event)
{
	events[date].insert(event);
}

string Database::Last(const Date & date) const
{
	string result;
	auto event_it = events.upper_bound(date);
	if (event_it != events.begin()) {
		auto events_set = prev(event_it)->second;
		if (!events_set.empty()) {
			result = *events_set.rbegin();
		}
	}
	return result;
}

void Database::Print(ostream& out) const
{
	for (const auto& item : events) {
		for (const auto& elem : item.second) {
			out << item.first << " " << elem << endl;
		}
	}
}
