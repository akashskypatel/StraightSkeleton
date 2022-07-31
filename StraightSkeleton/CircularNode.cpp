#include "CircularNode.h"
#include "CircularList.h"

CircularNode::CircularNode()
{
	Next = nullptr;
	Previous = nullptr;
	List = nullptr;
}

CircularNode::CircularNode(spn nextNode, spn prevNode, CircularList* list)
{
	Next = nextNode;
	Previous = prevNode;
	List = list;
}

CircularNode::~CircularNode()
{
	std::cout << "parent destructor\n";
}

void CircularNode::AddNext(spn node)
{
	List->AddNext(std::make_shared<CircularNode>(*this), node);
}

void CircularNode::AddPrevious(spn node)
{
	List->AddPrevious(std::make_shared<CircularNode>(*this), node);
}

void CircularNode::Remove()
{
	List->Remove(std::make_shared<CircularNode>(*this));
}

std::string CircularNode::ToString() const
{
	return "virtual parent ToString() called";
}
