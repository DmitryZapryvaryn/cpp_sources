#include "database.h"

#include <iostream>

using std::cout, std::endl;

void Database::Add(const Date & date, const string & event)
{
	events[date].insert(event);
}

bool Database::DeleteEvent(const Date & date, const string & event)
{
	return (events.count(date) == 0) || (events[date].count(event) == 0) ?
		false : events[date].erase(event);
}

int Database::DeleteDate(const Date & date)
{
	int events_count = 0;
	if (events.count(date) > 0) {
		events_count = events[date].size();
		events.erase(date);
	}

	return events_count;
}

set<string> Database::Find(const Date & date) const
{
	if (events.count(date) == 0) {
		return {};
	}
	return events.at(date);
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
