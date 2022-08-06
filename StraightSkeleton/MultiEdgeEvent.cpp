#ifndef _MULTIEDGEEVENT_H_
#define _MULTIEDGEEVENT_H_

#include "MultiEdgeEvent.h"

MultiEdgeEvent::MultiEdgeEvent(spv2d point, double distance, spec chain) : SkeletonEvent(point, distance)
{
    Chain = chain;
}

bool MultiEdgeEvent::IsObsolete()
{
    return false;
}

#endif // !_MULTIEDGEEVENT_H_
