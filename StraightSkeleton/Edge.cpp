#include "Edge.h"
#include "CircularList.h"

unsigned int Edge::_idCounter = 0;

Edge::Edge()
{
	_id = ++_idCounter;
	Begin = nullptr;
	End = nullptr;
	lineLinear2d = nullptr;
	Norm = nullptr;
}

Edge::Edge(Vector2d begin,Vector2d end, spn nextNode, spn prevNode, CircularList* list) : CircularNode(nextNode, prevNode, list)
{
	_id = ++_idCounter;
	Begin = std::make_shared<Vector2d>(Vector2d(begin)); 					 
	End = std::make_shared<Vector2d>(Vector2d(end)); 						 
	lineLinear2d = std::make_shared<LineLinear2d>(LineLinear2d(begin, end)); 
	Norm = std::make_shared<Vector2d>(Vector2d((end - begin).Normalized())); 
}

Edge::Edge(spv2d begin, spv2d end)
{
	_id = ++_idCounter;
	Begin = begin;
	End = end;
	lineLinear2d = std::make_shared<LineLinear2d>(LineLinear2d(*begin, *end));
	Norm = std::make_shared<Vector2d>(Vector2d((*end - *begin).Normalized()));
}

std::string Edge::ToString() const
{
	return std::format("Edge [p1={0}, p2={1}]", Begin->ToString(), End->ToString());
}

Edge& Edge::operator=(const Edge& other)
{
	if (this != &other)
	{
		Begin = other.Begin;
		End = other.End;
		lineLinear2d = other.lineLinear2d;
		Norm = other.Norm;
	}
	return *this;
};

unsigned int Edge::GetInstanceId() const
{
	return _id;
}

size_t Edge::HashFunction::operator()(const Edge& val) const
{
	return val.GetInstanceId();
}

size_t Edge::HashFunction::operator()(const std::shared_ptr<Edge> val) const
{
	return val->GetInstanceId();
}