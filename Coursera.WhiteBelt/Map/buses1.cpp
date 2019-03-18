#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void PrintVector(const vector<string>& vecToPrint) {
	for (const string item : vecToPrint) cout << item << " ";
	cout << endl;
}

int main() {
	size_t q;
	cin >> q;

	map<string, vector<string>> bus_to_stops;
	map<string, vector<string>> stop_to_buses;

	for (int i = 0; i < q; ++i) {
		string command;
		cin >> command;

		if (command == "NEW_BUS") {
			string bus;
			int stop_count;
			cin >> bus >> stop_count;

			vector<string> stops(stop_count);

			for (auto& stop : stops) {
				cin >> stop;
				stop_to_buses[stop].push_back(bus);
			}
			bus_to_stops[bus] = stops;
		}
		else if (command == "BUSES_FOR_STOP") {
			string stop;
			cin >> stop;

			if (stop_to_buses.count(stop) == 0) {
				cout << "No stop" << endl;
			}
			else {
				PrintVector(stop_to_buses[stop]);
			}
		}
		else if (command == "STOPS_FOR_BUS") {
			string bus;
			cin >> bus;

			if (bus_to_stops.count(bus) == 0) {
				cout << "No bus" << endl;
			}
			else {
				for (const auto& stop : bus_to_stops[bus]) {
					cout << "Stop " << stop << ": ";

					if (stop_to_buses[stop].size() == 1) cout << "no interchange" << endl;
					else {
						for (const auto& other_bus : stop_to_buses[stop]) {
							if (bus != other_bus) cout << other_bus << " ";
						}
						cout << endl;
					}
				}
			}
		}
		else if (command == "ALL_BUSES") {
			if (bus_to_stops.empty())
				cout << "No buses" << endl;
			else {
				for (const auto& route : bus_to_stops) {
					cout << "Bus " << route.first << ": ";
					PrintVector(route.second);
				}
			}
		}
	}
}