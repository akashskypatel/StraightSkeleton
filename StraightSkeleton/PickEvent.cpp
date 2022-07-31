#include "PickEvent.h"

PickEvent::PickEvent(spv2d point, double distance, spec chain) : SkeletonEvent(point, distance)
{
    Chain = chain.get();
}

bool PickEvent::IsObsolete()
{
    return false;
}
