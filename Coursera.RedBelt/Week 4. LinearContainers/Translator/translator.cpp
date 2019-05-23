#include "../../test_runner.h"
#include "../../profiler.h"
#include <string>
#include <string_view>
#include <deque>

using namespace std;

class Translator {
public:
	void Add(string_view source, string_view target) {
		const string_view source_copy = GetStringView(source);
		const string_view target_copy = GetStringView(target);

		dict_forward[source_copy] = target_copy;
		dict_backward[target_copy] = source_copy;
	}
	string_view TranslateForward(string_view source) const {
		return Translate(dict_forward, source);
	}
	string_view TranslateBackward(string_view target) const {
		return Translate(dict_backward, target);
	}

private:
	string_view GetStringView(string_view s) {
		// for ( const auto& i : {1, 2, 3})
		// i: 1, 2, 3
		// for (const auto[*|&] map : {&map1, &map2}) - для избежания копирования map используются адреса и указатели на map
		// *map: map1, map2 
		for (const auto* dict : { &dict_forward, &dict_backward }) {
			const auto it = dict->find(s);
			if (it != dict->end()) {
				return it->first;
			}
		}

		return data.emplace_back(s);
	}

	string_view Translate(const map<string_view, string_view>& dict, string_view s) const {
		
		// первый аргумент - инициализация пременной, которая живет только в рамках текущего if(;)
		if (const auto it = dict.find(s); it == dict.end()) {
			return {};
		}
		else {
			return it->second;
		}
	}

	map<string_view, string_view> dict_forward;
	map<string_view, string_view> dict_backward;

	deque<string> data;
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
