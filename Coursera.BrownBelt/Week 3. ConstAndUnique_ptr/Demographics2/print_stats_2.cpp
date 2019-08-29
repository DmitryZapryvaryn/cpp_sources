#include "test_runner.h"

#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

template <typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator begin, Iterator end)
		: first(begin)
		, last(end)
	{
	}

	Iterator begin() const {
		return first;
	}

	Iterator end() const {
		return last;
	}

private:
	Iterator first, last;
};

template <typename Collection>
auto Head(Collection& v, size_t top) {
	return IteratorRange{ v.begin(), next(v.begin(), min(top, v.size())) };
}

struct Person {
	string name;
	int age, income;
	bool is_male;

	friend istream& operator>> (istream& in, Person& p) {
		char gender;
		return in >> p.name >> p.age >> p.income >> gender;
		p.is_male = (gender == 'M');
	}
};

vector<Person> ReadPeople(istream& input) {
	int count;
	input >> count;

	vector<Person> result(count);
	for (Person& p : result) {
		input >> p;
	}

	return result;
}

/*
	people must be sorted
*/
size_t countPeopleFromAge(const vector<Person>& people, size_t adult_age) {
	auto adult_begin = lower_bound(
		begin(people), end(people), adult_age, [](const Person& lhs, int age) {
			return lhs.age < age;
		}
	);

	return distance(adult_begin, people.end());
}

void TestCountFromAge() {
	// given
	vector<Person> givenPeople1 = {
		{"name1", 20, 4, true}, {"name2", 17, 45, true}, {"name3", 19, 100, false}, {"name4", 18, 45, false}
	};
	vector<Person> givenPeople2 = {
		{"name1", 20, 4, true}, {"name2", 20, 45, true}, {"name3", 20, 100, false}, {"name4", 20, 45, false}
	};


	// when
	ASSERT_EQUAL(countPeopleFromAge(givenPeople1, 18), 2);
	ASSERT_EQUAL(countPeopleFromAge(givenPeople2, 20), 4);
}


int main() {

	/*TestRunner tr;
	RUN_TEST(tr, TestCountFromAge);*/
	vector<Person> people = ReadPeople(cin);

	sort(begin(people), end(people), [](const Person& lhs, const Person& rhs) {
		return lhs.age < rhs.age;
		});

	for (string command; cin >> command; ) {
		if (command == "AGE") {
			int adult_age;
			cin >> adult_age;

			auto adult_begin = lower_bound(
				begin(people), end(people), adult_age, [](const Person& lhs, int age) {
					return lhs.age < age;
				}
			);

			cout << "There are " << distance(adult_begin, end(people))
				<< " adult people for maturity age " << adult_age << '\n';
		}
		else if (command == "WEALTHY") {
			int count;
			cin >> count;

			auto head = Head(people, count);

			partial_sort(
				head.begin(), head.end(), people.end(), [](const Person& lhs, const Person& rhs) {
					return lhs.income > rhs.income;
				}
			);

			int total_income = accumulate(
				head.begin(), head.end(), 0, [](int cur, const Person& p) {
					return cur += p.income;
				}
			);
			cout << "Top-" << count << " people have total income " << total_income << '\n';
		}
		else if (command == "POPULAR_NAME") {
			char gender;
			cin >> gender;

			IteratorRange range{
			  begin(people),
			  partition(begin(people), end(people), [gender](Person& p) {
				return p.is_male = (gender == 'M');
			  })
			};
			if (range.begin() == range.end()) {
				cout << "No people of gender " << gender << '\n';
			}
			else {
				sort(range.begin(), range.end(), [](const Person& lhs, const Person& rhs) {
					return lhs.name < rhs.name;
					});
				const string* most_popular_name = &range.begin()->name;
				int count = 1;
				for (auto i = range.begin(); i != range.end(); ) {
					auto same_name_end = find_if_not(i, range.end(), [i](const Person& p) {
						return p.name == i->name;
						});
					auto cur_name_count = std::distance(i, same_name_end);
					if (cur_name_count > count) {
						count = cur_name_count;
						most_popular_name = &i->name;
					}
					i = same_name_end;
				}
				cout << "Most popular name among people of gender " << gender << " is "
					<< *most_popular_name << '\n';
			}
		}
	}
}
