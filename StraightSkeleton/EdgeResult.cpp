#include "EdgeResult.h"

EdgeResult::EdgeResult(Edge edge, std::vector<Vector2d> polygon)
{
    this->edge = std::make_shared<Edge>(Edge(edge));
    Polygon = new std::vector<Vector2d>(polygon);
}

EdgeResult::~EdgeResult()
{
    //delete edge;
    //delete Polygon;
}
