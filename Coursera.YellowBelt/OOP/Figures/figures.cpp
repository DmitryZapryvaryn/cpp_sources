#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <memory>
#include <math.h>

using namespace std;

constexpr auto PI = 3.14;

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
};

class Circle : public Figure {
public:
	Circle(const double& r) : radius(r) {}

	string Name() const override {
		return "CIRCLE";
	}

	double Perimeter() const override {
		return 2 * PI * radius;
	}

	double Area() const override {
		return PI * radius * radius;
	}

private:
	const double radius;
};

class Rect : public Figure {
public:
	Rect(const double& w, const double& h) : width(w), height(h) {}

	string Name() const override {
		return "RECT";
	}

	double Perimeter() const override {
		return 2 * (width + height);
	}

	double Area() const override {
		return width * height;
	}

private:
	const double width, height;
};

class Triangle : public Figure {
public:
	Triangle(const double& a, const double& b, const double& c) : sideA(a), sideB(b), sideC(c) {}

	string Name() const override {
		return "TRIANGLE";
	}

	double Perimeter()const override {
		return sideA + sideB + sideC;
	}

	double Area() const override {
		const double p = Perimeter() / 2;
		return sqrt(p * (p - sideA) * (p - sideB) * (p - sideC));
	}

private:
	const double sideA, sideB, sideC;
};

shared_ptr<Figure> CreateFigure(istringstream& is) {
	string figure_name;
	is >> figure_name;
	if (figure_name == "CIRCLE") {
		double r;
		is >> r;
		return make_shared<Circle>(r);
	}
	else if (figure_name == "RECT") {
		double w, h;
		is >> w >> h;
		return make_shared<Rect>(w, h);

	}
	else if (figure_name == "TRIANGLE") {
		double a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	}
}

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
					<< current_figure->Name() << " "
					<< current_figure->Perimeter() << " "
					<< current_figure->Area() << endl;
			}
		}
	}
	return 0;
}