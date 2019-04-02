#include "print_stats.h"
#include <iostream>
#include <algorithm>

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
	if (range_begin == range_end) {
		return 0;
	}
	vector<typename InputIt::value_type> range_copy(range_begin, range_end);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	nth_element(
		begin(range_copy), middle, end(range_copy),
		[](const Person& lhs, const Person& rhs) {
		return lhs.age < rhs.age;
	}
	);
	return middle->age;
}

void PrintStats(vector<Person> persons)
{
	cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;

	auto gender_it = partition(persons.begin(), persons.end(), [](const Person& p) { return p.gender == Gender::FEMALE; });
	cout << "Median age for females = " << ComputeMedianAge(persons.begin(), gender_it) << endl;
	cout << "Median age for males = " << ComputeMedianAge(gender_it, persons.end()) << endl;

	auto female_empl_it = partition(persons.begin(), gender_it, [](const Person& p) { return p.is_employed; });
	cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), female_empl_it) << endl;
	cout << "Median age for unemployed females = " << ComputeMedianAge(female_empl_it, gender_it) << endl;

	auto male_empl_it = partition(gender_it, persons.end(), [](const Person& p) { return p.is_employed; });
	cout << "Median age for employed males = " << ComputeMedianAge(gender_it, male_empl_it) << endl;
	cout << "Median age for unemployed males = " << ComputeMedianAge(male_empl_it, persons.end()) << endl;
}
