#include "FaceNode.h"
#include "Vertex.h"
#include "FaceQueue.h"

FaceNode::FaceNode(Vertex vert)
{
	vertex = std::make_shared<Vertex>(Vertex(vert));
	Next = nullptr;
	Previous = nullptr;
	List = nullptr;
}

FaceNode::FaceNode(std::shared_ptr<Vertex> vert)
{

}

FaceNode::~FaceNode()
{
	//delete vertex;
}

std::shared_ptr<Vertex> FaceNode::GetVertex()
{
	return vertex;
}

void FaceNode::SetVertex(Vertex val)
{
	//delete vertex;
	vertex = std::make_shared<Vertex>(Vertex(val));
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
void FaceNode::AddPush(spfn node)
{
	List->AddPush(spfn(this), node);
}
std::shared_ptr<FaceNode> FaceNode::Pop()
{
	return List->Pop(spfn(this));
}
std::shared_ptr<FaceNode> FaceNode::FindEnd()
{
	if (IsEnd())
		return spfn(this);

	spfn current(this);
	while (current->Previous != nullptr)
		current = current->Previous;

	return current;
}
std::shared_ptr<FaceNode> FaceNode::AddQueue(spfn queue)
{
	if (List == queue->List)
		return nullptr;

	spfn currentQueue(this);

	spfn current(queue);

	while (current != nullptr)
	{
		spfn next(current->Pop());
		currentQueue->AddPush(current);
		currentQueue = current;

		current = next;
	}

	return currentQueue;
}

void FaceNode::QueueClose()
{
	List->Close();
}
