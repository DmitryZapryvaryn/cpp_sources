#include <map>
#include <string>
#include <iostream>
using namespace std;

template<typename K, typename V> V& GetRefStrict(const map<K, V>& m, const K& key);

template<typename K, typename V>
V& GetRefStrict(map<K, V>& m, const K & key)
{
	if (!m.count(key)) throw runtime_error("");

	return m.at(key);
}


int main() {
	map<int, string> m = { {0, "value"} };
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
}