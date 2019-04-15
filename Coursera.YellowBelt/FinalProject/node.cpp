#include "node.h"

bool EmptyNode::Evaluate(const Date & date, const string & event) const
{
	return true;
}

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

bool EventComparisonNode::Evaluate(const Date & date, const string & event) const
{
	switch (comparison)
	{
	case Comparison::Equal:
		return event_ == event;
		break;
	case Comparison::NotEqual:
		return event_ != event;
		break;
	default:
		return false;
		break;
	}
}

bool LogicalOperationNode::Evaluate(const Date & date, const string & event) const
{
	return false;
}
