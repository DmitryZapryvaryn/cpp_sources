#pragma once

#include "date.h"

#include <string>
#include <set>
#include <map>
#include <ostream>
#include <algorithm>

using namespace std;


class Database {
public:
	void Add(const Date& date, const string& event);
	
	template<typename PredicateFunc>
	int RemoveIf(PredicateFunc predicate);

	template<typename PredicateFunc>
	set<string> FindIf(PredicateFunc date) const;

	string Last(const Date& date) const;

	void Print(ostream& out) const;

private:
	map<Date, set<string>> events;
};

template<typename PredicateFunc>
int Database::RemoveIf(PredicateFunc predicate)
{
	return 0;
}

template<typename PredicateFunc>
set<string> Database::FindIf(PredicateFunc predicate) const
{
	return set<string>();
}
