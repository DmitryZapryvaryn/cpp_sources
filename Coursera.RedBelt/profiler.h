#pragma once

#include <string>
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