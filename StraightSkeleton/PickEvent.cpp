#include "PickEvent.h"

PickEvent::PickEvent(spv2d point, double distance, spec chain) : SkeletonEvent(point, distance)
{
    Chain = chain;
}

bool PickEvent::IsObsolete()
{
    return false;
}
