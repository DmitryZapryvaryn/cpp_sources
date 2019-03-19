#include <iostream>
#include <vector>
#include <string>

using namespace std;

const vector<int> MONTHS_DAYS = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int MONTHS_COUNT = MONTHS_DAYS.size();

int main() {
	int q;
	cin >> q;

	vector<string> commands(q);
	int currentMonth = 0;
	vector<vector<string>> days(31);
	for (string& command : commands) {
		cin >> command;

		if (command == "ADD") {
			int i;
			string s;
			cin >> i >> s;
			days[i - 1].push_back(s);
		}
		else if (command == "NEXT") {
			int oldSize = days.size();

			currentMonth = (currentMonth + 1) % MONTHS_COUNT;
			int newSize = MONTHS_DAYS[currentMonth];

			if (newSize > oldSize)
			{
				days.resize(newSize);
			}
			else 
			{
				for (int i = newSize; i < oldSize; ++i) {
					days[newSize - 1].insert(days[newSize - 1].end(), days[i].begin(), days[i].end());
				}
				days.resize(newSize);
			}
		}
		else if (command == "DUMP") {
			int i;
			cin >> i;
			cout << days[i - 1].size() << " ";
			for (string task : days[i - 1]) cout << task << " ";
			cout << endl;
		}
	}
	

	return 0;
}