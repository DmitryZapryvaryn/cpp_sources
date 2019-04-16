#pragma once

#include <iostream>

using namespace std;

struct Date {
	int year;
	int month;
	int day;
};

bool operator!= (const Date& lhs, const Date& rhs);
bool operator== (const Date& lhs, const Date& rhs);

bool operator< (const Date& lhs, const Date& rhs);
bool operator> (const Date& lhs, const Date& rhs);

bool operator<= (const Date& lhs, const Date& rhs);
bool operator>= (const Date& lhs, const Date& rhs);


ostream& operator <<(ostream& output, const Date& date);

Date ParseDate(istream& is);