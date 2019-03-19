#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
	ifstream fin("input.txt");

	double line;
	cout << fixed << setprecision(3);
	while (fin >> line) {
		cout << line << endl;
	}

	return 0;
}