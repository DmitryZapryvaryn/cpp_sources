#include "date.h"

#include <string>
#include <iomanip>
#include <stdexcept>

Year::Year(int new_value)
{
	value = new_value;
}

Month::Month(int new_value)
{
	if (new_value > 12 || new_value < 1) {
		string error_message = "Month value is invalid: " + to_string(new_value);
		throw range_error(error_message);
	}
	value = new_value;
}

Day::Day(int new_value)
{
	if (new_value > 31 || new_value < 1) {
		string error_message = "Day value is invalid: " + to_string(new_value);
		throw range_error(error_message);
	}
	value = new_value;
}

Date::Date()
{
	day = 1;
	month = 1;
	year = 0;
}

Date::Date(Year new_year, Month new_month, Day new_day)
{
	day = new_day.value;
	month = new_month.value;
	year = new_year.value;
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

bool operator<(const Date & lhs, const Date & rhs)
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

	Month month = Month(m);
	Day day = Day(d);
	Year year = Year(y);

	return Date(year, month, day);
}