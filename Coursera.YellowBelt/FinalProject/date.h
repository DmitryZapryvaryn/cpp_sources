#pragma once

#include <string>
#include <exception>

using std::string, std::exception;

struct Year {
	int value;
	explicit Year(int new_value) {
		value = new_value;
	}
};

struct Month {
	int value;

	explicit Month(int new_value) {
		if (new_value > 12 || new_value < 1) {
			string error_message = "Month value is invalid: " + to_string(new_value);
			throw range_error(error_message);
		}
		value = new_value;
	}
};

struct Day {
	int value;

	explicit Day(int new_value) {
		if (new_value > 31 || new_value < 1) {
			string error_message = "Day value is invalid: " + to_string(new_value);
			throw range_error(error_message);
		}
		value = new_value;
	}
};

class Date {
public:
	Date() {
		day = 1;
		month = 1;
		year = 0;
	}

	Date(Year new_year, Month new_month, Day new_day) {
		day = new_day.value;
		month = new_month.value;
		year = new_year.value;
	}

	Date(const string& string_date) {

	}

	int GetYear() const {
		return year;
	}

	int GetMonth() const {
		return month;
	}

	int GetDay() const {
		return day;
	}

	friend ostream& operator <<(ostream& output, const Date& date) {
		output << setfill('0');
		output << setw(4) << date.GetYear() << '-'
			<< setw(2) << date.GetMonth() << '-'
			<< setw(2) << date.GetDay();

		return output;
	}

private:
	int day;
	int month;
	int year;
};

bool operator<(const Date& lhs, const Date& rhs) {
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