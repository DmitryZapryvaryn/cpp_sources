#include <map>
#include <vector>
#include <string>
#include <ostream>

using namespace std;

class Person {
public:
	Person(const string& name, const string& surname, int _birth_year) {
		first_names[_birth_year] = name;
		last_names[_birth_year] = surname;
		birth_year = _birth_year;
	}

	void ChangeFirstName(int year, const string& first_name) {
		if (year >= birth_year) {
			first_names[year] = first_name;
		}
	}
	void ChangeLastName(int year, const string& last_name) {
		if (year >= birth_year) {
			last_names[year] = last_name;
		}
	}
	string GetFullName(int year) const {
		if (year < birth_year) { return "No person"; }

		const vector<string> first_name_history = FindNameHistoryByYear(first_names, year);
		string first_name;
		if (!first_name_history.empty())
			first_name = first_name_history.back();

		const vector<string> last_name_history = FindNameHistoryByYear(last_names, year);
		string last_name;
		if (!last_name_history.empty())
			last_name = last_name_history.back();

		return BuildFullName(first_name, last_name);
	}
	string GetFullNameWithHistory(int year) const {
		if (year < birth_year) return "No person";

		const vector<string> first_name_history = FindNameHistoryByYear(first_names, year);
		string first_name;
		if (!first_name_history.empty())
			first_name = first_name_history.back();

		const vector<string> last_name_history = FindNameHistoryByYear(last_names, year);
		string last_name;
		if (!last_name_history.empty())
			last_name = last_name_history.back();

		if (first_name.empty() && last_name.empty()) {
			return "Incognito";
		}
		else if (first_name.empty()) {
			return last_name + BuildOutputNameHistory(last_name_history) + " with unknown first name";
		}
		else if (last_name.empty()) {
			return first_name + BuildOutputNameHistory(first_name_history) + " with unknown last name";
		}
		else {
			return first_name + BuildOutputNameHistory(first_name_history) + " " + last_name + BuildOutputNameHistory(last_name_history);
		}
	}

private:
	int birth_year;
	map<int, string> first_names;
	map<int, string> last_names;

	vector<string> FindNameHistoryByYear(const map<int, string>& names, int year) const {
		vector<string> name_history;

		for (const auto& item : names) {
			if (item.first <= year && (name_history.empty() || name_history.back() != item.second))	name_history.push_back(item.second);
			else break;
		}

		return name_history;
	}

	string BuildOutputNameHistory(const vector<string>& names) const {
		string result;

		if (names.empty()) return result;

		string separator;
		size_t end = names.size() - 1;
		for (size_t i = 1; i < names.size(); ++i) {
			result += separator + names[end - i];
			separator = ", ";
		}

		if (result.empty())
			return result;

		return " (" + result + ")";
	}

	string BuildFullName(const string& first_name, const string& last_name) const {
		if (first_name.empty() && last_name.empty()) {
			return "Incognito";
		}
		else if (first_name.empty()) {
			return last_name + " with unknown first name";
		}
		else if (last_name.empty()) {
			return first_name + " with unknown last name";
		}
		else {
			return first_name + " " + last_name;
		}
	}
};

int main() {
	ofstream
	Person("Harold", "Rovia", 1996);
	Person person("Harold", "Rovia", 1996);
	Person person1 = { "Harold", "Rovia", 1996 };
}