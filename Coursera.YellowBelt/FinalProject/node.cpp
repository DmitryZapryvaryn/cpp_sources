#include "node.h"

template<typename T>
bool CompareTo(const T& lhs, const T& rhs, const Comparison cmp)
{
	switch (cmp)
	{
	case Comparison::Less:
		return lhs < rhs;
		break;
	case Comparison::LessOrEqual:
		return lhs <= rhs;
		break;
	case Comparison::Greater:
		return lhs > rhs;
		break;
	case Comparison::GreaterOrEqual:
		return lhs >= rhs;
		break;
	case Comparison::Equal:
		return lhs == rhs;
		break;
	case Comparison::NotEqual:
		return lhs != rhs;
		break;
	default:
		return false;
		break;
	}
}

bool EmptyNode::Evaluate(const Date & date, const string & event) const
{
	return true;
}

bool DateComparisonNode::Evaluate(const Date & date, const string & event) const
{
	return CompareTo(date, date_, comparison);
}

bool EventComparisonNode::Evaluate(const Date & date, const string & event) const
{
	return CompareTo(event, event_, comparison);
}

bool LogicalOperationNode::Evaluate(const Date & date, const string & event) const
{
	switch (logicalOperation)
	{
	case LogicalOperation::And:
		return left_->Evaluate(date, event) && right_->Evaluate(date, event);
		break;
	case LogicalOperation::Or:
		return left_->Evaluate(date, event) || right_->Evaluate(date, event);
		break;
	default:
		return false;
		break;
	}
}
