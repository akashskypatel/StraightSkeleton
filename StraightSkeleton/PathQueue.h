#pragma once
#include "PathQueueNode.h"

class PathQueue
{
public:	
	void AddPush(PathQueueNode* node, PathQueueNode* newNode)
	{
		if (newNode->List == nullptr && node->Previous == nullptr)
		{
			newNode->List = this;
			size++;

			if (node->Next == nullptr)
			{
				newNode->Previous = node;
				newNode->Next = nullptr;

				node->Next = newNode;
			}
			else
			{
				newNode->Previous = nullptr;
				newNode->Next = node;

				node->Previous = newNode;
			}
		}
	}
	void AddFirst(PathQueueNode* node)
	{
		if (node->List == nullptr)
		{
			if (first == nullptr)
			{
				first = node;

				node->List = this;
				node->Next = nullptr;
				node->Previous = nullptr;

				size++;
			}
		}
	}
	/*
	void AddFirst(T data)
	{
		T newData(data);
		PathQueueNode* newNode = new PathQueueNode(newData);
		AddFirst(newNode);
	}
	void AddFirst(T* data)
	{
		T newData(*data);
		PathQueueNode* newNode = new PathQueueNode(newData);
		AddFirst(newNode);
	}
	*/
	PathQueueNode* Pop(PathQueueNode* node)
	{
		if (node->List == this && size > 0 && node->IsEnd())
		{
			node->List = nullptr;

			PathQueueNode* previous = nullptr;

			if (size == 1)
				first = nullptr;
			else
			{
				if (first == node)
				{
					if (node->Next != nullptr)
						first = node->Next;
					else if (node->Previous != nullptr)
						first = node->Previous;
				}
				if (node->Next != nullptr)
				{
					node->Next->Previous = nullptr;
					previous = node->Next;
				}
				else if (node->Previous != nullptr)
				{
					node->Previous->Next = nullptr;
					previous = node->Previous;
				}
			}

			node->Previous = nullptr;
			node->Next = nullptr;

			size--;
			return previous;
		}
		return nullptr;
	}	
	size_t Size()
	{
		return size;
	}
	PathQueueNode* First()
	{
		return first;
	}
private:
	size_t size = 0;
	PathQueueNode* first = nullptr;
};

