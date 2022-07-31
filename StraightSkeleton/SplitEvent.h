#pragma once
#include <string>
#include <format>
#include "SkeletonEvent.h"
#include "Edge.h"
#include "Vertex.h"

class SplitEvent :
    public SkeletonEvent
{
private:
    using spe = std::shared_ptr<Edge>;
    using spv = std::shared_ptr<Vertex>;
public:
    spe OppositeEdge;
    spv Parent;
    SplitEvent(Vector2d point, double distance, spv parent, spe oppositeEdge);
    ~SplitEvent();
    bool IsObsolete() override;
    std::string ToString();
};


