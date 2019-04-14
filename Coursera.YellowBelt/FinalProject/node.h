#pragma once

#include "date.h"

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) = 0;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event) override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(Comparison cmp, const Date& date);

	bool Evaluate(const Date& date, const string& event) override;

private:
	Comparison comparison;
	Date date;
};