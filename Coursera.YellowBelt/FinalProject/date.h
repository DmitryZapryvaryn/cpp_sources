#pragma once

#include <iostream>

using namespace std;

struct Year {
	int value;

	explicit Year(int new_value);
};

struct Month {
	int value;

	explicit Month(int new_value);
};

struct Day {
	explicit Day(int new_value);

	int value;
};

class Date {
public:
	Date();
	Date(Year new_year, Month new_month, Day new_day);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const; 

private:
	int day;
	int month;
	int year;
};

bool operator!= (const Date& lhs, const Date& rhs);
bool operator== (const Date& lhs, const Date& rhs);

bool operator< (const Date& lhs, const Date& rhs);
bool operator> (const Date& lhs, const Date& rhs);

bool operator<= (const Date& lhs, const Date& rhs);
bool operator>= (const Date& lhs, const Date& rhs);


ostream& operator <<(ostream& output, const Date& date);

Date ParseDate(istream& is);