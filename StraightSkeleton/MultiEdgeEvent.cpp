#include "MultiEdgeEvent.h"

MultiEdgeEvent::MultiEdgeEvent(Vector2d point, double distance, EdgeChain* chain) : SkeletonEvent(point, distance)
{
    Chain = chain;
}

bool MultiEdgeEvent::IsObsolete()
{
    return false;
}
