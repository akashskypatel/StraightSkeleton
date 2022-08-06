#include "FaceNode.h"
#include "Vertex.h"
#include "FaceQueue.h"

/*
FaceNode::FaceNode(Vertex* vert)
{
	vertex = vert;
}
*/

FaceNode::FaceNode(spv vert)
{
	vertex = vert;
}

FaceNode::~FaceNode()
{
	//delete vertex;
}

std::shared_ptr<Vertex> FaceNode::GetVertex()
{
	return vertex;
}

FaceQueue* FaceNode::GetFaceQueue()
{
	return this->List;
}

bool FaceNode::IsQueueUnconnected()
{
	return false;
}
bool FaceNode::IsEnd()
{
	return Next == nullptr || Previous == nullptr;
}
void FaceNode::AddPush(spfn node, spfn newNode)
{
	List->AddPush(node, newNode);
}
std::shared_ptr<FaceNode> FaceNode::Pop(spfn node)
{
	return List->Pop(node);
}
//not used
std::shared_ptr<FaceNode> FaceNode::FindEnd() 
{
	if (IsEnd())
		return spfn(this); //not gonna work

	spfn current(this); //not gonna work
	while (current->Previous != nullptr)
		current = current->Previous;

	return current;
}
std::shared_ptr<FaceNode> FaceNode::AddQueue(spfn thisQueue, spfn queue)
{
	if (List == queue->List)
		return nullptr;

	//spfn currentQueue(this); //not gonna work

	spfn current(queue);

	while (current != nullptr)
	{
		spfn next(current->Pop(current));
		thisQueue->AddPush(thisQueue, current);
		thisQueue = current;

		current = next;
	}

	return thisQueue;
}

void FaceNode::QueueClose()
{
	List->Close();
}
