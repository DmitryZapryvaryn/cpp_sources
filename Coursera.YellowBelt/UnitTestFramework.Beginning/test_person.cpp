#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

/*
class Person {
public:
  // Вы можете вставлять сюда различные реализации класса,
  // чтобы проверить, что ваши тесты пропускают корректный код
  // и ловят некорректный
  void ChangeFirstName(int year, const string& first_name) {
  }
  void ChangeLastName(int year, const string& last_name) {
  }
  string GetFullName(int year) {
  }
};
*/

void TestIncognito() {
	Person p;
	AssertEqual(p.GetFullName(1900), "Incognito", "line 111");
}

void TestFirstNameWithoutLastName() {
	Person p;
	string first_name1 = "Greta";
	p.ChangeFirstName(1978, first_name1);
	AssertEqual(p.GetFullName(1980), first_name1 + " with unknown last name", "line 118");
	string first_name2 = "Fina";
	p.ChangeFirstName(1996, first_name2);
	AssertEqual(p.GetFullName(2000), first_name2 + " with unknown last name", "line 121");
}

void TestLastNameWithoutFirstName() {
	Person p;
	string last_name1 = "Henrike";
	p.ChangeLastName(1978, last_name1);
	AssertEqual(p.GetFullName(1980), last_name1 + " with unknown first name", "line 128");
	string last_name2 = "Redo";
	p.ChangeLastName(1996, last_name2);
	AssertEqual(p.GetFullName(2000), last_name2 + " with unknown first name", "line 131");
}

void TestFullName() {
	Person p;
	string first_name = "Great";
	string last_name = "Redo";
	p.ChangeFirstName(1978, first_name);
	p.ChangeLastName(1978, last_name);
	AssertEqual(p.GetFullName(1980), first_name + " " + last_name, "line 140");
	p.ChangeFirstName(1981, "Tara");
	AssertEqual(p.GetFullName(1992), "Tara " + last_name, "line 142");
	p.ChangeLastName(1982, "White");
	AssertEqual(p.GetFullName(1992), "Tara White", "line 144");
	AssertEqual(p.GetFullName(1980), first_name + " " + last_name, "line 145");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestIncognito, "TestIncognito");
  runner.RunTest(TestFirstNameWithoutLastName, "TestFirstNameWithoutLastName");
  runner.RunTest(TestLastNameWithoutFirstName, "TestLastNameWithoutFirstName");
  runner.RunTest(TestFullName, "TestFullName");
  return 0;
}