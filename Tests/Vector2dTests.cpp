#pragma once
#include <iostream>
#include "pch.h"
#include "CppUnitTest.h"
#include "../StraightSkeleton/SkeletonBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Vector2dTests
{
	TEST_CLASS(Vector2dTests)
	{
	public:
		
		TEST_METHOD(Vector2dInit)
		{
			Vector2d vec = Vector2d(10.265, 84.526);
			Assert::IsTrue(vec.X == 10.265 && vec.Y == 84.526);
		}
		TEST_METHOD(Vector2dNegate)
		{
			Vector2d vec = Vector2d(10.265, 84.526);
			vec.Negate();
			Assert::IsTrue(vec.X == -10.265 && vec.Y == -84.526);
		}
		TEST_METHOD(Vector2dDistanceTo)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2 = Vector2d(2, 6);
			double dist = vec1.DistanceTo(vec2);
			Assert::IsTrue(fabs(dist - 8.24621) < 0.0001);
		}
		TEST_METHOD(Vector2dDot)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2 = Vector2d(2, 6);
			double dot = vec1.Dot(vec2);
			Assert::IsTrue(dot == (vec1.X * vec2.X + vec1.Y * vec2.Y));
		}
		TEST_METHOD(Vector2dDistanceSquared)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2 = Vector2d(2, 6);
			double dist = vec1.DistanceSquared(vec2);
			double var1 = vec1.X - vec2.X;
			double var2 = vec1.Y - vec2.Y;
			Assert::IsTrue(dist == (var1 * var1 + var2 * var2));
		}
		TEST_METHOD(Vector2dCopyCtor)
		{
			Vector2d vec1 = Vector2d(10.265, 84.526);
			Vector2d vec2(vec1);
			Assert::IsTrue(vec2.X == 10.265 && vec2.Y == 84.526);
		}
		TEST_METHOD(Vector2dEqual)
		{
			Vector2d vec1 = Vector2d(10.265, 84.526);
			Vector2d vec2 = Vector2d(vec1);
			Vector2d vec3 = Vector2d(12.2, 8.26);
			Assert::IsTrue(vec1 == vec2);
			Assert::IsTrue(vec1.Equals(vec2));
			Assert::IsFalse(vec1 == vec3);
			Assert::IsTrue(vec1 != vec3);
		}
		TEST_METHOD(Vector2dAddition)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2 = Vector2d(2, 6);
			Vector2d vec3 = vec1 + vec2;
			Assert::IsTrue(vec3.X == 12 && vec3.Y == 14);
		}
		TEST_METHOD(Vector2dSubtraction)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2 = Vector2d(2, 6);
			Vector2d vec3 = vec1 - vec2;
			Assert::IsTrue(vec3.X == 8 && vec3.Y == 2);
		}
		TEST_METHOD(Vector2dMultiplication)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2 = Vector2d(2, 6);
			Vector2d vec3 = vec1 * vec2;
			Assert::IsTrue(vec3.X == 20 && vec3.Y == 48);
		}
		TEST_METHOD(Vector2dNormalize)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2 = vec1.Normalized();
			vec1.Normalize();
			Assert::IsTrue(vec1.X == vec1.X * (1.0f / sqrt(vec1.X * vec1.X + vec1.Y * vec1.Y)));
			Assert::IsTrue(vec1.Y == vec1.Y * (1.0f / sqrt(vec1.X * vec1.X + vec1.Y * vec1.Y)));
			Assert::IsTrue(vec1 == vec2);
		}
		TEST_METHOD(Vector2dMltlyDblAsgnmt)
		{
			Vector2d vec1 = Vector2d(10, 8);
			vec1 *= 2;
			Assert::IsTrue(vec1.X == 20 && vec1.Y == 16);
		}
		TEST_METHOD(Vector2dMltlyV2dAsgnmt)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2 = Vector2d(4, 2);
			vec1 *= vec2;
			Assert::IsTrue(vec1.X == 40 && vec1.Y == 16);
			Assert::IsTrue(vec2.X == 4 && vec2.Y == 2);
		}
		TEST_METHOD(Vector2dAddV2dAsgnmt)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2 = Vector2d(4, 2);
			vec1 += vec2;
			Assert::IsTrue(vec1.X == 14 && vec1.Y == 10);
			Assert::IsTrue(vec2.X == 4 && vec2.Y == 2);
		}
		TEST_METHOD(Vector2dCopyCtorWork)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2(vec1);
			vec2 *= 2;
			Assert::IsTrue(vec2.X == 20 && vec2.Y == 16);
			Assert::IsTrue(vec1.X == 10 && vec1.Y == 8);
		}
		TEST_METHOD(Vector2dCopyAsgnmt)
		{
			Vector2d vec1 = Vector2d(10, 8);
			Vector2d vec2;
			vec2 = vec1;
			vec2 *= 2;
			Assert::IsTrue(vec2.X == 20 && vec2.Y == 16);
			Assert::IsTrue(vec1.X == 10 && vec1.Y == 8);
		}
	};
}
