#include "Skeleton.h"

Skeleton::Skeleton(std::vector<EdgeResult>* edges, std::map<Vector2d, double>* distances)
{
	Edges = edges;
	Distances = distances;
}

Skeleton::~Skeleton()
{
	//delete Edges;
	//delete Distances;
}
