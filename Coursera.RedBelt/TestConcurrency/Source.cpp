#include <iostream>
#include <vector>
#include <future>

using namespace std;


int64_t HeavyTask() {

	cout << this_thread::get_id << "\n";
	int64_t sum = 0;
	for (int64_t i = 0; i < 1000000; ++i) {
		sum += i;
	}

	return sum;
}

int main() {

	vector<future<int64_t>> futures;
	for (int i = 0; i < 10; ++i) {
		futures.push_back(async(HeavyTask));
	}

	for (auto& f : futures) {
		f.get();
	}

	return 0;
}