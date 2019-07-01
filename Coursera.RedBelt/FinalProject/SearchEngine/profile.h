#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;


class LogDuration {
public:
	explicit LogDuration(const string& msg = "") : message(msg + ": "), start(steady_clock::now()) {}

	~LogDuration() {
		auto finish = steady_clock::now();
		auto duration = finish - start;
		cerr << message << duration_cast<milliseconds>(duration).count() << " ms" << endl;
	}

private:
	string message;
	steady_clock::time_point start;
};

#define CONCAT_IMPL(a, b) a##b
#define UNIQ_ID(lineno) CONCAT_IMPL(_local_uniq_var_, lineno)

#define LOG_DURATION(msg) \
	LogDuration UNIQ_ID(__LINE__) {msg};

struct TotalDuration {
	string message;
	steady_clock::duration value;
	explicit TotalDuration(const string& msg = "")
		: message(msg + ": ")
		, value(0)
	{
	}
	~TotalDuration() {
		ostringstream _total_duration_os;
		_total_duration_os << message
			<< duration_cast<milliseconds>(value).count()
			<< " ms" << endl;
		cerr << _total_duration_os.str();
	}
};

class AddDuration {
public:
	explicit AddDuration(steady_clock::duration& dest)
		: add_to(dest)
		, start(steady_clock::now())
	{
	}
	explicit AddDuration(TotalDuration& dest)
		: AddDuration(dest.value)
	{
	}
	~AddDuration() {
		add_to += steady_clock::now() - start;
	}
private:
	steady_clock::duration& add_to;
	steady_clock::time_point start;
};

#define ADD_DURATION(value) \
	AddDuration UNIQ_ID(__LINE__) {value};