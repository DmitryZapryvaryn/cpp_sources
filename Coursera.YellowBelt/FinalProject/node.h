#pragma once

#include "date.h"

#include <memory>

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

enum class LogicalOperation {
	Or,
	And,
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
	DateComparisonNode(const Comparison cmp, const Date& date) : comparison(cmp), date_(date) {};

	bool Evaluate(const Date& date, const string& event) const override;

private:
	const Comparison comparison;
	const Date date_;
};

class EventComparisonNode : public Node {
public:
	EventComparisonNode(Comparison cmp, const string& event) : comparison(cmp), event_(event) {}

	bool Evaluate(const Date& date, const string& event) const override;

private:
	const Comparison comparison;
	const string event_;
};

class LogicalOperationNode : public Node {
public:
	LogicalOperationNode(const LogicalOperation logOp, shared_ptr<const Node> left, shared_ptr<const Node> right) : logicalOperation(logOp), left_(left), right_(right) {}

	bool Evaluate(const Date& date, const string& event) const override;

private:
	const LogicalOperation logicalOperation;
	shared_ptr<const Node> left_, right_;
};
