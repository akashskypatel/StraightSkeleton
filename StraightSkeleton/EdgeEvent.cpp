#include "EdgeEvent.h"

bool EdgeEvent::IsObsolete()
{
    return (PreviousVertex->IsProcessed || NextVertex->IsProcessed);
}

EdgeEvent::EdgeEvent(spv2d point, double distance, spv previousVertex, spv nextVertex) : SkeletonEvent(point, distance)
{
    PreviousVertex = previousVertex;
    NextVertex = nextVertex;
}

EdgeEvent::~EdgeEvent()
{
    NextVertex = nullptr;
    PreviousVertex = nullptr;
}

std::string EdgeEvent::ToString()
{
    std::string str1 = V->ToString();
    std::string str2 = (PreviousVertex != nullptr ? PreviousVertex->Point->ToString() : "null");
    std::string str3 = (NextVertex != nullptr ? NextVertex->Point->ToString() : "null");
    return std::format("EdgeEvent [V={0}, PreviousVertex={1}, NextVertex={2}, Distance={3}]", str1, str2, str3, SkeletonEvent::Distance);
}
