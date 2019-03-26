#pragma once
#include "test_runner.h"
#include "sum_reverse_sort.h"

void TestSum() {
	AssertEqual(Sum(1, 2), 3, "1");
	AssertEqual(Sum(-1, 2), 1, "2");
	AssertEqual(Sum(-1, -2), -3, "3");
	AssertEqual(Sum(0, 2), 2, "4");
	AssertEqual(Sum(1, 0), 1, "5");
}

void TestReverse() {
	AssertEqual(Reverse(""), "", "6");
	AssertEqual(Reverse(" "), " ", "7");
	AssertEqual(Reverse("a"), "a", "8");
	AssertEqual(Reverse("ab"), "ba", "9");
	AssertEqual(Reverse("abc"), "cba", "10");
}

void TestSort() {
	vector<int> toSort = { 3, 4, 2, 1 };
	Sort(toSort);
	vector<int> expectedVector = { 1, 2, 3, 4 };
	Assert(toSort == expectedVector, "11");
}

void RunAll() {
	TestRunner tr;
	tr.RunTest(TestSum, "TestSum");
	tr.RunTest(TestReverse, "TestReverse");
	tr.RunTest(TestSort, "TestSort");
}