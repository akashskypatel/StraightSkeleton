#pragma once
#include "Edge.h"
#include "FaceNode.h"

class FaceQueue
{
private:	
    using spfn = std::shared_ptr<FaceNode>;	
	std::shared_ptr<Edge> edge = nullptr;
	bool closed = false;
	size_t size = 0;
	std::shared_ptr<FaceNode> first = nullptr;
public:
	struct Iterator
	{
		std::shared_ptr<FaceNode> first;
		size_t s;
		size_t i;
		std::shared_ptr<FaceNode> operator*()
		{
			return first;
		}
		bool operator != (const Iterator& rhs)
		{
			s = rhs.s;
			return first != rhs.first;
		}
		bool operator == (const Iterator& rhs)
		{
			return first == rhs.first;
		}
		Iterator& operator++()
		{
			i++;
			if (i < s)
				first = first->Next;
			else
				first = nullptr;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator iterator = *this;
			++* this;
			return iterator;
		}
		Iterator& operator = (std::shared_ptr<FaceNode> rhs)
		{
			this->first = rhs;
			return *this;
		}
	};
	Iterator begin()
	{ 
		if(first->IsEnd())
			return Iterator{ first, size };

		auto current = first;
		while(current->Previous != nullptr)
			current = current->Previous;
			
		return Iterator{ current, size };
	}
	Iterator end() 
	{ 
		return Iterator{ nullptr, size }; 
	}
	Iterator cbegin() 
	{ 
		if (first->IsEnd())
			return Iterator{ first, size };

		auto current = first;
		while (current->Previous != nullptr)
			current = current->Previous;

		return Iterator{ current, size };
	}
	Iterator cend() 
	{ 
		return Iterator{ nullptr, size }; 
	}
    std::shared_ptr<Edge> GetEdge();
	FaceQueue();
    bool Closed();
    bool IsUnconnected();
    void AddPush(std::shared_ptr<FaceNode> node, std::shared_ptr<FaceNode> newNode);
    void AddFirst(std::shared_ptr<FaceNode> node);
	std::shared_ptr<FaceNode> Pop(std::shared_ptr<FaceNode> node);
    void SetEdge(std::shared_ptr<Edge> val);
    ~FaceQueue();
    void Close();
    size_t Size();
	std::shared_ptr<FaceNode> First();
};

