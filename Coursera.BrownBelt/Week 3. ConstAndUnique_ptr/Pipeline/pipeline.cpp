#include "test_runner.h"

#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
	string from;
	string to;
	string body;

	Email(string from_,
		string to_,
		string body_) : from(from_), to(to_), body(body_) {}
};


class Worker {
public:
	virtual ~Worker() = default;
	virtual void Process(unique_ptr<Email> email) = 0;
	virtual void Run() {
		// только первому worker-у в пайплайне нужно это имплементировать
		throw logic_error("Unimplemented");
	}

protected:
	// реализации должны вызывать PassOn, чтобы передать объект дальше
	// по цепочке обработчиков
	void PassOn(unique_ptr<Email> email) const {
		if (next_) {
			next_->Process(move(email));
		}
	}

public:
	void SetNext(unique_ptr<Worker> next) {
		next_ = move(next);
	}
private:
	unique_ptr<Worker> next_ = nullptr;
};


class Reader : public Worker {
public:
	Reader(istream& in) : input(in) {}

	virtual void Run() override {

		for (string line; getline(input, line); ) {
			if (line.empty()) continue;

			string from = line;
			string to; getline(input, to);
			string body; getline(input, body);

			PassOn(make_unique<Email>(from, to, body));
		}
	}

	void Process(unique_ptr<Email> email) override {
		PassOn(move(email));
	}
private:
	istream& input;
};


class Filter : public Worker {
public:
	using Function = function<bool(const Email&)>;

public:
	Filter(Function function) : function_(function) {}

	void Process(unique_ptr<Email> email) override {
		if (function_(*email)) {
			PassOn(move(email));
		}
	}

private:
	Function function_;
};


class Copier : public Worker {
public:
	Copier(const string& recipient) : recipient_(recipient) {}

	void Process(unique_ptr<Email> email) override {
		string body = email->body;
		string from = email->from;
		string to = email->to;

		PassOn(move(email));

		if (to != recipient_) {
			PassOn(make_unique<Email>(from, recipient_, body));
		}
		
	}

private:
	string recipient_;
};


class Sender : public Worker {
public:
	Sender(ostream& out) : output(out) {}

	void Process(unique_ptr<Email> email) override {
		output << email->from << "\n"
			<< email->to << "\n"
			<< email->body << "\n";
		PassOn(move(email));
	}

private:
	ostream& output;
};


// реализуйте класс
class PipelineBuilder {
public:
	// добавляет в качестве первого обработчика Reader
	explicit PipelineBuilder(istream& in) {
		reader_ =  make_unique<Reader>(in);
	}

	// добавляет новый обработчик Filter
	PipelineBuilder& FilterBy(Filter::Function filter) {
		filter_ = make_unique<Filter>(filter);
		return *this;
	}

	// добавляет новый обработчик Copier
	PipelineBuilder& CopyTo(string recipient) {
		copier_ = make_unique<Copier>(recipient);
		return *this;
	}

	// добавляет новый обработчик Sender
	PipelineBuilder& Send(ostream& out) {
		sender_ = make_unique<Sender>(out);
		return *this;
	}

	// возвращает готовую цепочку обработчиков
	unique_ptr<Worker> Build() {
		copier_->SetNext(move(sender_));
		filter_->SetNext(move(copier_));
		reader_->SetNext(move(filter_));

		return move(reader_);
	}

private:
	unique_ptr<Worker> reader_;
	unique_ptr<Worker> filter_;
	unique_ptr<Worker> copier_;
	unique_ptr<Worker> sender_;
};


void TestSanity() {
	string input = (
		"erich@example.com\n"
		"richard@example.com\n"
		"Hello there\n"

		"erich@example.com\n"
		"ralph@example.com\n"
		"Are you sure you pressed the right button?\n"

		"ralph@example.com\n"
		"erich@example.com\n"
		"I do not make mistakes of that kind\n"
		);
	istringstream inStream(input);
	ostringstream outStream;

	PipelineBuilder builder(inStream);
	builder.FilterBy([](const Email& email) {
		return email.from == "erich@example.com";
		});
	builder.CopyTo("richard@example.com");
	builder.Send(outStream);
	auto pipeline = builder.Build();

	pipeline->Run();

	string expectedOutput = (
		"erich@example.com\n"
		"richard@example.com\n"
		"Hello there\n"

		"erich@example.com\n"
		"ralph@example.com\n"
		"Are you sure you pressed the right button?\n"

		"erich@example.com\n"
		"richard@example.com\n"
		"Are you sure you pressed the right button?\n"
		);

	ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSanity);
	return 0;
}
