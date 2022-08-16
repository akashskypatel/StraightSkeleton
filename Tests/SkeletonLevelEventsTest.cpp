#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <memory>
#include <algorithm>
#include <limits>
#include <map>
#include "pch.h"
#include "CppUnitTest.h"
#include "../StraightSkeleton/SkeletonBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SkeletonLevelEventsTest
{
	TEST_CLASS(SkeletonLevelEventsTest)
	{
	private:
        static std::vector<Vector2d> GetFacePoints(Skeleton sk)
        {
            std::vector<Vector2d> ret = std::vector<Vector2d>();

            for (auto edgeOutput : *sk.Edges)
            {
                auto points = edgeOutput->Polygon;
                for (auto vector2d : *points)
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
            for (const Vector2d& expected : expectedList)
            {
                if (!ContainsEpsilon(givenList, expected))
                    sb << "Can't find expected point ({0}, {1}) in given list\n" << expected.X << expected.Y;
            }

            for (const Vector2d& given : givenList)
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

        static bool ContainsEpsilon(std::vector<Vector2d> list, const Vector2d& p)
        {
            return std::any_of(list.begin(), list.end(), [&p](Vector2d l) { return EqualEpsilon(l.X, p.X) && EqualEpsilon(l.Y, p.Y); });
        }

        static bool EqualEpsilon(double d1, double d2)
        {
            return fabs(d1 - d2) < 5E-6;
        }
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
        
		TEST_METHOD(Skeleton_multiEdgeEvent)
		{
            std::vector<Vector2d> polygon = 
            {
                Vector2d(0, 1),
                Vector2d(-1, 0),
                Vector2d(0, -1),
                Vector2d(5, -2),
                Vector2d(7, 0),
                Vector2d(5, 2)
            };

            std::vector<Vector2d> expected = 
            {
                Vector2d(0.53518, 0),
                Vector2d(4.39444872, 0)
            };

            expected.insert(expected.end(), polygon.begin(), polygon.end());

            auto sk = SkeletonBuilder::Build(polygon);

            Assert::IsTrue(AssertExpectedPoints(expected, GetFacePoints(sk)));
		}
        TEST_METHOD(Skeleton_pickEvent)
        {
            std::vector<Vector2d> polygon = 
            {
                Vector2d(-1, -1),
                Vector2d(1, -1),
                Vector2d(1, 1),
                Vector2d(-1, 1)
            };
            std::vector<Vector2d> expected = 
            {
                Vector2d(0, 0)
            };

            expected.insert(expected.end(), polygon.begin(), polygon.end());

            auto sk = SkeletonBuilder::Build(polygon);

            Assert::IsTrue(AssertExpectedPoints(expected, GetFacePoints(sk)));
        }
        TEST_METHOD(SkeletonTest_cross_T1)
        {
            std::vector<Vector2d> polygon = 
            {
                Vector2d(-3, -1),
                Vector2d(3, -1),
                Vector2d(3, 1),
                Vector2d(1, 1),
                Vector2d(1, 3),
                Vector2d(-1, 3),
                Vector2d(-1, 1),
                Vector2d(-3, 1)
            };

            std::vector<Vector2d> expected = 
            {
                Vector2d(-2, 0),
                Vector2d(2, 0),
                Vector2d(0, 0),
                Vector2d(0, 2)
            };

            expected.insert(expected.end(), polygon.begin(), polygon.end());

            auto sk = SkeletonBuilder::Build(polygon);

            Assert::IsTrue(AssertExpectedPoints(expected, GetFacePoints(sk)));
        }
        TEST_METHOD(SkeletonTest_cross_X1)
        {
            std::vector<Vector2d> polygon = 
            {
                Vector2d(-3, -1),
                Vector2d(-1, -1),
                Vector2d(-1, -3),
                Vector2d(1, -3),
                Vector2d(1, -1),
                Vector2d(3, -1),
                Vector2d(3, 1),
                Vector2d(1, 1),
                Vector2d(1, 3),
                Vector2d(-1, 3),
                Vector2d(-1, 1),
                Vector2d(-3, 1)
            };

            std::vector<Vector2d> expected = 
            {
                Vector2d(0, 0),
                Vector2d(0, 2),
                Vector2d(0, -2),
                Vector2d(2, 0),
                Vector2d(-2, 0)
            };

            expected.insert(expected.end(), polygon.begin(), polygon.end());

            auto sk = SkeletonBuilder::Build(polygon);

            Assert::IsTrue(AssertExpectedPoints(expected, GetFacePoints(sk)));
        }
        TEST_METHOD(SkeletonTest_double_split)
        {
            std::vector<Vector2d> polygon = 
            {
                Vector2d(-6, 0),
                Vector2d(-3, -6),
                Vector2d(-1, -2),
                Vector2d(1, -2),
                Vector2d(3, -6),
                Vector2d(6, 0)
            };

            std::vector<Vector2d> expected = 
            {
                Vector2d(-3.0000000000000004, -1.854101966249685),
                Vector2d(-1.6180339887498951, -1.0000000000000002),
                Vector2d(1.6180339887498951, -1.0000000000000002),
                Vector2d(3.0000000000000004, -1.854101966249685)
            };

            expected.insert(expected.end(), polygon.begin(), polygon.end());

            auto sk = SkeletonBuilder::Build(polygon);

            Assert::IsTrue(AssertExpectedPoints(expected, GetFacePoints(sk)));
        }
        TEST_METHOD(SkeletonTest_double_split2)
        {
            std::vector<Vector2d> polygon = 
            {
                Vector2d(-6, 0),
                Vector2d(-3, -6),
                Vector2d(-1, -2),
                Vector2d(0, -3),
                Vector2d(1, -2),
                Vector2d(3, -6),
                Vector2d(6, 0)
            };

            std::vector<Vector2d> expected = 
            {
                Vector2d(-3.0000000000000004, -1.854101966249685),
                Vector2d(-1.2038204263767998, -0.7440019398522527),
                Vector2d(-0.0, -1.242640687119285),
                Vector2d(1.2038204263767998, -0.7440019398522527),
                Vector2d(3.0000000000000004, -1.854101966249685)
            };

            expected.insert(expected.end(), polygon.begin(), polygon.end());

            auto sk = SkeletonBuilder::Build(polygon);

            AssertPolygonWithEdges(7, sk);

            Assert::IsTrue(AssertExpectedPoints(expected, GetFacePoints(sk)));
        }
        TEST_METHOD(SkeletonTest_multiple)
        {
            std::vector<Vector2d> polygon = { Vector2d(0, 0), Vector2d(5, 0), Vector2d(5, 5), Vector2d(0, 5) };

            std::vector<Vector2d> h1 = { Vector2d(1, 1), Vector2d(2, 1), Vector2d(2, 2), Vector2d(1, 2) };

            std::vector<Vector2d> h2 = { Vector2d(3, 3), Vector2d(4, 3), Vector2d(4, 4), Vector2d(3, 4) };

            std::vector<Vector2d> h3 = { Vector2d(1, 3), Vector2d(2, 3), Vector2d(2, 4), Vector2d(1, 4) };

            std::vector<Vector2d> h4 = { Vector2d(3, 1), Vector2d(4, 1), Vector2d(4, 2), Vector2d(3, 2) };

            std::vector<Vector2d> expected = 
            {
                Vector2d(4.5, 2.5),
                Vector2d(4.5, 0.5),
                Vector2d(4.5, 4.5),
                Vector2d(0.5, 4.5),
                Vector2d(2.5, 4.5),
                Vector2d(0.5, 0.5),
                Vector2d(0.5, 2.5),
                Vector2d(2.5, 0.5),
                Vector2d(2.5, 2.5),
                Vector2d(2.0, 2.0),
                Vector2d(2.0, 1.0),
                Vector2d(1.0, 1.0),
                Vector2d(1.0, 2.0),
                Vector2d(4.0, 4.0),
                Vector2d(4.0, 3.0),
                Vector2d(3.0, 3.0),
                Vector2d(3.0, 4.0),
                Vector2d(2.0, 4.0),
                Vector2d(2.0, 3.0),
                Vector2d(1.0, 3.0),
                Vector2d(1.0, 4.0),
                Vector2d(4.0, 2.0),
                Vector2d(4.0, 1.0),
                Vector2d(3.0, 1.0),
                Vector2d(3.0, 2.0)
            };

            expected.insert(expected.end(), polygon.begin(), polygon.end());

            std::vector<std::vector<Vector2d>> holes = { h1, h2, h3, h4 };

            auto sk = SkeletonBuilder::Build(polygon, holes);

            Assert::IsTrue(AssertExpectedPoints(expected, GetFacePoints(sk)));
        }       
	};
}