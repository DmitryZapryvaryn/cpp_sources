#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;


int main() {
	int N;
	uint16_t R;
	uint64_t W, H, D;
	uint64_t sum = 0u;

	cin >> N >> R;

	for (int i = 0; i < N; ++i) {
		cin >> W >> H >> D;
		sum += W * H * D;
	}
	
	cout << sum * R << endl;

	return 0;
}