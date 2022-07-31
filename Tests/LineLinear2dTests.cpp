#pragma once
#include <iostream>
#include <limits>
#include "pch.h"
#include "CppUnitTest.h"
#include "../StraightSkeleton/LineLinear2d.h"
#include "../StraightSkeleton/LineLinear2d.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LineLinear2dTests
{
	TEST_CLASS(LineLinear2dTests)
	{
		TEST_METHOD(LL2dConstrctor)
		{
			LineLinear2d line1 = LineLinear2d(Vector2d(10.0, 2.0), Vector2d(20.0, 36.0));
			Assert::IsTrue(line1.A == (2.0 - 36.0));
			Assert::IsTrue(line1.B == (20.0 - 10.0));
			Assert::IsTrue(line1.C == (10.0 * 36.0 - 20.0 * 2.0));
			LineLinear2d line2 = LineLinear2d((-34.0), (10.0), (320.0));
			Assert::IsTrue(line2.A == (-34.0));
			Assert::IsTrue(line2.B == (10.0));
			Assert::IsTrue(line2.C == (320));
		}
		TEST_METHOD(LL2dCollide)
		{
			Assert::IsTrue(1 == 1);
		}
	};
}