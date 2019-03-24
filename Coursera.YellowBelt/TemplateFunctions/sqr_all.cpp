#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
using namespace std;

template <typename T>
T Sqr(T c);

template <typename T>
vector<T> Sqr(const vector<T>& v);

template <typename K, typename V>
map<K, V> Sqr(const map<K, V>& m);

template <typename L, typename R>
pair<L, R> Sqr(const pair<L, R>& p);

template<typename T>
T Sqr(T c)
{
	return c*c;
}

template<typename T>
vector<T> Sqr(const vector<T>& v)
{
	vector<T> result;
	for (const auto& i : v) {
		// Здесь важно, что вместо x * x вызывается функция Sqr:
		// это позволяет возводить в квадрат составные объекты
		result.push_back(Sqr(i));
	}
	return result;
}

template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& m)
{
	map<K, V> result;
	for (const auto&[k, v] : m) {
		result[k] = Sqr(v);
	}
	return result;
}

template<typename L, typename R>
pair<L, R> Sqr(const pair<L, R>& p)
{
	return { Sqr(p.first), Sqr(p.second) };
}