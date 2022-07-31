#include "Edge.h"
#include "CircularList.h"

Edge::Edge()
{
	std::cout << "default ctor " << this << "\n";
	Begin = nullptr;
	End = nullptr;
	lineLinear2d = nullptr;
	Norm = nullptr;
}

Edge::Edge(const Edge& other, spn nextNode, spn prevNode, CircularList* list) : CircularNode(nextNode, prevNode, list)
{
	std::cout << "edge ref ctor " << this << "\n";
	Begin = std::make_shared<Vector2d>(Vector2d(other.Begin->X, other.Begin->Y)); 	// new Vector2d(other.Begin->X, other.Begin->Y);
	End = std::make_shared<Vector2d>(Vector2d(other.End->X, other.End->Y)); 		// new Vector2d(other.End->X, other.End->Y);
	lineLinear2d = std::make_shared<LineLinear2d>(LineLinear2d(*Begin, *End)); 		// new LineLinear2d(*Begin, *End);
	Norm = std::make_shared<Vector2d>(Vector2d(other.Norm->X, other.Norm->Y)); 		// new Vector2d(other.Norm->X, other.Norm->Y);
}

Edge::Edge(Vector2d begin,Vector2d end, spn nextNode, spn prevNode, CircularList* list) : CircularNode(nextNode, prevNode, list)
{
	std::cout << "vector2d ctor " << this << "\n";
	Begin = std::make_shared<Vector2d>(Vector2d(begin)); 					 // new Vector2d(begin);
	End = std::make_shared<Vector2d>(Vector2d(end)); 						 // new Vector2d(end);
	lineLinear2d = std::make_shared<LineLinear2d>(LineLinear2d(begin, end)); // new LineLinear2d(begin, end);
	Norm = std::make_shared<Vector2d>(Vector2d((end - begin).Normalized())); // new Vector2d((end - begin).Normalized());
}

Edge::Edge(spv2d begin, spv2d end)
{
	Begin = begin;
	End = end;
	lineLinear2d = std::make_shared<LineLinear2d>(LineLinear2d(*begin.get(), *end.get()));
	Norm = std::make_shared<Vector2d>(Vector2d((*end.get() - *begin.get()).Normalized()));
}

Edge::~Edge()
{
	std::cout << "child destructor " << this << "\n";
	//delete Begin;
	//delete End;
	//delete lineLinear2d;
	//delete Norm;
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

