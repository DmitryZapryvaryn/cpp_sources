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
	
	int RemoveIf(const Date& date);

	set<string> FindIf(const Date& date) const;

	string Last(const Date& date) const;

	void Print(ostream& out) const;

private:
	map<Date, set<string>> events;
};