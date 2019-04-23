#include <vector>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

constexpr int N = 2'000'000;

vector<int> fillBigVector() {
	vector<int> result;
	for (int i = 0; i < N; ++i) {
		result.push_back(i);
	}

	return result;
}

vector<int> fillReservedBigVectorWithPushBack() {
	vector<int> result;
	result.reserve(N);
	for (int i = 0; i < N; ++i) {
		result.push_back(i);
	}

	return result;
}

vector<int> fillReservedBigVectorWithEmplaceBack() {
	vector<int> result;
	result.reserve(N);
	for (int i = 0; i < N; ++i) {
		result.emplace_back(i);
	}

	return result;
}


vector<int> fillReservedBigVectorWithAssignment() {
	vector<int> result;
	result.resize(N);
	for (int i = 0; i < N; ++i) {
		result[i] = i;
	}

	return result;
}

int main() {
	auto start1 = system_clock::now();
	auto v1 = fillBigVector();
	auto finish1 = system_clock::now();
	auto duration1 = finish1 - start1;
	auto simple = duration_cast<milliseconds>(duration1).count();

	auto start2 = system_clock::now();
	auto v2 = fillReservedBigVectorWithPushBack();
	auto finish2 = system_clock::now();
	auto duration2 = finish2 - start2;
	auto preallocPushBack = duration_cast<milliseconds>(duration2).count();

	auto start3 = system_clock::now();
	auto v3 = fillReservedBigVectorWithEmplaceBack();
	auto finish3 = system_clock::now();
	auto duration3 = finish3 - start3;
	auto preallocEmplaceBack = duration_cast<milliseconds>(duration3).count();

	auto start4 = system_clock::now();
	auto v4 = fillReservedBigVectorWithAssignment();
	auto finish4 = system_clock::now();
	auto duration4 = finish4 - start4;
	auto preallocAssignment = duration_cast<milliseconds>(duration4).count();

	cout << "Without preallocation: " << simple << endl;
	cout << "Preallocated with push_back(): " << preallocPushBack << endl;
	cout << "Preallocated with emplace_back(): " << preallocEmplaceBack << endl;
	cout << "Preallocated with assignment: " << preallocAssignment << endl;

	return 0;
}