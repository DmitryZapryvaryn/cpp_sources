#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0) : size(a_size) {
		if (a_size > N) {
			throw invalid_argument("");
		}
	}

	T& operator[](size_t index) {
		return data[index];
	}
	const T& operator[](size_t index) const {
		return data[index];
	}

	T* begin() {
		return data.begin();
	}
	T* end() {
		return data.begin() + size;
	}
	const T* begin() const {
		return data.cbegin();
	}
	const T* end() const {
		return data.cbegin() + size;
	}

	size_t Size() const {
		return size;
	}
	size_t Capacity() const {
		return N;
	}

	void PushBack(const T& value) {
		if (size == N) {
			throw overflow_error("");
		}
		data[size++] = value;
	}
	T PopBack() {
		if (size == 0) {
			throw underflow_error("");
		}

		return data[--size];
	}

private:
	array<T, N> data;
	size_t size;
};

