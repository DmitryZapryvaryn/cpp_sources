#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
	Person(const string& new_name, const string& new_type) : name(new_name), type(new_type) {}

	string GetName() const {
		return name;
	}

	string GetType() const {
		return type;
	}

	ostream& PrintInfo() const {
		return cout << type << ": " << name;
	}

	virtual void Walk(const string& destination) const {
		PrintInfo() << " walks to: " << destination << endl;
	}

protected:
	const string type;
	const string name;
};

class Student : public Person {
public:

	Student(const string& name, const string& favouriteSong_) 
		: Person(name, "Student"), favouriteSong(favouriteSong_) {
	}

	void Learn() const {
		PrintInfo() << " learns" << endl;
	}

	void Walk(const string& destination) const override {
		Person::Walk(destination);
		SingSong();
	}

	void SingSong() const {
		PrintInfo() << " sings a song: " << favouriteSong << endl;
	}

private:
	const string favouriteSong;
};


class Teacher : public Person {
public:

	Teacher(const string& name, const string& subject_) : Person(name, "Teacher"), subject(subject_) {}

	void Teach() const {
		PrintInfo() << " teaches: " << subject << endl;
	}

private:
	const string subject;
};


class Policeman : public Person {
public:
	Policeman(const string& name) : Person(name, "Policeman") {}

	void Check(const Person& p) const {
		PrintInfo() << " checks " << p.GetType() << ". " << p.GetType() << "'s name is: " << p.GetName() << endl;
	}
};


void VisitPlaces(const Person& person, const vector<string>& places) {
	for (const auto& place : places) {
		person.Walk(place);
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