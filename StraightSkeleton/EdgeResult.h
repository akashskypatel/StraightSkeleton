#pragma once
#include <vector>
#include "Edge.h"
#include "Vector2d.h"
class EdgeResult
{
private:
	using spe = std::shared_ptr<Edge>;
public:
	spe edge;
	std::vector<Vector2d>* Polygon;
    EdgeResult(spe edge, std::vector<Vector2d>* polygon);
	~EdgeResult();
};

