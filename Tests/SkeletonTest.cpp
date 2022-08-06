#pragma once
#include <iostream>
#include <string>
#include "pch.h"
#include "CppUnitTest.h"
#include "../StraightSkeleton/SkeletonBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SkeletonTest
{
    TEST_CLASS(SkeletonTest)
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

        static bool ContainsEpsilon(std::vector<Vector2d> list, Vector2d p)
        {
            return std::any_of(list.begin(), list.end(), [](Vector2d l) { return EqualEpsilon(l.X, l.Y) && EqualEpsilon(l.X, l.Y); });
            //list.Any(l = > EqualEpsilon(l.X, p.X) && EqualEpsilon(l.Y, p.Y));
        }

        static bool EqualEpsilon(double d1, double d2)
        {
            return fabs(d1 - d2) < 5E-6;
        }
    public:
        TEST_METHOD(CircularAddTest)
        {
            std::vector<Vector2d> polygon = {
                Vector2d(50, 50),
                Vector2d(100, 50),
                Vector2d(100, 100),
                Vector2d(50, 100)
            };
            
            std::vector<Vector2d> expected = {
                Vector2d(75.000000, 75.000000)
            };

            expected.insert(expected.end(), polygon.begin(), polygon.end());

            auto sk = SkeletonBuilder::Build(polygon);

            Assert::IsTrue(AssertExpectedPoints(expected, GetFacePoints(sk)));
        }
        TEST_METHOD(CircularAddTest2)
        {
            std::vector<Vector2d> polygon = {
                Vector2d(50, 50),
                Vector2d(150, 50),
                Vector2d(150, 100),
                Vector2d(50, 100)
            };

            std::vector<Vector2d> expected = {
                Vector2d(75.000000, 75.000000),
                Vector2d(125.000000, 75.000000)
            };

            expected.insert(expected.end(), polygon.begin(), polygon.end());

            auto sk = SkeletonBuilder::Build(polygon);

            Assert::IsTrue(AssertExpectedPoints(expected, GetFacePoints(sk)));
        }
        TEST_METHOD(SkeletonTest_hole_1)
        {
            std::vector<Vector2d> polygon = {
                Vector2d(-2, -2),
                Vector2d(2, -2),
                Vector2d(2, 2),
                Vector2d(-2, 2)
            };

            std::vector<Vector2d> hole = {
                Vector2d(-1, 1),
                Vector2d(1, 1),
                Vector2d(1, -1),
                Vector2d(-1, -1)
            };

            std::vector<std::vector<Vector2d>> holes = { hole };

            std::vector<Vector2d> expected = {
                Vector2d(-1.500000, -1.500000),
                Vector2d(-1.500000, 1.500000),
                Vector2d(1.500000, -1.500000),
                Vector2d(1.500000, 1.500000)
            };

            expected.insert(expected.end(), polygon.begin(), polygon.end());
            expected.insert(expected.end(), hole.begin(), hole.end());

            auto sk = SkeletonBuilder::Build(polygon, holes);

            Assert::IsTrue(AssertExpectedPoints(expected, GetFacePoints(sk)));
        }
        /*
        TEST_METHOD(SkeletonTest_hole_2)
        {

        }
        TEST_METHOD(SkeletonTest5)
        {

        }
        TEST_METHOD(SkeletonTest6_9)
        {

        }
        TEST_METHOD(SkeletonTest7)
        {

        }
        TEST_METHOD(SkeletonTest8)
        {

        }
        TEST_METHOD(SkeletonTest9)
        {

        }
        TEST_METHOD(SkeletonTestB1)
        {

        }
        TEST_METHOD(SkeletonTestB10)
        {

        }
        TEST_METHOD(SkeletonTestB11)
        {

        }
        TEST_METHOD(SkeletonTestB11_b)
        {

        }
        TEST_METHOD(SkeletonTestB12)
        {

        }
        TEST_METHOD(SkeletonTestB13)
        {

        }
        TEST_METHOD(SkeletonTestB2)
        {

        }
        TEST_METHOD(SkeletonTestB3__)
        {

        }
        TEST_METHOD(SkeletonTestB4__)
        {

        }
        TEST_METHOD(SkeletonTestB5__)
        {

        }
        TEST_METHOD(SkeletonTestB6__)
        {

        }
        TEST_METHOD(SkeletonTestB7__)
        {

        }
        TEST_METHOD(SkeletonTestB8__)
        {

        }
        TEST_METHOD(SkeletonTestC1)
        {

        }
        */
    };
}