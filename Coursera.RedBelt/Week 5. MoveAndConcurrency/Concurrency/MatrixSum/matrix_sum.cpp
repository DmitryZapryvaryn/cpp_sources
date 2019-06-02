#include "../../../test_runner.h"
#include <vector>
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
		size_t page_count = (end - begin) / page_size;
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

template<typename Container>
int64_t CalculatePartSum(const Container& matrix_part) {
	
	int64_t sum = 0;
	for (const auto& row : matrix_part) {
		for (auto i : row) {
			sum += i;
		}
	}

	return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
	vector<future<int64_t>> futures;
	//size_t page_size = matrix.size() / 4;
	for (auto& page : Paginate(matrix, 1)) {
		futures.push_back(async([=] {
			return CalculatePartSum(page); }));
	}

	int64_t sum = 0;
	for (auto& f : futures) {
		sum += f.get();
	}

	return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
