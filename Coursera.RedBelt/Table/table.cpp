#include "test_runner.h"

#include <vector>
#include <tuple>

using namespace std;

template<typename T>
class Table {
public:
	Table() {
		rows_n = 0;
		columns_n = 0;
		table.assign(0, vector<T>(0));
	}

	explicit Table(const size_t rows, const size_t columns) {
		Resize(rows, columns);
	}

	pair<size_t, size_t> Size() const {
		return { rows_n, columns_n };
	}

	void Resize(const size_t new_rows, const size_t new_cols) {
		rows_n = new_rows;
		columns_n = new_cols;
		table.resize(rows_n);
		for (auto& item : table) {
			item.resize(columns_n);
		}
	}

	const vector<const T>& operator[] (const size_t row_index) const {
		return table[row_index];
	}

	vector<T>& operator[] (const size_t row_index) {
		return table[row_index];
	}

private:
	size_t rows_n, columns_n;
	vector<vector<T>> table;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
