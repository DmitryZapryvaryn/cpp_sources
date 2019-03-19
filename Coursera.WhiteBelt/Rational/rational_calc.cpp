#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Rational {
public:
	Rational() {
		numerator = 0;
		denominator = 1;
	}

	Rational(int new_numerator, int new_denominator) {
		if (new_denominator == 0) {
			throw invalid_argument("Invalid argument");
		}

		int divisor = GreatestCommonDivisor(new_numerator, new_denominator);
		numerator = new_numerator / divisor;
		denominator = new_denominator / divisor;

		if (new_denominator < 0) {
			numerator = -numerator;
			denominator = -denominator;
		}
	}

	int Numerator() const {
		return numerator;
	}

	int Denominator() const {
		return denominator;
	}

private:
	int numerator;
	int denominator;

	int GreatestCommonDivisor(int a, int b) const {
		a = abs(a);
		b = abs(b);
		while (a > 0 && b > 0) {
			if (a > b) {
				a %= b;
			}
			else {
				b %= a;
			}
		}
		return a + b;
	}
};

Rational operator -(const Rational& rhs) {
	return Rational(-rhs.Numerator(), rhs.Denominator());
}

Rational operator +(const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == rhs.Denominator()) {
		return Rational(lhs.Numerator() + rhs.Numerator(), lhs.Denominator());
	}
	else {
		int denominator = lhs.Denominator() * rhs.Denominator();

		int numerator = lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator();

		return Rational(numerator, denominator);
	}
}

Rational operator -(const Rational& lhs, const Rational& rhs) {
	return lhs + (-rhs);
}

Rational operator *(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator /(const Rational& lhs, const Rational& rhs) {
	if (rhs.Numerator() == 0) {
		throw domain_error("Division by zero");
	}
	return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

bool operator ==(const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() == rhs.Numerator())
		&& (lhs.Denominator() == rhs.Denominator());
}

bool operator <(const Rational& lhs, const Rational& rhs) {
	if (lhs.Numerator() == rhs.Numerator()) {
		return lhs.Denominator() > rhs.Denominator();
	}
	else if (lhs.Denominator() == rhs.Denominator()) {
		return lhs.Numerator() < rhs.Numerator();
	}
	return (lhs - rhs).Numerator() < 0;
}

ostream& operator <<(ostream& output, const Rational& rhs) {
	output << rhs.Numerator() << "/" << rhs.Denominator();
	return output;
}

istream& operator >>(istream& input, Rational& rhs) {
	int p, q;
	char c;
	input >> p >> c >> q;
	// TODO: if(istream) !!!
	if (input && c == '/') rhs = Rational(p, q);
	return input;
}

int main() {
	Rational r1, r2;
	char operation;

	try {
		cin >> r1 >> operation >> r2;
		switch (operation) {
			case '+':
				cout << r1 + r2;
				break;
			case '-':
				cout << r1 - r2;
				break;
			case '*':
				cout << r1 * r2;
				break;
			case '/':
				cout << r1 / r2;
				break;
		}
	}
	catch (invalid_argument ia) {
		cout << ia.what();
	}
	catch (domain_error de) {
		cout << de.what();
	}

	return 0;
}
