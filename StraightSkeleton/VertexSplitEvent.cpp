#include "VertexSplitEvent.h"

VertexSplitEvent::VertexSplitEvent(spv2d point, double distance, spv parent) :
    SplitEvent(point, distance, parent, nullptr)
{
}

std::string VertexSplitEvent::ToString()
{
    return std::format("VertexSplitEvent [V={0}, Parent={1}, Distance={2}]", V->ToString(), (Parent != nullptr ? Parent->Point->ToString() : "null"), Distance);
}
