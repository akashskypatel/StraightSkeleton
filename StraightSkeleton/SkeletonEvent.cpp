#include "SkeletonEvent.h"

SkeletonEvent::SkeletonEvent(spv2d point, double distance)
{
    V = point;
    Distance = distance;
}

SkeletonEvent::~SkeletonEvent()
{

}

std::string SkeletonEvent::ToString()
{
    return std::format("IntersectEntry [V={0}, Distance={1}]", V->ToString(), Distance);
}
