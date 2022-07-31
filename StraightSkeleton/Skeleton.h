#pragma once
#include <vector>
#include <map>
#include "EdgeResult.h"
#include "Vector2d.h"

class Skeleton
{
public:
	std::vector<EdgeResult>* Edges;
	std::map<Vector2d, double>* Distances;
	Skeleton(std::vector<EdgeResult> edges, std::map< Vector2d, double> distances);
	~Skeleton();
};

