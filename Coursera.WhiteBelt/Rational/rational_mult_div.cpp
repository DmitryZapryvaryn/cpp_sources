#include <iostream>
using namespace std;

class Rational {
public:
	Rational() {
		numerator = 0;
		denominator = 1;
	}

	Rational(int new_numerator, int new_denominator) {
		int divisor = GreatestCommonDivisor(new_numerator, new_denominator);
		if ((new_numerator >= 0 && new_denominator > 0) || (new_numerator <= 0 && new_denominator > 0)) {
			numerator = new_numerator / divisor;
			denominator = new_denominator / divisor;
		}
		else if ((new_numerator <= 0 && new_denominator < 0) || (new_numerator >= 0 && new_denominator < 0)) {
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

bool operator ==(const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator());
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}
