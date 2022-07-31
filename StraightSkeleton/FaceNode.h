#pragma once
#include "FaceQueue.h"

class Vertex;
class FaceQueue;
class FaceNode
{	
private:
	using spv = std::shared_ptr<Vertex>;
	using spfn = std::shared_ptr<FaceNode>;
	spv vertex = nullptr;
public:	
	spfn Next = nullptr;
	spfn Previous = nullptr;
	FaceQueue* List = nullptr;
	FaceNode(Vertex vert);
	FaceNode(std::shared_ptr<Vertex> vert);
	~FaceNode();
	std::shared_ptr<Vertex> GetVertex();
	void SetVertex(Vertex val);
	FaceQueue* GetFaceQueue();
	bool IsQueueUnconnected();
	bool IsEnd();
	void AddPush(spfn node);
	spfn Pop();
	spfn FindEnd();
	spfn AddQueue(spfn queue);
	void QueueClose();	
};

