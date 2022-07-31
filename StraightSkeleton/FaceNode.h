#pragma once
#include "FaceQueue.h"

class Vertex;
class FaceQueue;
class FaceNode
{	
private:
	using spv = std::shared_ptr<Vertex>;
	using spfn = std::shared_ptr<FaceNode>;
	Vertex* vertex = nullptr;
public:	
	spfn Next = nullptr;
	spfn Previous = nullptr;
	FaceQueue* List = nullptr;
	FaceNode(Vertex* vert);
	~FaceNode();
	Vertex* GetVertex();
	FaceQueue* GetFaceQueue();
	bool IsQueueUnconnected();
	bool IsEnd();
	void AddPush(spfn node);
	spfn Pop();
	spfn FindEnd();
	spfn AddQueue(spfn queue);
	void QueueClose();	
};

