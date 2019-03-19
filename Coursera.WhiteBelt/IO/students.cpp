#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
	string full_name;
	string birthday;
};

int main () {
	int q;
	cin >> q;

	vector<Student> students(q);
	string first_name, last_name;
	string day, month, year;
	for (auto& student : students) {
		cin >> first_name >> last_name >> day >> month >> year;
		student.full_name = first_name + " " + last_name;
		student.birthday = day + "." + month + "." + year;
	}

	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string command;
		int k;
		cin >> command >> k;
		--k;
		if (command == "name" && k >= 0 && k < q) {
			cout << students[k].full_name << endl;
		}
		else if (command == "date" && k >= 0 && k < q) {
			cout << students[k].birthday << endl;
		}
		else {
			cout << "bad request" << endl;
		}
	}

	return 0;
}