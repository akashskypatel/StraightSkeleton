#pragma once
#include <string>
#include <format>
#include "SplitEvent.h"

class VertexSplitEvent :
    public SplitEvent
{
private:
    using spv = std::shared_ptr<Vertex>;
public:
    VertexSplitEvent(Vector2d point, double distance, spv parent);
    std::string ToString();
};

