#pragma once
#include <vector>
#include "Vertex.h"

class LavUtil
{
    /// <summary> Check if two vertex are in the same lav. </summary>
    static bool IsSameLav(Vertex v1, Vertex v2);
    static void RemoveFromLav(Vertex* vertex);
    /// <summary>
    ///     Cuts all vertex after given startVertex and before endVertex. start and
    ///     and vertex are _included_ in cut result.
    /// </summary>
    /// <param name="startVertex">Start vertex.</param>
    /// <param name="endVertex">End vertex.</param>
    /// <returns> List of vertex in the middle between start and end vertex. </returns>
    static std::vector<Vertex*>* CutLavPart(Vertex* startVertex, Vertex* endVertex, std::vector<Vertex*>* ret);
    /// <summary>
    ///     Add all vertex from "merged" lav into "base" lav. Vertex are added before
    ///     base vertex. Merged vertex order is reversed.
    /// </summary>
    /// <param name="base">Vertex from lav where vertex will be added.</param>
    /// <param name="merged">Vertex from lav where vertex will be removed.</param>
    static void MergeBeforeBaseVertex(Vertex* base, Vertex* merged);
    /// <summary>
    ///     Moves all nodes from given vertex lav, to new lav. All moved nodes are
    ///     added at the end of lav. The lav end is determined by first added vertex
    ///     to lav.
    /// </summary>
    static void MoveAllVertexToLavEnd(Vertex* vertex, CircularList* newLaw);

};

