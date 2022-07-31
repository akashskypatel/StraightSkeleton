#include "LavUtil.h"
#include "CircularList.h"

/// <summary> Check if two vertex are in the same lav. </summary>

bool LavUtil::IsSameLav(Vertex v1, Vertex v2)
{
    if (v1.List == nullptr || v2.List == nullptr)
        return false;
    return v1.List == v2.List;
}

void LavUtil::RemoveFromLav(Vertex* vertex)
{
    // if removed or not in list, skip
    if (vertex == nullptr || vertex->List == nullptr)
        return;
    vertex->Remove();
}

/// <summary>
///     Cuts all vertex after given startVertex and before endVertex. start and
///     and vertex are _included_ in cut result.
/// </summary>
/// <param name="startVertex">Start vertex.</param>
/// <param name="endVertex">End vertex.</param>
/// <returns> List of vertex in the middle between start and end vertex. </returns>

std::vector<Vertex*>* LavUtil::CutLavPart(Vertex* startVertex, Vertex* endVertex, std::vector<Vertex*>* ret)
{
    size_t size = startVertex->List->Size();
    Vertex* next = startVertex;

    for (size_t i = 0; i < size; i++)
    {
        Vertex* current = next;
        next = dynamic_cast<Vertex*>(current->Next.get());
        current->Remove();
        ret->push_back(current);

        if (current == endVertex)
            return ret;
    }

    throw std::exception("End vertex can't be found in start vertex lav");
}

/// <summary>
///     Add all vertex from "merged" lav into "base" lav. Vertex are added before
///     base vertex. Merged vertex order is reversed.
/// </summary>
/// <param name="base">Vertex from lav where vertex will be added.</param>
/// <param name="merged">Vertex from lav where vertex will be removed.</param>

void LavUtil::MergeBeforeBaseVertex(Vertex* base, Vertex* merged)
{
    size_t size = merged->List->Size();
    for (size_t i = 0; i < size; i++)
    {
        Vertex* nextMerged = dynamic_cast<Vertex*>(merged->Next.get());
        nextMerged->Remove();

        base->AddPrevious(std::make_shared<Vertex>(*nextMerged)); //TODO verify
    }
}

/// <summary>
///     Moves all nodes from given vertex lav, to new lav. All moved nodes are
///     added at the end of lav. The lav end is determined by first added vertex
///     to lav.
/// </summary>

void LavUtil::MoveAllVertexToLavEnd(Vertex* vertex, CircularList* newLaw)
{
    size_t size = vertex->List->Size();
    for (size_t i = 0; i < size; i++)
    {
        Vertex* ver = vertex;
        vertex = dynamic_cast<Vertex*>(vertex->Next.get());
        ver->Remove();
        newLaw->AddLast(std::make_shared<Vertex>(*ver)); //TODO: verify
    }
}
