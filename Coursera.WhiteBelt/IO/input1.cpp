#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
	ifstream fin("input.txt");
	string out_line;

	while (getline(fin, out_line)) {
		cout << out_line << endl;
	}
}