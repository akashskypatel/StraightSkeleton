#include "LineParametric2d.h"
#include "PrimitiveUtils.h"

LineParametric2d LineParametric2d::Empty()
{
	return LineParametric2d();
}

LineParametric2d::LineParametric2d()
{
	A = nullptr;
	U = nullptr;
}
/*
LineParametric2d::LineParametric2d(const LineParametric2d& other)
{
	A = new Vector2d(*other.A);
	U = new Vector2d(*other.U);
}
*/
LineParametric2d::LineParametric2d(Vector2d* pA, Vector2d pU)
{
	//A = new Vector2d(pA.X, pA.Y);
	//U = new Vector2d(pU.X, pU.Y);
	A = pA;
	U = std::make_shared<Vector2d>(pU);
}

LineParametric2d::~LineParametric2d()
{
	//delete A;
	//delete U;
}

LineLinear2d LineParametric2d::CreateLinearForm()
{
	double x = A->X;
	double y = A->Y;

	double B = -U->X;
	double A = U->Y;

	double C = -(A * x + B * y);
	return LineLinear2d(A, B, C);
}

Vector2d LineParametric2d::Collide(LineParametric2d ray, LineLinear2d line, double epsilon)
{
	Vector2d collide = LineLinear2d::Collide(ray.CreateLinearForm(), line);
	if (collide.Equals(Vector2d::Empty()))
		return Vector2d::Empty();

	Vector2d collideVector = collide - *ray.A;
	return ray.U->Dot(collideVector) < epsilon ? Vector2d::Empty() : collide;
}

bool LineParametric2d::IsOnLeftSite(Vector2d point, double epsilon)
{
	Vector2d direction = point - *A;
	return PrimitiveUtils::OrthogonalRight(*U).Dot(direction) < epsilon;
}

bool LineParametric2d::IsOnRightSite(Vector2d point, double epsilon)
{
	Vector2d direction = point - *A;
	return PrimitiveUtils::OrthogonalRight(*U).Dot(direction) > -epsilon;
}

std::string LineParametric2d::ToString() const
{
	return std::format("Line [A={0}, U={1}]", A->ToString(), U->ToString());
}
