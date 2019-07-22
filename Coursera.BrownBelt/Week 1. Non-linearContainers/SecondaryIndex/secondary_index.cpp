#include "test_runner.h"

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

struct Record {
	string id;
	string title;
	string user;
	int timestamp;
	int karma;
};

class Database {
public:
	bool Put(const Record& record) {
		if (db.find(record.id) == db.end()) {

			db.insert({ record.id, record });

			user_index.insert({record.user, record.id});
			timestamp_index.insert({ record.timestamp, record.id });
			karma_index.insert({ record.karma, record.id });

			return true;
		}

		return false;
	}

	const Record* GetById(const string& id) const {
		auto it = db.find(id);
		if (it == db.end()) { return nullptr; }
		return &it->second;
	}

	bool Erase(const string& id) {
		if (auto it = db.find(id); it != db.end()) {

			// TODO: refactor, code duplication
			auto lo_hi1 = user_index.equal_range(it->second.user);
			for (auto it = lo_hi1.first; it != lo_hi1.second; ++it) {
				if (it->second == id) {
					user_index.erase(it);
					break;
				}
			}

			// TODO: refactor, code duplication
			auto lo_hi2 = timestamp_index.equal_range(it->second.timestamp);
			for (auto it = lo_hi2.first; it != lo_hi2.second; ++it) {
				if (it->second == id) {
					timestamp_index.erase(it);
					break;
				}
			}

			// TODO: refactor, code duplication
			auto lo_hi3 = karma_index.equal_range(it->second.karma);
			for (auto it = lo_hi3.first; it != lo_hi3.second; ++it) {
				if (it->second == id) {
					karma_index.erase(it);
					break;
				}
			}

			db.erase(id);

			return true;
		}

		return false;
	}

	// TODO: refactor, code duplication
	template <typename Callback>
	void RangeByTimestamp(int low, int high, Callback callback) const {
		for (auto it = timestamp_index.lower_bound(low);
			it != timestamp_index.upper_bound(high);
			++it) {

			if (auto i = db.find(it->second); i == db.end() || !callback(i->second)) {
				break;
			}
		}
	}

	// TODO: refactor, code duplication
	template <typename Callback>
	void RangeByKarma(int low, int high, Callback callback) const {
		for (auto it = karma_index.lower_bound(low);
			it != karma_index.upper_bound(high);
			++it) {
		
			if (auto i = db.find(it->second); i == db.end() || !callback(i->second)) {
				break;
			}
		}
	}

	// TODO: refactor, code duplication
	template <typename Callback>
	void AllByUser(const string& user, Callback callback) const {
		auto lo_hi = user_index.equal_range(user);
		for (auto it = lo_hi.first;
			it != lo_hi.second;
			++it) {

			if (auto i = db.find(it->second); i == db.end() || !callback(i->second)) {
				break;
			}
		}
	}

private:
	unordered_map<string, Record> db;
	multimap<string, string> user_index;
	multimap<int, string> timestamp_index;
	multimap<int, string> karma_index;


};

void TestRangeBoundaries() {
	const int good_karma = 1000;
	const int bad_karma = -10;

	Database db;
	db.Put({ "id1", "Hello there", "master", 1536107260, good_karma });
	db.Put({ "id2", "O>>-<", "general2", 1536107260, bad_karma });

	int count = 0;
	db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
		++count;
		return true;
		});

	ASSERT_EQUAL(2, count);
}

void TestSameUser() {
	Database db;
	db.Put({ "id1", "Don't sell", "master", 1536107260, 1000 });
	db.Put({ "id2", "Rethink life", "master", 1536107260, 2000 });

	int count = 0;
	db.AllByUser("master", [&count](const Record&) {
		++count;
		return true;
		});

	ASSERT_EQUAL(2, count);
}

void TestReplacement() {
	const string final_body = "Feeling sad";

	Database db;
	db.Put({ "id", "Have a hand", "not-master", 1536107260, 10 });
	db.Erase("id");
	auto not_existing_record = db.GetById("id");
	ASSERT(not_existing_record == nullptr);

	db.Put({ "id", final_body, "not-master", 1536107260, -10 });

	auto record = db.GetById("id");
	ASSERT(record != nullptr);
	ASSERT_EQUAL(final_body, record->title);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestRangeBoundaries);
	RUN_TEST(tr, TestSameUser);
	RUN_TEST(tr, TestReplacement);
	return 0;
}
