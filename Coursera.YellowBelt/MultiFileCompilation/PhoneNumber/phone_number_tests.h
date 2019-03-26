#pragma once
#include "test_runner.h"
#include "phone_number.h"

void TestInvalidNumber() {
	int count_failed = 0;
	try {
		PhoneNumber pn1("");
	}
	catch (invalid_argument& e) {
		AssertEqual(string(e.what()), "Invalid number format");
		++count_failed;
	}
	try {
		PhoneNumber pn2("+7");
	}
	catch (invalid_argument& e) {
		AssertEqual(string(e.what()), "Invalid number format");
		++count_failed;
	}
	try {
		PhoneNumber pn3("+7-123");
	}
	catch (invalid_argument& e) {
		AssertEqual(string(e.what()), "Invalid number format");
		++count_failed;
	}
	try {
		PhoneNumber pn4("-7");
	}
	catch (invalid_argument& e) {
		AssertEqual(string(e.what()), "Invalid number format");
		++count_failed;
	}
	AssertEqual(count_failed, 4);
}

void TestValidNumber() {
	PhoneNumber pn("+7-123-4567-312-321");
	AssertEqual(pn.GetCountryCode(), "7");
	AssertEqual(pn.GetCityCode(), "123");
	AssertEqual(pn.GetLocalNumber(), "4567-312-321");
	AssertEqual(pn.GetInternationalNumber(), "+7-123-4567-312-321");
	
}

void RunAll() {
	TestRunner tr;
	tr.RunTest(TestInvalidNumber, "TestInvalidNumber");
	tr.RunTest(TestValidNumber, "TestValidNumber");
}