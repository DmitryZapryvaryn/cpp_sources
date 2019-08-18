#include <iostream>
#include <memory>


using namespace std;

class Child1;
class Child2;

struct Parent {
	virtual ~Parent() = default;

	virtual void foo(const Parent& that) const = 0;
	virtual void fooWith(const Child1& that) const = 0;
	virtual void fooWith(const Child2& that) const = 0;
};

struct Child1 : public Parent {
	void foo(const Parent& that) const {
		cout << "Child1::foo" << endl;
		that.fooWith(*this);
	};
	void fooWith(const Child1& that) const {
		cout << "Child1::fooWith(Child1)" << endl;
	};
	void fooWith(const Child2& that) const {
		cout << "Child1::fooWith(Child2)" << endl;
	};
};

struct Child2 : public Parent {
	void foo(const Parent& that) const {
		cout << "Child2::foo" << endl;
		that.fooWith(*this);
	};
	void fooWith(const Child1& that) const {
		cout << "Child2::fooWith(Child1)" << endl;
	};
	void fooWith(const Child2& that) const {
		cout << "Child2::fooWith(Child2)" << endl;
	};
};

void bar(const Parent& first, const Parent& second) {
	second.foo(first);
}

int main() {
	Parent* ch11 = &Child1();
	Parent* ch21 = &Child2();
	Parent* ch12 = &Child1();
	Parent* ch22 = &Child2();

	cout << "Child 1 - Child 1: " << endl;
	bar(*ch11, *ch12);
	cout << "Child 1 - Child 2: " << endl;
	bar(*ch11, *ch21);
	cout << "Child 2 - Child 1: " << endl;
	bar(*ch21, *ch11);
	cout << "Child 2 - Child 2: " << endl;
	bar(*ch21, *ch22);

	return 0;
}