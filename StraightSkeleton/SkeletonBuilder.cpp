#include "SkeletonBuilder.h"
#include "CircularList.h"

/// <summary>
///     Take next lav vertex _AFTER_ given edge, find vertex is always on RIGHT
///     site of edge.
/// </summary>

inline Vertex* SkeletonBuilder::GetEdgeInLav(CircularList& lav, Edge& oppositeEdge)
{
	for (auto node : lav)
	{
		auto e = dynamic_cast<Vertex*>(node);
		auto epn = std::dynamic_pointer_cast<Edge>(e->Previous->Next);
		if (&oppositeEdge == e->PreviousEdge || &oppositeEdge == epn.get()) //probably not gonna work
			return e;
	}
	return nullptr;
}

inline void SkeletonBuilder::AddFaceBack(Vertex newVertex, Vertex* va, Vertex* vb)
{
	std::shared_ptr<FaceNode> fn = std::make_shared<FaceNode>(FaceNode(newVertex));
	va->RightFace->AddPush(fn);
	FaceQueueUtil::ConnectQueues(fn, vb->LeftFace);
}

inline void SkeletonBuilder::AddFaceRight(Vertex newVertex, Vertex vb)
{
	std::shared_ptr<FaceNode> fn = std::make_shared<FaceNode>(FaceNode(newVertex));
	vb.RightFace->AddPush(fn);
	newVertex.RightFace = fn;
}

inline void SkeletonBuilder::AddFaceLeft(Vertex newVertex, Vertex va)
{
	std::shared_ptr<FaceNode> fn = std::make_shared<FaceNode>(FaceNode(newVertex));
	va.LeftFace->AddPush(fn);
	newVertex.LeftFace = fn;
}

inline double SkeletonBuilder::CalcDistance(Vector2d intersect, Edge currentEdge)
{
	Vector2d edge = *currentEdge.End - *currentEdge.Begin;
	Vector2d vector = intersect - *currentEdge.Begin;
	Vector2d pointOnVector = PrimitiveUtils::OrthogonalProjection(edge, vector);
	return vector.DistanceTo(pointOnVector);
}

inline Vector2d SkeletonBuilder::CalcVectorBisector(Vector2d norm1, Vector2d norm2)
{
	return PrimitiveUtils::BisectorNormalized(norm1, norm2);
}

inline std::shared_ptr<LineParametric2d> SkeletonBuilder::CalcBisector(Vector2d* p, Edge e1, Edge e2)
{
	Vector2d norm1 = *e1.Norm;
	Vector2d norm2 = *e2.Norm;
	Vector2d bisector = CalcVectorBisector(norm1, norm2);
	return std::make_shared<LineParametric2d>(p, bisector);
}
/*
Skeleton SkeletonBuilder::Build(std::vector<Vector2d>& polygon)
{
	std::vector<std::vector<Vector2d>> holes;
	return Build(polygon, holes);
}

Skeleton SkeletonBuilder::Build(std::vector<Vector2d>& polygon, std::vector<std::vector<Vector2d>>& holes)
{
	InitPolygon(polygon);
	MakeClockwise(holes);
	
}
*/
std::vector<Vector2d> SkeletonBuilder::InitPolygon(std::vector<Vector2d>& polygon)
{
	if (polygon.size() == 0)
		throw std::exception("polygon can't be null");
	if(polygon[0].Equals(polygon[polygon.size() - 1]))
		throw std::exception("polygon can't start and end with the same point");

	return MakeCounterClockwise(polygon);
}

std::vector<std::vector<Vector2d>>& SkeletonBuilder::MakeClockwise(std::vector<std::vector<Vector2d>>& holes)
{
	if (holes.size() == 0)
		return holes;
	for (auto hole : holes)
	{
		if (!PrimitiveUtils::IsClockwisePolygon(hole))
		{
			std::reverse(hole.begin(), hole.end());
		}
	}
	return holes;
}

std::vector<Vector2d> SkeletonBuilder::MakeCounterClockwise(std::vector<Vector2d>& polygon)
{
	return PrimitiveUtils::MakeCounterClockwise(polygon);
}
/*
void SkeletonBuilder::InitSlav(std::vector<Vector2d>& polygon, std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>& sLav, std::vector<std::shared_ptr<Edge>>& edges, std::vector<FaceQueue>& faces)
{	
	
	CircularList edgesList;
	size_t size = polygon.size();
	for (size_t i = 0; i < size; i++)
	{
		size_t j = (i + 1) % size;
		edgesList.AddLast(std::shared_ptr<Edge>(Edge(polygon[i], polygon[j])));
	}
	for (auto edge : edgesList)
	{
		auto nextEdge =  std::dynamic_pointer_cast<Edge>(edge->Next);
		auto curEdge = std::dynamic_pointer_cast<Edge>(edge);
		auto end = *std::dynamic_pointer_cast<Edge>(edge)->End;
		auto bisector = CalcBisector(end, *curEdge, *nextEdge.get());

		curEdge->BisectorNext = bisector;
		nextEdge->BisectorPrevious = bisector;
		edges.push_back(curEdge);
	}
	std::shared_ptr<CircularList> lav = std::make_shared<CircularList>();
	sLav.insert(lav);
	for (auto edge : edgesList)
	{
		auto curEdge = std::dynamic_pointer_cast<Edge>(edge);
		auto nextEdge = std::dynamic_pointer_cast<Edge>(edge->Next);
		auto vertex = std::make_shared<Vertex>(Vertex(curEdge->End, 0, curEdge->BisectorNext, curEdge, nextEdge));
		lav->AddLast(vertex);
	}
	for (auto vertex : *lav)
	{
		auto next = std::dynamic_pointer_cast<Vertex>(vertex->Next);
		auto curVertex = std::dynamic_pointer_cast<Vertex>(vertex);
		// create face on right site of vertex
		
		auto rightFace = std::shared_ptr<FaceNode>(FaceNode(curVertex));

		var faceQueue = new FaceQueue();
		faceQueue.Edge = (vertex.NextEdge);

		faceQueue.AddFirst(rightFace);
		faces.Add(faceQueue);
		vertex.RightFace = rightFace;

		// create face on left site of next vertex
		var leftFace = new FaceNode(next);
		rightFace.AddPush(leftFace);
		next.LeftFace = leftFace;
		
	}
	
}
*/
