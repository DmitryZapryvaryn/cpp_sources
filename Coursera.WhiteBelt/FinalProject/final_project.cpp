#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <set>
#include <map>

using namespace std;

struct Year {
	int value;
	explicit Year(int new_value) {
		value = new_value;
	}
};

struct Month {
	int value;

	explicit Month(int new_value) {
		if (new_value > 12 || new_value < 1) {
			string error_message = "Month value is invalid: " + to_string(new_value);
			throw range_error(error_message);
		}
		value = new_value;
	}
};

struct Day {
	int value;

	explicit Day(int new_value) {
		if (new_value > 31 || new_value < 1) {
			string error_message = "Day value is invalid: " + to_string(new_value);
			throw range_error(error_message);
		}
		value = new_value;
	}
};

class Date {
public:
	Date() {
		day = 1;
		month = 1;
		year = 0;
	}

	Date(Year new_year, Month new_month, Day new_day) {
		day = new_day.value;
		month = new_month.value;
		year = new_year.value;
	}

	Date(const string& string_date) {
		
	}

	int GetYear() const {
		return year;
	}

	int GetMonth() const {
		return month;
	}

	int GetDay() const {
		return day;
	}

	friend ostream& operator <<(ostream& output, const Date& date) {
		output << setfill('0');
		output << setw(4) << date.GetYear() << '-'
				<< setw(2) << date.GetMonth() << '-' 
				<< setw(2) << date.GetDay();

		return output;
	}

private:
	int day;
	int month;
	int year;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth()) {
		return lhs.GetDay() < rhs.GetDay();
	}
	else if (lhs.GetYear() == rhs.GetYear()) {
		return lhs.GetMonth() < rhs.GetMonth();
	}
	else {
		return lhs.GetYear() < rhs.GetYear();
	}
}

Date ParseDate(const string& str_date) {

	stringstream ss(str_date);
	int y, m, d;
	char delimeter1, delimeter2;
	char any;
	Date date;
	ss >> y >> delimeter1 >> m >> delimeter2 >> d;
	
	if (ss && delimeter1 == '-' && delimeter2 == '-' && ss.eof()) {
		Month month = Month(m);
		Day day = Day(d);
		date = Date(Year(y), month, day);
	}
	else {
		throw domain_error("Wrong date format: " + str_date);
	}

	return date;
}

void PrintSet(const set<string>& set_str) {
	for (const auto& str : set_str) {
		cout << str << endl;
	}
}


class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		events[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event) {
		return (events.count(date) == 0) || (events[date].count(event) == 0) ?
			false : events[date].erase(event);
	}
	int DeleteDate(const Date& date) {
		int events_count = 0;
		if (events.count(date) > 0) {
			events_count = events[date].size();
			events.erase(date);
		}

		return events_count;
	}

	set<string> Find(const Date& date) const {
		if (events.count(date) == 0) {
			return {};
		}
		return events.at(date);
	}
  
	void Print() const {
		for (const auto& item : events) {
			for (const auto& elem : item.second) {
				cout << item.first << " " << elem << endl;
			}
		}
	}

private:
	map<Date, set<string>> events;
};

int main() {
  Database db;

  string command;
  try {
	  while (getline(cin, command)) {
		  stringstream ss(command);
		  string command;
		  ss >> command;
		  if (command == "Add") {
			  string date, event;
			  ss >> date >> event;
			  if (!event.empty())
				db.AddEvent(ParseDate(date), event);
		  }
		  else if (command == "Del") {
			  string sdate, event;
			  ss >> sdate >> event;
			  Date date = ParseDate(sdate);
			  if (event.empty()) {
				  cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
			  }
			  else {
				  db.DeleteEvent(date, event) ?
					  cout << "Deleted successfully" << endl :
					  cout << "Event not found" << endl;
			  }
		  }
		  else if (command == "Find") {
			  string sdate;
			  ss >> sdate;
			  Date date = ParseDate(sdate);
			  PrintSet(db.Find(date));
		  }
		  else if (command == "Print") {
			  db.Print();
		  }
		  else if (!command.empty()) {
			  cout << "Unknown command: " << command << endl;
			  break;
		  }
	  }
  }
  catch (exception& er) {
	  cout << er.what() << endl;
  }

  return 0;
}