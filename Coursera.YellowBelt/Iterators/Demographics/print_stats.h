#pragma once

#include <vector>

using namespace std;

enum class Gender {
	FEMALE,
	MALE
};

struct Person {
	int age;
	Gender gender;
	bool is_employed;
};

void PrintStats(vector<Person> persons);