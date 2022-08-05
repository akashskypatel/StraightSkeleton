#pragma once
#include <memory>

class Vertex;
class FaceQueue;
class FaceNode
{	
private:
	using spv = std::shared_ptr<Vertex>;
	using spfn = std::shared_ptr<FaceNode>;
	spv vertex = nullptr;
public:
	friend class FaceQueue;
	spfn Next = nullptr;
	spfn Previous = nullptr;
	FaceQueue* List = nullptr;
	//FaceNode(Vertex* vert);
	FaceNode(spv vert);
	~FaceNode();
	std::shared_ptr<Vertex> GetVertex();
	FaceQueue* GetFaceQueue();
	bool IsQueueUnconnected();
	bool IsEnd();
	void AddPush(spfn node);
	spfn Pop();
	spfn FindEnd();
	spfn AddQueue(spfn queue);
	void QueueClose();
};

