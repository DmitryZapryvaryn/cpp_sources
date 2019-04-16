#include "date.h"

#include <string>
#include <iomanip>

Date::Date()
{
	day = 1;
	month = 1;
	year = 0;
}

Date::Date(int new_year, int new_month, int new_day)
{
	day = new_day;
	month = new_month;
	year = new_year;
}

int Date::GetYear() const
{
	return year;
}

int Date::GetMonth() const
{
	return month;
}

int Date::GetDay() const
{
	return day;
}

bool operator!= (const Date & lhs, const Date & rhs)
{
	return (lhs.GetYear() != rhs.GetYear()) || (lhs.GetMonth() != rhs.GetMonth()) || (lhs.GetDay() != rhs.GetDay());
}

bool operator== (const Date & lhs, const Date & rhs)
{
	return !(lhs != rhs);
}

bool operator< (const Date & lhs, const Date & rhs)
{
	if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth()) {
		return lhs.GetDay() < rhs.GetDay();
	}
	else if (lhs.GetYear() == rhs.GetYear()) {
		return lhs.GetMonth() < rhs.GetMonth();
	}
	else {
		return lhs.GetYear() < rhs.GetYear();
	}
}

bool operator> (const Date & lhs, const Date & rhs)
{
	return lhs != rhs && !(lhs < rhs);
}

bool operator<= (const Date & lhs, const Date & rhs)
{
	return lhs == rhs || lhs < rhs;
}

bool operator>= (const Date & lhs, const Date & rhs)
{
	return  lhs == rhs || lhs > rhs;
}

ostream & operator<<(ostream & output, const Date & date)
{
	output << setfill('0');
	output << setw(4) << date.GetYear() << '-'
		<< setw(2) << date.GetMonth() << '-'
		<< setw(2) << date.GetDay();

	return output;
}

Date ParseDate(istream & is)
{
	int y, m, d;
	is >> y; is.ignore(1); is >> m; is.ignore(1); is >> d;

	return Date(y, m, d);
}