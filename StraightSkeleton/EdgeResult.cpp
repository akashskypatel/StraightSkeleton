#include "EdgeResult.h"

EdgeResult::EdgeResult(spe edge, std::vector<Vector2d>* polygon)
{
    this->edge = edge;
    Polygon = polygon;
}

EdgeResult::~EdgeResult()
{
    //delete edge;
    //delete Polygon;
}
