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

//class Rational {
//public:
//  // Вы можете вставлять сюда различные реализации,
//  // чтобы проверить, что ваши тесты пропускают корректный код
//  // и ловят некорректный
//
//  Rational();
//  Rational(int numerator, int denominator) {
//  }
//
//  int Numerator() const {
//  }
//
//  int Denominator() const {
//  }
//};

void TestDefaultConstructor() {
	Rational rational;
	AssertEqual(rational.Numerator(), 0, "line 115");
	AssertEqual(rational.Denominator(), 1, "line 116");
}

void TestConstructor() {
	Rational rational1(2, 3);
	AssertEqual(rational1.Numerator(), 2, "line 121");
	AssertEqual(rational1.Denominator(), 3, "line 122");

	Rational rational2(4, 12);
	AssertEqual(rational2.Numerator(), 1, "line 125");
	AssertEqual(rational2.Denominator(), 3, "line 126");

	Rational rational3(-2, 3);
	AssertEqual(rational3.Numerator(), -2, "line 129");
	AssertEqual(rational3.Denominator(), 3, "line 130");

	Rational rational4(1, -6);
	AssertEqual(rational4.Numerator(), -1, "line 133");
	AssertEqual(rational4.Denominator(), 6, "line 134");

	Rational rational5(-4, -5);
	AssertEqual(rational5.Numerator(), 4, "line 137");
	AssertEqual(rational5.Denominator(), 5, "line 138");

	Rational rational6(0, -5);
	AssertEqual(rational6.Numerator(), 0, "line 141");
	AssertEqual(rational6.Denominator(), 1, "line 142");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
  runner.RunTest(TestConstructor, "TestConstructor");
  return 0;
}
