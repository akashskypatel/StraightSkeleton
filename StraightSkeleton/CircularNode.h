#pragma once
#include <string>
#include <memory>

class CircularList;
class CircularNode
{
private:
	using spn = std::shared_ptr<CircularNode>;
public:
	friend class CircularList;
	CircularList* List;
	spn Next = nullptr;
	spn Previous = nullptr;
	CircularNode();
	CircularNode(spn nextNode, spn prevNode, CircularList* list);
	virtual ~CircularNode();
	void AddNext(spn node);
	void AddPrevious(spn node);
	void Remove();
	virtual std::string ToString() const;
};

