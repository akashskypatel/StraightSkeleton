#pragma once
#include "Edge.h"

class FaceNode;
class FaceQueue
{
private:
    using spfn = std::shared_ptr<FaceNode>;
public:
    Edge* GetEdge();
    bool Closed();
    bool IsUnconnected();
    void AddPush(spfn node, spfn newNode);
    void AddFirst(spfn node);
    spfn Pop(spfn node);
    void SetEdge(Edge* val);
    ~FaceQueue();
    void Close();
    size_t Size();
    spfn First();
private:
    Edge* edge = nullptr;
    bool closed = false;
    size_t size = 0;
    spfn first = nullptr;
};

