#include "test_runner.h"

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <algorithm>

using namespace std;

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {

	first = find_if(first, last, pred);

	if (first == last) return last;

	ForwardIterator max_iterator = first;
	++first;

	while(first != last) {
		if (pred(*first) && (*max_iterator < *first)) {
			max_iterator = first;
		}
		++first;
	}

	if (!pred(*max_iterator)) return last;

	return max_iterator;
}

void TestUniqueMax() {
  auto IsEven = [](int x) {
    return x % 2 == 0;
  };

  const list<int> hill{2, 4, 8, 9, 6, 4, 2};
  auto max_iterator = hill.begin();
  advance(max_iterator, 2);

  vector<int> numbers(10);
  iota(numbers.begin(), numbers.end(), 1);

  vector<int> first_not_suitable{1, 3, 0, 3};
  auto max_iterator_not_suitable = first_not_suitable.begin();
  advance(max_iterator_not_suitable, 2);

  /*
    Мы не используем AssertEqual, потому что для итераторов
    отсутствует перегрузка оператора вывода в поток ostream.
    Разыменование здесь также недопустимо, так как оно может повлечь
    неопределенное поведение, если функция max_element_if, к примеру,
    вернула итератор, указывающий на конец контейнера.
  */
  Assert(
    max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end(),
    "Expect the last element"
  );
  Assert(
    max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator,
    "Expect the maximal even number"
  );
  Assert(
	  max_element_if(first_not_suitable.begin(), first_not_suitable.end(), IsEven) == max_iterator_not_suitable,
	  "Returned end of the container but there is at least one suitable element"
  );
}

void TestSeveralMax() {
  struct IsCapitalized {
    bool operator()(const string &s) {
      return !s.empty() && isupper(s.front());
    }
  };

  const forward_list<string> text{"One", "two", "Three", "One", "Two",
    "Three", "one", "Two", "three"};
  auto max_iterator = text.begin();
  advance(max_iterator, 4);

  Assert(
    max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
    "Expect thr first \"Two\""
  );
}

void TestNoMax() {
  const vector<int> empty;
  const string str = "Non-empty string";

  auto AlwaysTrue = [](int) {
    return true;
  };
  Assert(
    max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end(),
    "Expect end for empty container"
  );

  auto AlwaysFalse = [](char) {
    return false;
  };
  Assert(
    max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end(),
    "Expect end for AlwaysFalse predicate"
  );
}

int main() {
  TestRunner tr;
  tr.RunTest(TestUniqueMax, "TestUniqueMax");
  tr.RunTest(TestSeveralMax, "TestSeveralMax");
  tr.RunTest(TestNoMax, "TestNoMax");
}