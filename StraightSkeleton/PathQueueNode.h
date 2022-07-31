#pragma once

class PathQueue;
class PathQueueNode
{
public:
	PathQueueNode* Next;
	PathQueueNode* Previous;
	PathQueue* List;
	
	bool IsEnd();
	void AddPush(PathQueueNode* node);	
	PathQueueNode* Pop();
	PathQueueNode* FindEnd();
	PathQueueNode* AddQueue(PathQueueNode* queue);
};