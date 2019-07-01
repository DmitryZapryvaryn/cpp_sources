#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <string_view>
using namespace std;

class InvertedIndex {
public:
	InvertedIndex() {
		docs.reserve(50000);
	}
  void Add(string&& document);
  vector<pair<size_t, size_t>> Lookup(const string_view word) const;

  const string& GetDocument(size_t id) const {
    return docs[id];
  }

  const size_t GetDocSize() const {
	  return docs.size();
  }

private:
	map<string_view, vector<pair<size_t,size_t>>> index;
	//map<string_view, vector<size_t>> index;
	vector<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
