#include "node.h"

bool EmptyNode::Evaluate(const Date & date, const string & event) const
{
	return true;
}

DateComparisonNode::DateComparisonNode(Comparison cmp, const Date & date) : comparison(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date & date, const string & event) const
{
	switch (comparison)
	{
	case Comparison::Less:
		return date < date_;
		break;
	case Comparison::LessOrEqual:
		return date <= date_;
		break;
	case Comparison::Greater:
		return date > date_;
		break;
	case Comparison::GreaterOrEqual:
		return date >= date_;
		break;
	case Comparison::Equal:
		return date == date_;
		break;
	case Comparison::NotEqual:
		return date != date_;
		break;
	default:
		return false;
		break;
	}
}

EventComparisonNode::EventComparisonNode(Comparison cmp, const string& event) : comparison(cmp), event_(event) {}

bool EventComparisonNode::Evaluate(const Date & date, const string & event) const
{
	return false;
}
