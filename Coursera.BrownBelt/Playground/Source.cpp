#include <iostream>
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>


using namespace std;

template<typename T>
void printVector(const vector<T> vec) {
	bool first = true;
	for (const auto value : vec) {
		if (first) {
			cout << value;
			first = false;
		}
		else { cout << " " << value; }
	}
}

struct Test {
	int num;
	bool b;

	friend istream& operator>> (istream& in, Test& t) {
		char b;

		in >> t.num >> b;
		
		t.b = b == 't';

		return in;
	}

	friend ostream& operator<< (ostream& out, const Test& t) {
		return out << t.num << ' ' << std::boolalpha << t.b;
	}
};

int main() {
	
	Test t;
	cin >> t;
	cout << t;
	
	/*vector<Test> numbers = { {1, true}, {2, false}, {3, false}, {4, true}, {5, false}, {6, true} };

	vector<Test> v1;
	vector<Test> v2;

	partition_copy(
		begin(numbers),
		end(numbers),
		back_inserter(v1),
		back_inserter(v2),
		[](const Test& n) {
			return n.b;
		});

	cout << "v1:\n";
	printVector(v1);
	cout << "\n";
	cout << "v2:\n";
	printVector(v2);
	cout << "\n";*/

	return 0;
}