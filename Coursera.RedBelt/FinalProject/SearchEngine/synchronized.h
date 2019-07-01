#pragma once

#include <mutex>

using namespace std;

template <typename T>
class Synchronized {
public:
	// не забывать использовать move() если параметр передаётся по значению
	explicit Synchronized(T initial = T()) : value(move(initial)) {}

	struct Access {
		T& ref_to_value;
		lock_guard<mutex> guard;
	};

	Access GetAccess() {
		return { value, lock_guard<mutex>(m) };
	}
private:
	mutex m;
	T value;
};