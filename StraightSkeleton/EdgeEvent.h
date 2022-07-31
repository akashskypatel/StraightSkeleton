#pragma once
#include <string>
#include <format>
#include "SkeletonEvent.h"
#include "Vertex.h"
#include "Vector2d.h"

class EdgeEvent :
    public SkeletonEvent
{
public:
    Vertex* NextVertex;
    Vertex* PreviousVertex;
    bool IsObsolete() override;
    EdgeEvent(Vector2d point, double distance, Vertex previousVertex, Vertex nextVertex);
    ~EdgeEvent();
    std::string ToString();
};

