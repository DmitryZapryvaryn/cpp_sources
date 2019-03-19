#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
	size_t q;
	std::cin >> q;

	typedef std::map<std::string, std::vector<std::string>> mapStringVecOfString;

	mapStringVecOfString bus_to_stops;
	mapStringVecOfString stop_to_buses;


	for (size_t i = 0; i < q; ++i) {
		std::string command;
		std::cin >> command;

		if (command == "NEW_BUS") {

		}
		else if (command == "BUSES_FOR_STOP") {

		}
		else if (command == "STOPS_FOR_BUS") {

		}
		else if (command == "ALL_BUSES") {

		}
	}
}