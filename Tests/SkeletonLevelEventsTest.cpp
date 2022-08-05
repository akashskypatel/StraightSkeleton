#pragma once
#include <iostream>
#include <string>
#include "pch.h"
#include "CppUnitTest.h"
#include "../StraightSkeleton/Vector2d.h"
#include "../StraightSkeleton/Vector2d.cpp"
#include "../StraightSkeleton/SkeletonBuilder.h"
#include "../StraightSkeleton/SkeletonBuilder.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SkeletonLevelEventsTest
{
	TEST_CLASS(SkeletonLevelEventsTest)
	{
	public:
        void AssertPolygonWithEdges(int numOfEdges, Skeleton sk)
        {
            for(auto edgeOutput : *sk.Edges)
            {
                auto points = edgeOutput->Polygon;
                if (points->size() == numOfEdges)
                    return;
            }
            std::string str = std::string("Expected polygon with number of edges: ") + std::to_string(numOfEdges);
            auto mes = std::wstring(str.begin(), str.end());
            Assert::Fail(mes.c_str());
        }
        /*
		TEST_METHOD(Skeleton_multiEdgeEvent)
		{

		}
        */
	};
}