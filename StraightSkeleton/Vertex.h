#pragma once
#include <string>
#include <format>
#include <limits>
#include "Edge.h"
#include "Vector2d.h"
#include "LineParametric2d.h"
#include "FaceNode.h"
#include "CircularNode.h"

class Vertex : public CircularNode
{    
private:
    using spn = std::shared_ptr<CircularNode>;
    using spfn = std::shared_ptr<FaceNode>;
    using spv2d = std::shared_ptr<Vector2d>;
    using splp2d = std::shared_ptr<LineParametric2d>;
    using spe = std::shared_ptr<Edge>;
    unsigned int _id;
    static unsigned int _idCounter;
    const int RoundDigitCount = 5;
    double Round(double value, double precision);
public:
    struct HashFunction
    {
        size_t operator()(const Vertex& val) const;
        size_t operator()(const std::shared_ptr<Vertex> val) const;
    };
    friend class CircularNode;
    spv2d Point = nullptr;
    double Distance;
    splp2d Bisector = nullptr;
    spe NextEdge = nullptr;
    spe PreviousEdge = nullptr;
    bool IsProcessed;

    Vertex();
    //Vertex(const Vertex& val);
    //Vertex(Vector2d point, double distance, LineParametric2d bisector, Edge previousEdge, Edge nextEdge, spn nextNode = nullptr, spn prevNode = nullptr, CircularList* list = nullptr);
    //Vertex(Vector2d* point, double distance, LineParametric2d* bisector, Edge* previousEdge, Edge* nextEdge);
    Vertex(spv2d point, double distance, splp2d bisector, spe previousEdge, spe nextEdge);
    Vertex& operator = (const Vertex& other);
    bool operator==(const Vertex& other) const;
    std::string ToString() const override;
    unsigned int GetInstanceId() const;
    spfn LeftFace = nullptr;
    spfn RightFace = nullptr;
};

