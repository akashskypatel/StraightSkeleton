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

void CircularNode::AddNext(spn node, spn newNode)
{
	List->AddNext(node, newNode);
}

void CircularNode::AddPrevious(spn node, spn newNode)
{
	List->AddPrevious(node, newNode);
}

void CircularNode::Remove(spn node)
{
	List->Remove(node);
}

std::string CircularNode::ToString() const
{
	return "circular node virtual parent ToString() called";
}
