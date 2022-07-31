#include "Skeleton.h"

Skeleton::Skeleton(std::vector<EdgeResult> edges, std::map<Vector2d, double> distances)
{
	Edges = new std::vector<EdgeResult>(edges);
	Distances = new std::map< Vector2d, double>(distances);
}

Skeleton::~Skeleton()
{
	delete Edges;
	delete Distances;
}
