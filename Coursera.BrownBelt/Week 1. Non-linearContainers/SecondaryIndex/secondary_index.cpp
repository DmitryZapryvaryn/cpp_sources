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

template<typename Key, typename Value>
class SecondaryIndex {
public:
	void Erase(const Key& key, const Value& id) {

		auto lo_hi = index.equal_range(key);

		for (auto it = lo_hi.first; it != lo_hi.second; ++it) {
			if (it->second == id) {
				index.erase(it);
				break;
			}
		}
	}
	void Insert(const Key& new_key, const Value& new_value) {
		index.insert({ new_key, new_value });
	}

	const auto& GetIndex() const {
		return index;
	}

private:
	multimap<Key, Value> index;
};

class Database {
public:
	bool Put(const Record& record) {
		if (db.find(record.id) == db.end()) {

			db.insert({ record.id, record });

			user_index.Insert(record.user, record.id);
			timestamp_index.Insert(record.timestamp, record.id);
			karma_index.Insert(record.karma, record.id);

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
			user_index.Erase(it->second.user, id);
			timestamp_index.Erase(it->second.timestamp, id);
			karma_index.Erase(it->second.karma, id);

			db.erase(id);

			return true;
		}

		return false;
	}

	template <typename Callback>
	void RangeByTimestamp(int low, int high, Callback callback) const {
		for (auto it = timestamp_index.GetIndex().lower_bound(low);
			it != timestamp_index.GetIndex().upper_bound(high);
			++it) {

			if (auto i = db.find(it->second); i == db.end() || !callback(i->second)) {
				break;
			}
		}
	}

	template <typename Callback>
	void RangeByKarma(int low, int high, Callback callback) const {
		for (auto it = karma_index.GetIndex().lower_bound(low);
			it != karma_index.GetIndex().upper_bound(high);
			++it) {
		
			if (auto i = db.find(it->second); i == db.end() || !callback(i->second)) {
				break;
			}
		}
	}

	template <typename Callback>
	void AllByUser(const string& user, Callback callback) const {
		auto lo_hi = user_index.GetIndex().equal_range(user);
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
	SecondaryIndex<string, string> user_index;
	SecondaryIndex<int, string> timestamp_index;
	SecondaryIndex<int, string> karma_index;


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
