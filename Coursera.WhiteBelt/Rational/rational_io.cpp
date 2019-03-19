#include <iostream>
#include <sstream>
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

// Реализуйте для класса Rational операторы << и >>
ostream& operator <<(ostream& output, const Rational& rhs) {
	output << rhs.Numerator() << "/" << rhs.Denominator();
	return output;
}

istream& operator >>(istream& input, Rational& rhs) {
	int p = rhs.Numerator(), q = rhs.Denominator();
	input >> p;
	input.ignore(1);
	input >> q;
	rhs = Rational(p, q);
	return input;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}
