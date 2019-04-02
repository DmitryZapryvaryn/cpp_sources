#include <vector>
#include <set>
#include <algorithm>

using namespace std;

template<typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T & border) {
	auto it = find_if(elements.begin(), elements.end(), [border](T el) { return el > border; });
	return { it, elements.end() };
}