#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

size_t BUS_NUMBER = 0;

int main() {
	size_t q;
	cin >> q;

	map<vector<string>, size_t> routes_to_bus;

	for (size_t i = 0; i < q; ++i) {
		int n;
		cin >> n;

		vector<string> stops(n);
		for (string& stop : stops) {
			cin >> stop;
		}

		if (routes_to_bus.count(stops) > 0) {
			cout << "Already exists for " << routes_to_bus[stops] << endl;
		}
		else {
			
			routes_to_bus[stops] = ++BUS_NUMBER;
			cout << "New bus " << routes_to_bus[stops] << endl;
		}
	}

	return 0;
}