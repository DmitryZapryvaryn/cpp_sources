#include "database.h"

#include <iostream>

using std::cout, std::endl;

void Database::Add(const Date & date, const string & event)
{
	if (unique_events.count({ date, event }) == 0) {
		events[date].push_back(event);
		unique_events.insert({ date, event });
	}
}

Enrty Database::Last(const Date & date) const
{
	auto date_it = events.upper_bound(date);
	if (date_it != events.begin()) {
		--date_it;
		auto events_vec = date_it->second;
		if (!events_vec.empty()) {
			return { date_it->first, events_vec.back() };
		}
		else throw invalid_argument("");
	}
	else {
		throw invalid_argument("");
	}
}

void Database::Print(ostream& out) const
{
	for (const auto& item : events) {
		for (const auto& elem : item.second) {
			out << item.first << ' ' << elem << endl;
		}
	}
}

ostream & operator<<(ostream & out, Enrty enrty)
{
	out << enrty.first << ' ' << enrty.second;
	return out;
}
