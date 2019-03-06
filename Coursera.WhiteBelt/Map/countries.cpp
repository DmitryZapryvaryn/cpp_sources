#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
	int q;
	cin >> q;

	map<string, string> countries;

	for (int i = 0; i < q; ++i) {
		string command;
		cin >> command;

		if (command == "CHANGE_CAPITAL") {
			string country, new_capital;

			cin >> country >> new_capital;

			if (countries.count(country) == 0) {
				countries[country] = new_capital;
				cout << "Introduce new country " << country << " with capital " << new_capital << endl;
			}
			else if (countries[country] == new_capital) {
				cout << "Country " << country << " hasn't changed its capital" << endl;
			}
			else {
				cout << "Country " << country << " has changed its capital from " << countries[country] << " to " << new_capital << endl;
				countries[country] = new_capital;
			}
		}
		else if (command == "RENAME") {
			string old_country_name, new_country_name;
			
			cin >> old_country_name >> new_country_name;

			if ((old_country_name == new_country_name) || (countries.count(old_country_name) == 0) || (countries.count(new_country_name) != 0)) {
				cout << "Incorrect rename, skip" << endl;
			}
			else {
				cout << "Country " << old_country_name << " with capital " << countries[old_country_name] << " has been renamed to " << new_country_name << endl;
				countries[new_country_name] = countries[old_country_name];
				countries.erase(old_country_name);
			}
		}
		else if (command == "ABOUT") {
			string country;

			cin >> country;

			if (countries.count(country) == 0) {
				cout << "Country " << country << " doesn't exist" << endl;
			}
			else {
				cout << "Country " << country << " has capital " << countries[country] << endl;
			}
		}
		else if (command == "DUMP") {
			if (countries.empty()) {
				cout << "There are no countries in the world" << endl;
			}
			else {
				for (const auto& country : countries) {
					cout << country.first << "/" << country.second << " ";
				}
				cout << endl;
			}
		}
	}
}