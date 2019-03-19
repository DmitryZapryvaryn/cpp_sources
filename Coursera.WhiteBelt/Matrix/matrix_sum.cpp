#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

// Реализуйте здесь
// * класс Matrix
class Matrix {
public:
	Matrix() {
		n_rows = 0;
		n_columns = 0;
	}

	Matrix(int num_rows, int num_cols) {
		Reset(num_rows, num_cols);
	}

	void Reset(int num_rows, int num_cols) {
		if (num_rows < 0 ) {
			throw out_of_range("num_rows must be >= 0");
		}
		if (num_cols < 0) {
			throw out_of_range("num_columns must be >= 0");
		}
		if (num_rows == 0 || num_cols == 0) {
			num_rows = num_cols = 0;
		}

		n_rows = num_rows;
		n_columns = num_cols;
		data.assign(n_rows, vector<int>(n_columns));
	}

	int At(int row, int col) const {
		return data.at(row).at(col);
	}

	int& At(int row, int col) {
		return data.at(row).at(col);
	}

	int GetNumRows() const {
		return n_rows;
	}

	int GetNumColumns() const {
		return n_columns;
	}

private:
	int n_rows;
	int n_columns;
	vector<vector<int>> data;
};
// * оператор ввода для класса Matrix из потока istream
istream& operator >>(istream& input, Matrix& m) {
	int r, c;
	input >> r >> c;
	m.Reset(r, c);
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			input >> m.At(i, j);
		}
	}

	return input;
}
// * оператор вывода класса Matrix в поток ostream
ostream& operator <<(ostream& output, const Matrix& m) {
	output << m.GetNumRows() << " " << m.GetNumColumns() << endl;

	for (int i = 0; i < m.GetNumRows(); ++i) {
		for (int j = 0; j < m.GetNumColumns(); ++j) {
			if (j > 0) {
				output << " ";
			}
			output << m.At(i, j);
		}
		output << endl;
	}

	return output;
}
// * оператор проверки на равенство двух объектов класса Matrix
bool operator ==(const Matrix& lhs, const Matrix& rhs) {
	if ((lhs.GetNumColumns() != rhs.GetNumColumns()) || (lhs.GetNumRows() != rhs.GetNumRows())) {
		return false;
	}

	for (int i = 0; i < lhs.GetNumRows(); ++i) {
		for (int j = 0; j < lhs.GetNumColumns(); ++j) {
			if (lhs.At(i, j) != rhs.At(i, j)) {
				return false;
			}
		}
	}
	
	return true;
}
// * оператор сложения двух объектов класса Matrix
Matrix operator +(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() != rhs.GetNumRows()) {
		throw invalid_argument("Mismatched number of rows");
	}
	if (lhs.GetNumColumns() != rhs.GetNumColumns()) {
		throw invalid_argument("Mismatched number of columns");
	}
	
	Matrix sum(lhs.GetNumRows(), lhs.GetNumColumns());
	for (int i = 0; i < sum.GetNumRows(); ++i) {
		for (int j = 0; j < sum.GetNumColumns(); ++j) {
			sum.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}

	return sum;
}

int main() {
	Matrix one;
	Matrix two;

	cin >> one >> two;
	cout << one + two << endl;

	return 0;
}
