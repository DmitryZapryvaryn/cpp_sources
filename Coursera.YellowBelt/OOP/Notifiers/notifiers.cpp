#include <string>
#include <iostream>

using namespace std;

void SendSms(const string& number, const string& message);
void SendEmail(const string& email, const string& message);

class INotifier {
public:
	virtual void Notify(const string& message) = 0;
};

class SmsNotifier : public INotifier {
public:
	SmsNotifier(const string& phone_number_) : phone_number(phone_number_) {}

	void Notify(const string& message) override {
		SendSms(phone_number, message);
	}

private:
	const string phone_number;
};

class EmailNotifier : public INotifier {
public:
	EmailNotifier(const string& email_) : email(email_) {}

	void Notify(const string& message) override {
		SendEmail(email, message);
	}

private:
	const string email;
};