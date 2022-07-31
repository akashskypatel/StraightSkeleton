#pragma once
#include <string>
#include <format>
#include "LineLinear2d.h"

class LineParametric2d
{
public:
	Vector2d* A;
	Vector2d* U;
	static LineParametric2d Empty();
	LineParametric2d();
	LineParametric2d(const LineParametric2d& other);
	LineParametric2d(Vector2d pA, Vector2d pU);
	~LineParametric2d();
	LineLinear2d CreateLinearForm();
	static Vector2d Collide(LineParametric2d ray, LineLinear2d line, double epsilon);
	bool IsOnLeftSite(Vector2d point, double epsilon);
	bool IsOnRightSite(Vector2d point, double epsilon);
	std::string ToString() const;
};

