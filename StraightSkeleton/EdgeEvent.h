#pragma once
#include <string>
#include <format>
#include "SkeletonEvent.h"
#include "Vertex.h"
#include "Vector2d.h"

class EdgeEvent :
    public SkeletonEvent
{
private:
    using spv2d = std::shared_ptr<Vector2d>;
    using spv = std::shared_ptr<Vertex>;
public:
    spv NextVertex;
    spv PreviousVertex;
    bool IsObsolete() override;
    //EdgeEvent(Vector2d point, double distance, Vertex previousVertex, Vertex nextVertex);
    EdgeEvent(spv2d point, double distance, spv previousVertex, spv nextVertex);
    ~EdgeEvent();
    std::string ToString();
};

