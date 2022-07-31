#include "SplitEvent.h"

SplitEvent::SplitEvent(spv2d point, double distance, spv parent, spe oppositeEdge)
    : SkeletonEvent(point, distance)
{
    Parent = parent.get();
    OppositeEdge = (oppositeEdge.get() != nullptr ? oppositeEdge.get() : nullptr);
}

SplitEvent::~SplitEvent()
{
    //delete OppositeEdge;
    //delete Parent;
}

bool SplitEvent::IsObsolete()
{
    return Parent->IsProcessed;
}

std::string SplitEvent::ToString()
{
    return std::format("SplitEvent [V={0}, Parent={1}, Distance={2}]", V->ToString(), (Parent != nullptr ? Parent->Point->ToString() : "null"), Distance);
}
