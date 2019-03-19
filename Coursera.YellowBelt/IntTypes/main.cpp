#include <iostream>
#include <limits>

using namespace std;


int main() {

	cout << "int " << sizeof(int) << endl;

	int8_t x8 = -1;
	cout << "int8_t " << sizeof(int8_t) << endl;
	int16_t x16 = -1;
	cout << "int16_t " << sizeof(int16_t) << endl;
	int32_t x32 = -1;
	cout << "int32_t " << sizeof(int32_t) << endl;
	int64_t x64 = -1;
	cout << "int64_t " << sizeof(int64_t) << endl;

	uint8_t x8u = 1;
	cout << "uint8_t " << sizeof(uint8_t) << endl;
	uint16_t x16u = 1;
	cout << "uint16_t " << sizeof(uint16_t) << endl;
	uint32_t x32u = 1;
	cout << "uint32_t " << sizeof(uint32_t) << endl;
	uint64_t x64u = 1;
	cout << "uint8=64_t " << sizeof(uint64_t) << endl;

	cout << (x64 < x64u) << " " << (x64 < x32u) << " " << (x64 < x16u) << endl;

	cout << (x32 < x64u) << " " << (x32 < x32u) << " " << (x32 < x16u) << endl;

	cout << (x16 < x64u) << " " << (x16 < x32u) << " " << (x16 < x16u) << endl;

	return 0;
}