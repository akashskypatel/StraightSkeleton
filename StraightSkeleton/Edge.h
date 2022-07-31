#pragma once
#include <iostream>
#include <string>
#include <format>
#include <memory>
#include "Vector2d.h"
#include "LineParametric2d.h"
#include "CircularNode.h"

class CircularList;
class Edge : public CircularNode
{
private:
    using spv2d = std::shared_ptr<Vector2d>;
    using spn = std::shared_ptr<CircularNode>;
public:
    friend class CircularNode;
    Edge();
    Edge(const Edge& val, spn nextNode = nullptr, spn prevNode = nullptr, CircularList* list = nullptr);
    Edge(Vector2d begin,Vector2d end, spn nextNode = nullptr, spn prevNode = nullptr, CircularList* list = nullptr);
    Edge(spv2d begin, spv2d end);
    ~Edge() override;
    std::shared_ptr<Vector2d> Begin = nullptr;                      // Vector2d* Begin;
    std::shared_ptr<Vector2d> End = nullptr;                        // Vector2d* End;
    std::shared_ptr<Vector2d> Norm = nullptr;                       // Vector2d* Norm;
    std::shared_ptr<LineParametric2d> BisectorNext = nullptr;       // LineParametric2d* BisectorNext
    std::shared_ptr<LineParametric2d> BisectorPrevious = nullptr;   // LineParametric2d* BisectorPrevious;
    std::shared_ptr<LineLinear2d> lineLinear2d = nullptr;           // LineLinear2d* lineLinear2d; 
    std::string ToString() const override;
    Edge& operator=(const Edge& val);
};

