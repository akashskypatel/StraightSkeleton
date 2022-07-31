#pragma once
#include <vector>
#include "Edge.h"
#include "Vector2d.h"
class EdgeResult
{
public:
	std::shared_ptr<Edge> edge;
	std::vector<Vector2d>* Polygon;
    EdgeResult(Edge edge, std::vector<Vector2d> polygon);
	~EdgeResult();
};

