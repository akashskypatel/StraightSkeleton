#include "PickEvent.h"

PickEvent::PickEvent(Vector2d point, double distance, EdgeChain* chain) : SkeletonEvent(point, distance)
{
    Chain = chain;
}

bool PickEvent::IsObsolete()
{
    return false;
}
