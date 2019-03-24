#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
	string command;
	is >> command;
	if (command == "NEW_BUS") {
		q.type = QueryType::NewBus;
		is >> q.bus;
		int stop_count = 0;
		is >> stop_count;
		q.stops.resize(stop_count);
		for (string& stop : q.stops) {
			is >> stop;
		}
	}
	else if (command == "BUSES_FOR_STOP") {
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (command == "STOPS_FOR_BUS") {
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (command == "ALL_BUSES") {
		q.type = QueryType::AllBuses;
	}
  return is;
}

struct BusesForStopResponse {
	vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
	bool first = true;
	for (const auto& bus : r.buses) {
		if (!first) {
			os << ' ';
		}
		first = false;
		os << bus;
	}

	return os;
}

struct StopsForBusResponse {
	vector<pair<string, vector<string>>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
	if (r.stops.empty()) os << "No bus";
	else {
		for (const auto& stop : r.stops) {
			os << "Stop " << stop.first << ":";
			for (const auto& bus : stop.second) {
				os << ' ' << bus;
			}
			os << endl;
		}
	}

  return os;
}

struct AllBusesResponse {
	map<string, vector<string>> buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
	if (r.buses.empty()) os << "No buses";
	else {
		for (const auto& bus : r.buses) {
			os << "Bus " << bus.first << ":";
			for (const auto& stop : bus.second) {
				os << ' ' << stop;
			}
			os << endl;
		}
	}
  return os;
}

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
	  buses_to_stops[bus] = stops;
	  for (const string& stop : stops) {
		  stops_to_buses[stop].push_back(bus);
	  }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
	  BusesForStopResponse response;
	  if (stops_to_buses.count(stop) == 0) {
		  response.buses.push_back("No stop");
	  }
	  else {
		  response.buses = stops_to_buses.at(stop);
	  }

	  return response;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
	  StopsForBusResponse response;
	  if (buses_to_stops.count(bus) != 0) {
		  for (const string& stop : buses_to_stops.at(bus)) {
			  pair<string, vector<string>> stop_and_interchange;
			  stop_and_interchange.first = stop;
			  if (stops_to_buses.at(stop).size() == 1) {
				  response.stops.push_back({ stop, {"no interchange"} });
			  }
			  else {
				  for (const string& other_bus : stops_to_buses.at(stop)) {
					  if (bus != other_bus) {
						  stop_and_interchange.second.push_back(other_bus);
					  }
				  }
			  }
			  response.stops.push_back(stop_and_interchange);
		  }
	  }

	  return response;
  }

  AllBusesResponse GetAllBuses() const {
	  return AllBusesResponse{ buses_to_stops };
  }
private:
	map<string, vector<string>> buses_to_stops;
	map<string, vector<string>> stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
