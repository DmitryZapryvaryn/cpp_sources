#include "../../../profiler.h"
#include "../../../test_runner.h"

#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>
#include <iterator>
#include <future>
using namespace std;

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
	  for (const auto& [key, value] : other.word_frequences) {
		  word_frequences[key] += value;
	  }
  }
};

vector<string> Split(const string& line) {
	istringstream iss(line);

	return { istream_iterator<string>(iss),  istream_iterator<string>() };
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats result;
	for (auto& word : Split(line)) {
		if (key_words.count(word) > 0) {
			++result.word_frequences[word];
		}
	}

	return result;
}

Stats ExploreKeyWordsSingleThread(
  const set<string>& key_words, const vector<string>& input
) {
  Stats result;
  for (const string& line : input) {
    result += ExploreLine(key_words, line);
  }
  return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	vector<future<Stats>> futures;
	const size_t text_number_of_lines = 10000;
	vector<vector<string>> input_text;
	while (!input.eof()) {
		vector<string> text;
		text.reserve(text_number_of_lines);
		for (int i = 0; i < text_number_of_lines; ++i) {
			string str_buf;
			getline(input, str_buf);
			text.emplace_back(move(str_buf));
		}
		input_text.emplace_back(move(text));
	}

	for (auto& text : input_text) {
		futures.push_back(
			async(ExploreKeyWordsSingleThread, cref(key_words), cref(text)));
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

  const Stats stats = ExploreKeyWords(key_words, ss);
  
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
