#include "SkeletonEvent.h"
/*
SkeletonEvent::SkeletonEvent(Vector2d point, double distance)
{
    V = new Vector2d(point);
    Distance = distance;
}
*/
SkeletonEvent::SkeletonEvent(spv2d point, double distance)
{
    V = point.get();
    Distance = distance;
}

SkeletonEvent::~SkeletonEvent()
{
    delete V;
}

std::string SkeletonEvent::ToString()
{
    return std::format("IntersectEntry [V={0}, Distance={1}]", V->ToString(), Distance);
}
