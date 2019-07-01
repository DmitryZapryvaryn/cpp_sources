#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>

using namespace std;

class ReadingManager {
public:
	ReadingManager() : user_count(MAX_PAGE_COUNT_, 0) {}

	void Read(int user_id, int page_count) {
		if (users_.count(user_id) < 1) {
			users_[user_id] = page_count;
			++user_count[page_count];
		}
		else {
			const int old_page_count = users_.at(user_id);
			--user_count[old_page_count];
			users_.at(user_id) = page_count;
			++user_count[page_count];
		}
	}

	double Cheer(int user_id) const {
		if (users_.size() == 0u || users_.count(user_id) == 0u) return 0.0;

		const int page_count = users_.at(user_id);
		if (page_count == 0) return 0.0;

		int sum_of_user = 0;
		for (int i = 1; i < page_count; ++i) {
			sum_of_user += user_count[i];
		}

		if (sum_of_user == 0) {
			for (int i = page_count + 1; i < MAX_PAGE_COUNT_; ++i) {
				if (user_count[i] > 0) return 0.0;
			}

			if (user_count[page_count] != 1) return 0.0;

			return 1.0;
		}

		return sum_of_user * 1.0 / (users_.size() - 1);
	}

private:
	static const int MAX_PAGE_COUNT_ = 1000;

	vector<int> user_count;
	map<int, int> users_;
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) { // O(Q)
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count); // O(Q)
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n"; // O(Q)
    }
  }

  return 0;
}