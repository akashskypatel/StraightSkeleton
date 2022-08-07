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
    using spll2d = std::shared_ptr<LineLinear2d>;
    using splp2d = std::shared_ptr<LineParametric2d>;
    using spn = std::shared_ptr<CircularNode>;
    unsigned int _id;
    static unsigned int _idCounter;
public:
    struct HashFunction
    {
        size_t operator()(const Edge& val) const;
        size_t operator()(const std::shared_ptr<Edge> val) const;
    };
    friend class CircularNode;
    Edge();
    Edge(Vector2d begin,Vector2d end, spn nextNode = nullptr, spn prevNode = nullptr, CircularList* list = nullptr);
    Edge(spv2d begin, spv2d end);
    spv2d Begin = nullptr;               
    spv2d End = nullptr;                 
    spv2d Norm = nullptr;                
    splp2d BisectorNext = nullptr;       
    splp2d BisectorPrevious = nullptr;   
    spll2d lineLinear2d = nullptr;                  
    std::string ToString() const override;
    Edge& operator=(const Edge& val);
    unsigned int GetInstanceId() const;
};

