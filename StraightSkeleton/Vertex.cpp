#include "Vertex.h"
#include "CircularList.h"

Vertex::Vertex()
{
    Point = nullptr;
    Bisector = nullptr;
    NextEdge = nullptr;
    PreviousEdge = nullptr;
    Distance = std::numeric_limits<double>::quiet_NaN();
    IsProcessed = false;
    LeftFace = nullptr;
    RightFace = nullptr;
}

Vertex::Vertex(spv2d point, double distance, splp2d bisector, spe previousEdge, spe nextEdge)
{
    Point = point;
    Bisector = bisector;
    NextEdge = nextEdge;
    PreviousEdge = previousEdge;
    Distance = distance;
    IsProcessed = false;
    LeftFace = nullptr;
    RightFace = nullptr;
}

Vertex& Vertex::operator = (const Vertex& other)
{
    if (this != &other)
    {
        Point = other.Point;
        Distance = other.Distance;
        Bisector = other.Bisector;
        PreviousEdge = other.PreviousEdge;
        NextEdge = other.NextEdge;
        IsProcessed = other.IsProcessed;
        LeftFace = other.LeftFace;
        RightFace = other.RightFace;
    }
    return *this;
}

std::string Vertex::ToString() const
{
    return std::format("Vertex [v={0}, IsProcessed={1}, Bisector={2}, PreviousEdge={3}, NextEdge={4}]", Point->ToString(), IsProcessed, Bisector->ToString(), PreviousEdge->ToString(), NextEdge->ToString());
}

double Vertex::Round(double value, double precision)
{
    double p10 = pow(10.0f, precision);
    return round(value * p10) / p10;
}

Vertex::~Vertex()
{
    Point = nullptr;
    Bisector = nullptr;
    NextEdge = nullptr;
    PreviousEdge = nullptr;
    Distance = std::numeric_limits<double>::quiet_NaN();
    IsProcessed = false;
    LeftFace = nullptr;
    RightFace = nullptr;
}