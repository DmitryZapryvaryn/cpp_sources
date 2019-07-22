#include <map>
#include <unordered_map>
#include <string>
#include <iostream>


using namespace std;

int main() {
	multimap<string, int> mm;
	mm.insert({ "AAA", 1 });
	mm.insert({ "BBB", 2 });
	mm.insert({ "AAA", 3 });

	for (auto it = mm.lower_bound("AAA");
		it != mm.upper_bound("AAA");
		++it) {
		cout << it->second << endl;
	}

}