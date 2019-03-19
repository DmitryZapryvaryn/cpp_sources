#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {

	ifstream fin("input.txt");

	int N, M;
	fin >> N >> M;
	
	int n, i = 0, j = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			fin >> n;
			cout << setw(10) << n;
			fin.ignore(1);
			if (j != (M - 1)) { 
				cout << " ";
			}
		}
		if (i != (N - 1)) {
			cout << endl;
		}
	}

	return 0;
}