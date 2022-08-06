#ifndef _PICKEVENT_H_
#define _PICKEVENT_H_

#include "PickEvent.h"

PickEvent::PickEvent(spv2d point, double distance, spec chain) : SkeletonEvent(point, distance)
{
    Chain = chain;
}

bool PickEvent::IsObsolete()
{
    return false;
}

#endif // !_PICKEVENT_H_
