#include "PathQueueNode.h"
#include "PathQueue.h"

bool PathQueueNode::IsEnd()
{
	return Next == nullptr || Previous == nullptr;
}
void PathQueueNode::AddPush(PathQueueNode* node)
{
	List->AddPush(this, node);
}
PathQueueNode* PathQueueNode::Pop()
{
	return List->Pop(this);
}
PathQueueNode* PathQueueNode::FindEnd()
{
	if (IsEnd())
		return this;

	PathQueueNode* current = this;
	while (current->Previous != nullptr)
		current = current->Previous;

	return current;
}
PathQueueNode* PathQueueNode::AddQueue(PathQueueNode* queue)
{
	if (List == queue->List)
		return nullptr;

	PathQueueNode* currentQueue = this;

	PathQueueNode* current = queue;

	while (current != nullptr)
	{
		PathQueueNode* next = current->Pop();
		currentQueue->AddPush(current);
		currentQueue = current;

		current = next;
	}

	return currentQueue;
}