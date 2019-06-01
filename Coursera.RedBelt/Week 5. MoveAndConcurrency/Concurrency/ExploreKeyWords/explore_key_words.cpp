#include "../../../profiler.h"
#include "../../../test_runner.h"

#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <future>
using namespace std;

template<typename Iterator>
class IteratorRange {
public:
	IteratorRange(Iterator begin, Iterator end) : first(begin), last(end), size_(distance(first, last)) {}

	Iterator begin() const {
		return first;
	}

	Iterator end() const {
		return last;
	}

	size_t size() const {
		return size_;
	}

private:
	Iterator first, last;
	size_t size_;
};

template <typename Iterator>
class Paginator {
public:
	Paginator(Iterator begin, Iterator end, size_t page_size) {
		size_t page_count = distance(begin, end) / page_size;
		for (size_t i = 0; i < page_count; ++i) {
			auto next_iter = next(begin, page_size);
			pages.push_back({ begin, next_iter });
			begin = next_iter;
		}

		if (begin != end) {
			pages.push_back({ begin, end });
		}
	}

	size_t size() const {
		return pages.size();
	}

	auto begin() const {
		return pages.begin();
	}

	auto end() const {
		return pages.end();
	}

private:
	vector<IteratorRange<Iterator>> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator(c.begin(), c.end(), page_size);
}

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
	  for (const auto& [key, value] : other.word_frequences) {
		  word_frequences[key] += value;
	  }
  }
};

int CountOccurancies(const string& word, const string& line) {
	istringstream inss(line);
	int count = 0;
	while (!inss.eof()) {
		string tmp; inss >> tmp;
		if (tmp == word) {
			++count;
		}
	}

	return count;
}

template<typename Container>
Stats ExploreLineMulti(const Container& key_words, const string& line) {
	Stats result;
	for (const auto& key_word : key_words) {
		result.word_frequences[key_word] += CountOccurancies(key_word, line);
		if (result.word_frequences[key_word] == 0) { result.word_frequences.erase(key_word); }
	}

	return result;
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	for (const auto& key_word : key_words) {
		result.word_frequences[key_word] += CountOccurancies(key_word, line);
		if (result.word_frequences[key_word] == 0) { result.word_frequences.erase(key_word); }
	}

	return result;
}

template<typename Container>
Stats ExploreKeyWordsMultiThread(
	const Container& key_words, istream& input
) {
	Stats result;
	for (string line; getline(input, line); ) {
		result += ExploreLineMulti(key_words, line);
	}
	return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, istream& input
) {
  Stats result;
  for (string line; getline(input, line); ) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	LOG_DURATION("Multi Thread");
	const int CORE_NUMBER = 4;
	vector<future<Stats>> futures(4);
	for (const auto& page : Paginate(key_words, key_words.size() / CORE_NUMBER)) {
		futures.push_back(async([page, &input] { return ExploreKeyWordsMultiThread(page, input); }));
	}
	Stats result;
	for (auto& f : futures) {
		result += f.get();
	}

	return result;
}

void TestBasic() {
  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

  stringstream ss;
  ss << "this new yangle service really rocks\n";
  ss << "It sucks when yangle isn't available\n";
  ss << "10 reasons why yangle is the best IT company\n";
  ss << "yangle rocks others suck\n";
  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

  const auto stats = ExploreKeyWords(key_words, ss);
  const map<string, int> expected = {
    {"yangle", 6},
    {"rocks", 2},
    {"sucks", 1}
  };
  ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestBasic);
}
