#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
	Person(const string& new_name, const string& new_type) : name(new_name), type(new_type) {}

	string Log() const {
		return type + ": " + name;
	}

	virtual void Walk(const string& destination) const {
		cout << Log() << " walks to: " << destination << endl;
	}

	const string type;
	const string name;
};

class Student : public Person {
public:

	Student(const string& name, const string& favouriteSong_) 
		: Person(name, "Student"), favouriteSong(favouriteSong_) {
	}

	void Learn() const {
		cout << Log() << " learns" << endl;
	}

	void Walk(const string& destination) const {
		cout << Log() << " walks to: " << destination << endl;
		cout << Log() << " sings a song: " << favouriteSong << endl;
	}

	void SingSong() const {
		cout << Log() << " sings a song: " << favouriteSong << endl;
	}

private:
	const string favouriteSong;
};


class Teacher : public Person {
public:

	Teacher(const string& name, const string& subject_) : Person(name, "Teacher"), subject(subject_) {}

	void Teach() const {
		cout << Log() << " teaches: " << subject << endl;
	}

private:
	const string subject;
};


class Policeman : public Person {
public:
	Policeman(const string& name) : Person(name, "Policeman") {}

	void Check(const Person& p) const {
		cout << "Policeman: " << name << " checks " << type << ". " << type << "'s name is: " << p.name << endl;
	}
};


void VisitPlaces(const Person& base, const vector<string>& places) {
	for (auto p : places) {
		base.Walk(p);
	}
}

int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, { "Moscow", "London" });
	p.Check(s);
	VisitPlaces(s, { "Moscow", "London" });
	return 0;
}