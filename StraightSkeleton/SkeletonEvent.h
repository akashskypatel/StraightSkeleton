#pragma once
#include <string>
#include <format>
#include "Vector2d.h"

class SkeletonEvent
{
private:
    using spv2d = std::shared_ptr<Vector2d>;
public:
    Vector2d* V = nullptr;
    double Distance;    

    //SkeletonEvent(Vector2d point, double distance);
    SkeletonEvent(spv2d point, double distance);
    ~SkeletonEvent();
    std::string ToString();
    virtual bool IsObsolete() { return false; };
};

