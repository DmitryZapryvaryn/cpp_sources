#include "../../../test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = size_t;
  using Priority = int;

  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
	  Id id = data.size();
	  data.push_back({ move(object), 0 });
	  sorted_keys.insert({0, id});
	  return id;
  }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
	  IdOutputIt ids_begin) {
	  for (auto it = range_begin; it != range_end; ++it) {
		  *(ids_begin++) = Add(move(*it));
	  }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
	  return id >= 0 && id < data.size() && data[id].second != NONE_PRIORITY;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
	  return data[id].first;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
	  Priority priority = data[id].second++;
	  sorted_keys.erase({ priority, id });
	  sorted_keys.insert({ priority + 1, id });
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
	  const auto max_key_it = prev(sorted_keys.end());
	  return data[max_key_it->second];
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
	  const auto max_key_it = prev(sorted_keys.end());

	  Priority priority = max_key_it->first;
	  Id id = max_key_it->second;

	  sorted_keys.erase(max_key_it);
	  data[id].second = -1;

	  return { move(data[id].first), priority };
  }

private:
	using PriorityPair = pair<Priority, Id>;

	// Возможно лучше будет структура для лучшей читаемости
	//struct Data {
	//	T value;
	//	Priority priority;
	//};
	using Data = pair<T, Priority>;

	const int NONE_PRIORITY = -1;

	set<PriorityPair> sorted_keys;
	vector<Data> data;
};

class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
