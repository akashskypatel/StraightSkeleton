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

}

void CircularNode::AddNext(spn node)
{
	List->AddNext(spn(this), node);
}

void CircularNode::AddPrevious(spn node)
{
	List->AddPrevious(spn(this), node);
}

void CircularNode::Remove()
{
	List->Remove(this);
}

std::string CircularNode::ToString() const
{
	return "circular node virtual parent ToString() called";
}
