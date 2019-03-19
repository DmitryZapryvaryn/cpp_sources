#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	string out_line;

	while (getline(fin, out_line)) {
		fout << out_line << endl;;
	}
}