#include "test_runner.h"

#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

template<typename T>
class Deque {
public:
	Deque() {};

	bool Empty() const {
		return head.empty() && tail.empty();
	}

	size_t Size() const {
		return tail.size() + head.size();
	}

	T& operator[] (const size_t index) {
		if (index < head.size()) {
			return head[head.size() - index - 1];
		}
		else {
			return tail[index - head.size()];
		}
	}

	const T& operator[] (const size_t index) const {
		if (index < head.size()) {
			return head[head.size() - index - 1];
		}
		else {
			return tail[index - head.size()];
		}
	}

	T& At(const size_t index) {
		if (index >= Size()) throw out_of_range("");

		return (*this)[index];
	}

	const T& At(const size_t index) const {
		if (index >= Size()) throw out_of_range("");

		return (*this)[index];
	}

	T& Front() {
		if (head.empty()) {
			return tail.front();
		}

		return head.back();
	}

	const T& Front() const {
		if (head.empty()) {
			return tail.front();
		}

		return head.back();
	}

	T& Back() {
		if (tail.empty()) {
			return head[0];
		}

		return tail.back();
	}

	const T& Back() const {
		if (tail.empty()) {
			return head[0];
		}

		return tail.back();
	}

	void PushBack(T item) {
		tail.push_back(item);
	}

	void PushFront(T item) {
		head.push_back(item);
	}

private:
	vector<T> head;
	vector<T> tail;
};

void TestDeque() {
	Deque<int> deq;

	deq.PushBack(2);
	ASSERT_EQUAL(deq.Front(), 2);
	ASSERT_EQUAL(deq.Back(), 2);

	deq.PushBack(42);
	ASSERT_EQUAL(deq.Front(), 2);
	ASSERT_EQUAL(deq.Back(), 42);

	deq.PushFront(9);
	deq.PushBack(6);
	ASSERT_EQUAL(deq.Front(), 9);
	ASSERT_EQUAL(deq.Back(), 6);

	try {
		deq.At(5);
	}
	catch (out_of_range&) {}

	try {
		deq.At(-1);
	}
	catch (out_of_range&) {}

	ASSERT_EQUAL(deq.Size(), 4u);

	ASSERT_EQUAL(deq[0], 9);
	ASSERT_EQUAL(deq[1], 2);
	ASSERT_EQUAL(deq[2], 42);
	ASSERT_EQUAL(deq[3], 6);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestDeque);

	return 0;
}