#pragma once

#include <iostream>

using namespace std;

class Date {
public:
	Date();
	Date(int new_year, int new_month, int new_day);

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