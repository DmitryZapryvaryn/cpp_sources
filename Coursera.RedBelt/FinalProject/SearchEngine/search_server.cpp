#include "search_server.h"
#include "iterator_range.h"

//#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string_view> SplitIntoWords(const string& line) {
	string_view line_view = line;

	vector<string_view> result;

	while (true) {
		size_t not_space_pos = line_view.find_first_not_of(' ');
		if (not_space_pos == line_view.npos) {
			break;
		}

		size_t space_pos = line_view.find_first_of(' ', not_space_pos);
		result.push_back(line_view.substr(not_space_pos, space_pos - not_space_pos));

		if (space_pos == line_view.npos) {
			break;
		}
		else {
			line_view.remove_prefix(space_pos + 1);
		}
	}

	return result;
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  index = move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
	size_t index_size = index.GetDocSize();
	vector<pair<size_t, size_t>> search_result(index_size);
	for (string current_query; getline(query_input, current_query); ) {
		const auto& words = SplitIntoWords(current_query);
		for (size_t i = 0; i < index_size; ++i) {
			search_result[i] = { i, 0 };
		}

		for (const auto word : words) {
			for (const auto [docid, count] : index.Lookup(word)) {
				search_result[docid].second += count;
			}
		}

		partial_sort(
			begin(search_result),
			next(begin(search_result), min<size_t>(5, search_result.size())),
			end(search_result),
			[](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
				int64_t lhs_docid = lhs.first;
				auto lhs_hit_count = lhs.second;
				int64_t rhs_docid = rhs.first;
				auto rhs_hit_count = rhs.second;
				return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
			}
		);

		search_results_output << current_query << ':';
		for (auto [docid, hitcount] : Head(search_result, 5)) {
			if (hitcount == 0) { break; }
			search_results_output << " {"
				<< "docid: " << docid << ", "
				<< "hitcount: " << hitcount << '}';
		}
		search_results_output << endl;
	}
}

void InvertedIndex::Add(string&& document) {
  docs.emplace_back(move(document));

  const size_t docid = docs.size() - 1;
  for (const auto word : SplitIntoWords(docs.back())) {
	  if (index.count(word) > 0 && index[word].back().first == docid) {
		  auto& current_docid_count = index[word];
		  ++current_docid_count.back().second;
	  }
	  else {
		  index[word].push_back({ docid, 1 });
	  }
  }
}

vector<pair<size_t, size_t>> InvertedIndex::Lookup(const string_view word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}
