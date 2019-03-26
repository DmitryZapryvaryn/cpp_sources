#include "phone_number.h"
#include <sstream>

PhoneNumber::PhoneNumber(const string & international_number)
{
	stringstream ss(international_number);
	char plus;
	ss >> plus;
	if (plus != '+') {
		throw invalid_argument("Invalid number format");
	}

	string counrty_code, city_code, local_number;
	getline(ss, counrty_code, '-');
	getline(ss, city_code, '-');
	getline(ss, local_number);

	if (counrty_code.empty() || city_code.empty() || local_number.empty()) {
		throw invalid_argument("Invalid number format");
	}

	country_code_ = counrty_code;
	city_code_ = city_code;
	local_number_ = local_number;
}

string PhoneNumber::GetCountryCode() const
{
	return PhoneNumber::country_code_;
}

string PhoneNumber::GetCityCode() const
{
	return PhoneNumber::city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
	return PhoneNumber::local_number_;
}

string PhoneNumber::GetInternationalNumber() const
{
	return "+" + PhoneNumber::country_code_ + "-" + PhoneNumber::city_code_ + "-" + PhoneNumber::local_number_;
}
