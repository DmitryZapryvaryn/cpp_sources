#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define CONCAT(a, b) a##b
#define EXPAND(a, b) CONCAT(a, b)
#define UNIQ_ID EXPAND(var_, __LINE__)

int main() {
	int UNIQ_ID = 0;
	string UNIQ_ID = "hello";
	vector<string> UNIQ_ID = { "hello", "world" };
	vector<int> UNIQ_ID = { 1, 2, 3, 4 };
}