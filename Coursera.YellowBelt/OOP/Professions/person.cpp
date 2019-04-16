//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//class Person {
//public:
//	Person(const string& new_name, const string& new_type) : name(new_name), type(new_type) {}
//
//	string GetName() const {
//		return name;
//	}
//
//	string GetType() const {
//		return type;
//	}
//
//	string GetInfo() const {
//		return type + ": " + name;
//	}
//
//	virtual void Walk(const string& destination) const {
//		cout << GetInfo() << " walks to: " << destination << endl;
//	}
//
//protected:
//	const string type;
//	const string name;
//};
//
//class Student : public Person {
//public:
//
//	Student(const string& name, const string& favouriteSong_) 
//		: Person(name, "Student"), favouriteSong(favouriteSong_) {
//	}
//
//	void Learn() const {
//		cout << GetInfo() << " learns" << endl;
//	}
//
//	void Walk(const string& destination) const {
//		cout << GetInfo() << " walks to: " << destination << endl;
//		SingSong();
//	}
//
//	void SingSong() const {
//		cout << GetInfo() << " sings a song: " << favouriteSong << endl;
//	}
//
//private:
//	const string favouriteSong;
//};
//
//
//class Teacher : public Person {
//public:
//
//	Teacher(const string& name, const string& subject_) : Person(name, "Teacher"), subject(subject_) {}
//
//	void Teach() const {
//		cout << GetInfo() << " teaches: " << subject << endl;
//	}
//
//private:
//	const string subject;
//};
//
//
//class Policeman : public Person {
//public:
//	Policeman(const string& name) : Person(name, "Policeman") {}
//
//	void Check(const Person& p) const {
//		cout << "Policeman: " << name << " checks " << p.GetType() << ". " << p.GetType() << "'s name is: " << p.GetName() << endl;
//	}
//};
//
//
//void VisitPlaces(const Person& base, const vector<string>& places) {
//	for (auto p : places) {
//		base.Walk(p);
//	}
//}
//
//int main() {
//	Teacher t("Jim", "Math");
//	Student s("Ann", "We will rock you");
//	Policeman p("Bob");
//
//	VisitPlaces(t, { "Moscow", "London" });
//	p.Check(s);
//	VisitPlaces(s, { "Moscow", "London" });
//	return 0;
//}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
	Human(const string &name, const string &job) : Name(name), Job(job) {};

	virtual void Walk(const string& destination) {
		cout << Job << ": " << Name << " walks to: " << destination << endl;
	}

public:
	const string Name;
	const string Job;
};

class Student : public Human {
public:

	Student(const string &name, const string &song) : Human(name, "Student"), FavouriteSong(song) {};

	void Learn() {
		cout << Job << ": " << Name << " learns" << endl;
	}


	void SingSong() {
		cout << Job << ": " << Name << " sings a song: " << FavouriteSong << endl;
	}

	void Walk(const string& destination) override {
		Human::Walk(destination);
		SingSong();
	}

public:
	const string FavouriteSong;
};


class Teacher : public Human {
public:

	Teacher(const string& name, const string& subject) : Human(name, "Teacher"), Subject(subject) {};

	void Teach() {
		cout << Job << ": " << Name << " teaches: " << Subject << endl;
	}


public:

	const string Subject;
};


class Policeman : public Human {
public:
	Policeman(string name) : Human(name, "Policeman") {};

	void Check(Human h) {
		cout << "Policeman: " << Name << " checks " << h.Job << ". " << h.Job << "'s name is: " << h.Name << endl;
	}
};


void VisitPlaces(Human& h, const vector<string>& places) {
	for (auto p : places) {
		h.Walk(p);
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