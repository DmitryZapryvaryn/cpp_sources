#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <numeric>
#include <iterator>

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

struct Person {
	string name;
	int age, income;
	bool is_male;
};

vector<Person> ReadPeople(istream& input) {
	int count;
	input >> count;

	vector<Person> result(count);
	for (Person& p : result) {
		char gender;
		input >> p.name >> p.age >> p.income >> gender;
		p.is_male = (gender == 'M');
	}

	return result;
}

vector<int> countTotalIncome(vector<Person>& people) {
	vector<int> result(people.size());

	if (!people.empty()) {
		sort(people.begin(), people.end(),
			[](const Person& lhs, const Person& rhs) {
				return lhs.income > rhs.income;
			}
		);

		result[0] = people[0].income;
		for (size_t i = 1; i < result.size(); ++i) {
			result[i] = result[i - 1] + people[i].income;
		}
	}

	return result;
}

struct PopularNames {
	optional<string> male_popular_name;
	optional<string> female_popular_name;
};

template<typename T>
optional<string> findPopularName(IteratorRange<T> people_range) {
	optional<string> popular_name = std::nullopt;
	if (people_range.begin() != people_range.end()) {
		sort(people_range.begin(), people_range.end(), [](const Person& lhs, const Person& rhs) {
			return lhs.name < rhs.name;
			});

		const string* most_popular_name = &(people_range.begin()->name);
		int count = 1;
		for (auto current_pos = people_range.begin(); current_pos != people_range.end(); ) {
			// find first not same name
			auto same_name_end = find_if_not(current_pos, people_range.end(), [current_pos](const Person& p) {
				return p.name == current_pos->name;
				});

			// count number of duplicated names
			auto cur_name_count = std::distance(current_pos, same_name_end);

			// update popular name
			if (cur_name_count > count ||
				(cur_name_count == count && *most_popular_name > current_pos->name)) {
				count = cur_name_count;
				most_popular_name = &current_pos->name;
			}
			current_pos = same_name_end;
		}

		return *most_popular_name;
	}

	return popular_name;
}

PopularNames findPopularNames(vector<Person>& people) {
	optional<string> male_most_popular_name = std::nullopt;
	optional<string> female_most_popular_name = std::nullopt;

	if (!people.empty()) {
		auto partition_point = partition(
			people.begin(),
			people.end(),
			[](const Person& p) {
				return p.is_male;
			});

		IteratorRange male_range(people.begin(), partition_point);
		IteratorRange female_range(partition_point, people.end());

		male_most_popular_name = findPopularName(male_range);
		female_most_popular_name = findPopularName(female_range);
	}

	return { male_most_popular_name, female_most_popular_name };
}


//void TestTotalIncome() {
//	{
//		vector<Person> givenPeople = {
//			{"name1", 20, 6, true}, {"name2", 17, 45, true}, {"name3", 19, 100, false}, {"name4", 18, 45, false}, {"name5", 18, 13, false}, {"name6", 18, 4, false}
//		};
//
//		ASSERT_EQUAL(countTotalIncome(givenPeople)[4], 209);
//	}
//	{
//		vector<Person> givenPeople = {
//			{"name1", 20, 1, true}, {"name2", 20, 1, true}, {"name3", 20, 1, false}, {"name4", 20, 1, false}, {"name5", 18, 1, false}, {"name6", 18, 1, false}
//		};
//
//		ASSERT_EQUAL(countTotalIncome(givenPeople)[2], 3);
//	}
//	{
//		vector<Person> givenPeople = {
//			{"name1", 20, 1, true}, {"name2", 20, 1, true}, {"name1", 20, 1, true},
//		};
//
//		ASSERT_EQUAL(countTotalIncome(givenPeople)[0], 1);
//		ASSERT_EQUAL(countTotalIncome(givenPeople)[1], 2);
//		ASSERT_EQUAL(countTotalIncome(givenPeople)[2], 3);
//	}
//	{
//		vector<Person> givenPeople;
//
//		ASSERT(countTotalIncome(givenPeople).empty());
//	}
//}
//
//void TestFindPopularName() {
//
//	{
//		vector<Person> givenPeople = {
//			{"c", 20, 6, true}, {"c", 17, 45, true}, {"b", 19, 100, true}, {"c", 18, 45, false}, {"a", 18, 13, false}, {"a", 18, 4, false}
//		};
//
//		PopularNames names = findPopularNames(givenPeople);
//
//		ASSERT_EQUAL(*names.male_popular_name, "c");
//		ASSERT_EQUAL(*names.female_popular_name, "a");
//	}
//	{
//		vector<Person> givenPeople = {
//			{"a", 20, 6, true}, {"a", 20, 6, true}
//		};
//
//		PopularNames names = findPopularNames(givenPeople);
//
//		ASSERT_EQUAL(*names.male_popular_name, "a");
//		ASSERT(!names.female_popular_name);
//	}
//	{
//		vector<Person> givenPeople = {
//			{"a", 20, 6, false}, {"a", 20, 6, false}
//		};
//
//		PopularNames names = findPopularNames(givenPeople);
//
//		ASSERT(!names.male_popular_name);
//		ASSERT_EQUAL(*names.female_popular_name, "a");
//	}
//	{
//		vector<Person> givenPeople = {
//			{"a", 20, 6, false}, {"a", 20, 6, true}
//		};
//
//		PopularNames names = findPopularNames(givenPeople);
//
//		ASSERT_EQUAL(*names.male_popular_name, "a");
//		ASSERT_EQUAL(*names.female_popular_name, "a");
//
//	}
//	{
//		vector<Person> givenPeople;
//
//		PopularNames names = findPopularNames(givenPeople);
//
//		ASSERT(!names.male_popular_name);
//		ASSERT(!names.female_popular_name);
//	}
//}
//
//void TestCommands() {
//	istringstream iss("11\nIvan 25 1000 M\nOlga 30 623 W\nSergey 24 825 M\nMaria 42 1254 W\nMikhail 15 215 M\nOleg 18 230 M\nDenis 53 8965 M\nMaxim 37 9050 M\nIvan 47 19050 M\nIvan 17 50 M\nOlga 23 550 W\nAGE 18\nAGE 25\nWEALTHY 5\nPOPULAR_NAME M");
//
//	vector<Person> people = ReadPeople(iss);
//
//	const auto whealty_people = countTotalIncome(people);
//	const PopularNames popular_names = findPopularNames(people);
//	const vector<Person> sorted_by_age = std::move(people);
//
//	sort(begin(people), end(people), [](const Person& lhs, const Person& rhs) {
//		return lhs.age < rhs.age;
//		});
//
//	for (string command; iss >> command; ) {
//		if (command == "AGE") {
//			int adult_age;
//			iss >> adult_age;
//
//			auto adult_begin = lower_bound(
//				sorted_by_age.cbegin(), sorted_by_age.cend(), adult_age, [](const Person& lhs, int age) {
//					return lhs.age < age;
//				}
//			);
//
//			cout << "There are " << distance(adult_begin, sorted_by_age.end())
//				<< " adult people for maturity age " << adult_age << '\n';
//		}
//		else if (command == "WEALTHY") {
//			int count;
//			iss >> count;
//
//			int sum = count == 0 ? 0 : whealty_people[count - 1];
//			cout << "Top-" << count << " people have total income " << sum << '\n';
//		}
//		else if (command == "POPULAR_NAME") {
//			char gender;
//			iss >> gender;
//
//			auto pop_name = gender == 'M' ? popular_names.male_popular_name : popular_names.female_popular_name;
//
//			pop_name ?
//				cout << "Most popular name among people of gender " << gender << " is " << *pop_name << '\n' :
//				cout << "No people of gender " << gender << '\n';
//		}
//	}
//}
//

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	/*TestRunner tr;
	RUN_TEST(tr, TestTotalIncome);
	RUN_TEST(tr, TestFindPopularName);
	RUN_TEST(tr, TestCommands);*/
	vector<Person> people = ReadPeople(cin);

	const vector<int> whealty_people = countTotalIncome(people);
	const PopularNames popular_names = findPopularNames(people);
	sort(people.begin(), people.end(), [](const Person& lhs, const Person& rhs) {
		return lhs.age < rhs.age;
		});
	const vector<Person> sorted_by_age = std::move(people);

	for (string command; cin >> command; ) {
		if (command == "AGE") {
			int adult_age;
			cin >> adult_age;

			auto adult_begin = lower_bound(
				sorted_by_age.cbegin(), sorted_by_age.cend(), adult_age, [](const Person& lhs, int age) {
					return lhs.age < age;
				}
			);

			cout << "There are " << distance(adult_begin, sorted_by_age.end())
				<< " adult people for maturity age " << adult_age << '\n';
		}
		else if (command == "WEALTHY") {
			int count;
			cin >> count;

			int sum = count == 0 ? 0 : whealty_people[count - 1];

			cout << "Top-" << count << " people have total income " << sum << '\n';
		}
		else if (command == "POPULAR_NAME") {
			char gender;
			cin >> gender;

			const auto& pop_name = (gender == 'M') ? popular_names.male_popular_name : popular_names.female_popular_name;

			pop_name ?
				cout << "Most popular name among people of gender " << gender << " is " << *pop_name << '\n' :
				cout << "No people of gender " << gender << '\n';
		}
	}
}
