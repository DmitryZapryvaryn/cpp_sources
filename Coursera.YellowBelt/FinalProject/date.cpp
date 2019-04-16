#include "date.h"

#include <string>
#include <iomanip>

bool operator!= (const Date & lhs, const Date & rhs)
{
	return (lhs.year != rhs.year) || (lhs.month != rhs.month) || (lhs.day != rhs.day);
}

bool operator== (const Date & lhs, const Date & rhs)
{
	return !(lhs != rhs);
}

bool operator< (const Date & lhs, const Date & rhs)
{
	//if (lhs.year == rhs.year && lhs.month == rhs.month) {
	//	return lhs.day < rhs.day;
	//}
	//else if (lhs.year == rhs.year) {
	//	return lhs.month < rhs.month;
	//}
	//else {
	//	return lhs.year < rhs.year;
	//}

	return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
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
	output << setw(4) << date.year << '-'
		<< setw(2) << date.month << '-'
		<< setw(2) << date.day;

	return output;
}

Date ParseDate(istream & is)
{
	int y, m, d;
	is >> y; is.ignore(1); is >> m; is.ignore(1); is >> d;

	return { y, m, d };
}