#pragma once

#include "date.h"

#include <string>
#include <set>
#include <map>
#include <ostream>

using namespace std;


class Database {
public:
	void Add(const Date& date, const string& event);
	
	template<typename Predicate>
	int RemoveIf(Predicate predicate);

	template<typename Predicate>
	set<string> FindIf(Predicate date) const;

	string Last(const Date& date) const;

	void Print(ostream& out) const;

private:
	map<Date, set<string>> events;
};