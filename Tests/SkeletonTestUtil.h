#pragma once
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "../StraightSkeleton/Vector2d.h"
#include "../StraightSkeleton/Vector2d.cpp"
#include "../StraightSkeleton/Skeleton.h"
#include "../StraightSkeleton/Skeleton.cpp"
#include "../StraightSkeleton/EdgeResult.h"
#include "../StraightSkeleton/EdgeResult.cpp"

class SkeletonTestUtil
{
    static std::vector<Vector2d> GetFacePoints(Skeleton sk)
    {
        std::vector<Vector2d> ret = std::vector<Vector2d>();

        for(auto edgeOutput : *sk.Edges)
        {
            auto points = edgeOutput->Polygon;
            for(auto vector2d : *points)
            {
                if (!ContainsEpsilon(ret, *vector2d))
                    ret.push_back(*vector2d);
            }
        }
        return ret;
    }

    static bool AssertExpectedPoints(std::vector<Vector2d> expectedList, std::vector<Vector2d> givenList)
    {
        std::stringstream sb;
        for(const Vector2d& expected : expectedList)
        {
            if (!ContainsEpsilon(givenList, expected))
                sb << "Can't find expected point ({0}, {1}) in given list\n" << expected.X << expected.Y;
        }

        for(const Vector2d& given : givenList)
        {
            if (!ContainsEpsilon(expectedList, given))
                sb << "Can't find given point ({0}, {1}) in expected list\n" << given.X << given.Y;
        }

        if (sb.tellp() > 0)
        {
            std::cout << sb.str();
            return false;
        }
        else
        {
            return true;
        }
    }

    static bool ContainsEpsilon(std::vector<Vector2d> list, Vector2d p)
    {
        return std::any_of(list.begin(), list.end(), [](Vector2d l) { return EqualEpsilon(l.X, l.Y) && EqualEpsilon(l.X, l.Y); });            
            //list.Any(l = > EqualEpsilon(l.X, p.X) && EqualEpsilon(l.Y, p.Y));
    }

    static bool EqualEpsilon(double d1, double d2)
    {
        return fabs(d1 - d2) < 5E-6;
    }
};

