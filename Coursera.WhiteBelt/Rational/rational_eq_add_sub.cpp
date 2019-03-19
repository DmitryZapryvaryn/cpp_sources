#include <iostream>
using namespace std;

int GreatestCommonDivisor(int a, int b) {
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

int LeastCommonMultiple(int a, int b) {
	a = abs(a);
	b = abs(b);
	return (a * b) / GreatestCommonDivisor(a, b);
}

class Rational {
public:
	Rational() {
		numerator = 0;
		denominator = 1;
	}

	Rational(int new_numerator, int new_denominator) {
		int divisor = GreatestCommonDivisor(new_numerator, new_denominator);
		if (new_numerator == 0) {
			numerator = new_numerator;
			denominator = 1;
		}
		else if ((new_numerator > 0 && new_denominator > 0) || (new_numerator < 0 && new_denominator > 0)) {
			numerator = new_numerator / divisor;
			denominator = new_denominator / divisor;
		}
		else if ((new_numerator < 0 && new_denominator < 0) || (new_numerator > 0 && new_denominator < 0)) {
			numerator = -new_numerator / divisor;
			denominator = -new_denominator / divisor;
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
};

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
	if (lhs.Denominator() == rhs.Denominator()) {
		return Rational(lhs.Numerator() - rhs.Numerator(), lhs.Denominator());
	}
	else {
		int denominator = lhs.Denominator() * rhs.Denominator();

		int numerator = lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator();

		return Rational(numerator, denominator);
	}
}

bool operator ==(const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator());
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

	{
		Rational a(5, 7);
		Rational b(2, 9);
		Rational c = a - b;
		bool equal = c == Rational(31, 63);
		if (!equal) {
			cout << "5/7 - 2/9 != 31/63" << endl;
			return 3;
		}
	}

	{
		Rational a(3, 4);
		Rational b(-2, 3);
		Rational c = a + b;
		bool equal = c == Rational(1, 12);
		if (!equal) {
			cout << "3/4 + -2/3 != 1/12" << endl;
			return 2;
		}
	}

    cout << "OK" << endl;
    return 0;
}
