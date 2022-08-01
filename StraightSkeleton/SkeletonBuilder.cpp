#include "SkeletonBuilder.h"
#include "CircularList.h"

const double SkeletonBuilder::SplitEpsilon = 1E-10;

/// <summary>
///     Take next lav vertex _AFTER_ given edge, find vertex is always on RIGHT
///     site of edge.
/// </summary>

inline std::shared_ptr<Vertex> SkeletonBuilder::GetEdgeInLav(CircularList& lav, Edge& oppositeEdge)
{
	for (auto node : lav)
	{
		auto e = dynamic_pointer_cast<Vertex>(node);
		auto epn = std::dynamic_pointer_cast<Edge>(e->Previous->Next);
		if (&oppositeEdge == e->PreviousEdge.get() || &oppositeEdge == epn.get()) //probably not gonna work
			return e;
	}
	return nullptr;
}

inline void SkeletonBuilder::AddFaceBack(std::shared_ptr<Vertex> newVertex, Vertex* va, Vertex* vb)
{
	std::shared_ptr<FaceNode> fn = std::make_shared<FaceNode>(FaceNode(newVertex));
	va->RightFace->AddPush(fn);
	FaceQueueUtil::ConnectQueues(fn, vb->LeftFace);
}

inline void SkeletonBuilder::AddFaceRight(std::shared_ptr<Vertex> newVertex, Vertex vb)
{
	std::shared_ptr<FaceNode> fn = std::make_shared<FaceNode>(FaceNode(newVertex));
	vb.RightFace->AddPush(fn);
	newVertex->RightFace = fn;
}

inline void SkeletonBuilder::AddFaceLeft(std::shared_ptr<Vertex> newVertex, Vertex va)
{
	std::shared_ptr<FaceNode> fn = std::make_shared<FaceNode>(FaceNode(newVertex));
	va.LeftFace->AddPush(fn);
	newVertex->LeftFace = fn;
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

inline std::shared_ptr<LineParametric2d> SkeletonBuilder::CalcBisector(std::shared_ptr<Vector2d> p, Edge e1, Edge e2)
{
	Vector2d norm1 = *e1.Norm;
	Vector2d norm2 = *e2.Norm;
	auto bisector = std::make_shared<Vector2d>(CalcVectorBisector(norm1, norm2));
	return std::make_shared<LineParametric2d>(LineParametric2d(p, bisector));
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

void SkeletonBuilder::InitSlav(std::vector<Vector2d>& polygon, std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>& sLav, std::vector<std::shared_ptr<Edge>>& edges, std::vector<FaceQueue*>& faces)
{
	CircularList edgesList;
	size_t size = polygon.size();
	for (size_t i = 0; i < size; i++)
	{
		size_t j = (i + 1) % size;
		edgesList.AddLast(std::make_shared<Edge>(Edge(polygon[i], polygon[j])));
	}
	for (auto edge : edgesList)
	{
		auto nextEdge =  std::dynamic_pointer_cast<Edge>(edge->Next);
		auto curEdge = dynamic_pointer_cast<Edge>(edge);
		auto end = dynamic_pointer_cast<Edge>(edge)->End;
		auto bisector = CalcBisector(end, *curEdge, *nextEdge.get());

		curEdge->BisectorNext = bisector;
		nextEdge->BisectorPrevious = bisector;
		edges.push_back(curEdge);
	}
	std::shared_ptr<CircularList> lav = std::make_shared<CircularList>();
	sLav.insert(lav);
	for (auto edge : edgesList)
	{
		auto curEdge = dynamic_pointer_cast<Edge>(edge);
		auto nextEdge = std::dynamic_pointer_cast<Edge>(edge->Next);
		auto vertex = std::make_shared<Vertex>(Vertex(curEdge->End, 0, curEdge->BisectorNext, curEdge, nextEdge));
		lav->AddLast(vertex);
	}
	for (auto vertex : *lav)
	{
		auto next = std::dynamic_pointer_cast<Vertex>(vertex->Next);
		auto curVertex = dynamic_pointer_cast<Vertex>(vertex);
		// create face on right site of vertex
		
		auto rightFace = std::make_shared<FaceNode>(FaceNode(curVertex));

		auto faceQueue = std::make_shared<FaceQueue>(FaceQueue());
		faceQueue->SetEdge(curVertex->NextEdge);

		faceQueue->AddFirst(rightFace);
		faces.push_back(faceQueue.get());
		curVertex->RightFace = rightFace;

		// create face on left site of next vertex
		auto leftFace = std::make_shared<FaceNode>(FaceNode(next));
		rightFace->AddPush(leftFace);
		next->LeftFace = leftFace;
	}
}

bool SkeletonBuilder::EdgeBehindBisector(LineParametric2d bisector, LineLinear2d edge)
{
	return LineParametric2d::Collide(bisector, edge, SplitEpsilon) == Vector2d::Empty();
}

std::shared_ptr<SkeletonBuilder::SplitCandidate> SkeletonBuilder::CalcCandidatePointForSplit(std::shared_ptr<Vertex> vertex, std::shared_ptr<Edge> edge)
{
	auto vertexEdge = ChoseLessParallelVertexEdge(vertex, edge);
	if (vertexEdge == nullptr)
		return nullptr;

	const auto& vertexEdteNormNegate = *vertexEdge->Norm;
	auto edgesBisector = CalcVectorBisector(vertexEdteNormNegate, *edge->Norm);
	auto edgesCollide = vertexEdge->lineLinear2d->Collide(*edge->lineLinear2d);

	// Check should be performed to exclude the case when one of the
	// line segments starting at V is parallel to ei.
	if (edgesCollide == Vector2d::Empty())
		throw std::exception("Ups this should not happen");

	auto edgesBisectorLine = std::make_shared<LineLinear2d>(LineParametric2d(edgesCollide, edgesBisector).CreateLinearForm());

	// Compute the coordinates of the candidate point Bi as the intersection
	// between the bisector at V and the axis of the angle between one of
	// the edges starting at V and the tested line segment ei
	auto candidatePoint = std::make_shared<Vector2d>(LineParametric2d::Collide(*vertex->Bisector, *edgesBisectorLine, SplitEpsilon));

	if (*candidatePoint == Vector2d::Empty())
		return nullptr;

	if (edge->BisectorPrevious->IsOnRightSite(*candidatePoint, SplitEpsilon)
		&& edge->BisectorNext->IsOnLeftSite(*candidatePoint, SplitEpsilon))
	{
		auto distance = CalcDistance(*candidatePoint, *edge);

		if (edge->BisectorPrevious->IsOnLeftSite(*candidatePoint, SplitEpsilon))
			return std::make_shared<SplitCandidate>(SplitCandidate(candidatePoint, distance, nullptr, edge->Begin));
		if (edge->BisectorNext->IsOnRightSite(*candidatePoint, SplitEpsilon))
			return std::make_shared<SplitCandidate>(SplitCandidate(candidatePoint, distance, nullptr, edge->Begin));

		return std::make_shared<SplitCandidate>(SplitCandidate(candidatePoint, distance, edge, std::make_shared<Vector2d>(Vector2d::Empty())));
	}
	return nullptr;
}

std::shared_ptr<Edge> SkeletonBuilder::ChoseLessParallelVertexEdge(std::shared_ptr<Vertex> vertex, std::shared_ptr<Edge> edge)
{
	auto edgeA = vertex->PreviousEdge;
	auto edgeB = vertex->NextEdge;

	auto vertexEdge = edgeA;

	auto edgeADot = fabs(edge->Norm->Dot(*edgeA->Norm));
	auto edgeBDot = fabs(edge->Norm->Dot(*edgeB->Norm));

	// both lines are parallel to given edge
	if (edgeADot + edgeBDot >= 2 - SplitEpsilon)
		return nullptr;

	// Simple check should be performed to exclude the case when one of
	// the line segments starting at V (vertex) is parallel to e_i
	// (edge) we always chose edge which is less parallel.
	if (edgeADot > edgeBDot)
		vertexEdge = edgeB;

	return vertexEdge;
}


std::shared_ptr<std::vector<SkeletonBuilder::SplitCandidate>> SkeletonBuilder::CalcOppositeEdges(std::shared_ptr<Vertex> vertex, std::vector<std::shared_ptr<Edge>>& edges)
{
	auto ret = std::make_shared<std::vector<SkeletonBuilder::SplitCandidate>>();
	for(auto edgeEntry : edges)
	{
		auto edge = edgeEntry->lineLinear2d;
		// check if edge is behind bisector
		if (EdgeBehindBisector(*vertex->Bisector, *edge))
			continue;

		// compute the coordinates of the candidate point Bi
		auto candidatePoint = CalcCandidatePointForSplit(vertex, edgeEntry);
		if (candidatePoint != nullptr)
			ret->push_back(*candidatePoint);
	}
	std::sort(ret->begin(), ret->end(), SkeletonBuilder::SplitCandidateComparer());
	return ret;
}

void SkeletonBuilder::ComputeSplitEvents(std::shared_ptr<Vertex> vertex, std::vector<std::shared_ptr<Edge>>& edges, std::priority_queue<std::shared_ptr<SkeletonEvent>>& queue, double distanceSquared)
{
	auto source = vertex->Point;
	auto oppositeEdges = CalcOppositeEdges(vertex, edges);

	// check if it is vertex split event
	for(auto oppositeEdge : *oppositeEdges)
	{
		auto point = oppositeEdge.Point;

		if (fabs(distanceSquared - (-1)) > SplitEpsilon)
		{
			if (source->DistanceSquared(*point) > distanceSquared + SplitEpsilon)
			{
				// Current split event distance from source of event is
				// greater then for edge event. Split event can be reject.
				// Distance from source is not the same as distance for
				// edge. Two events can have the same distance to edge but
				// they will be in different distance form its source.
				// Unnecessary events should be reject otherwise they cause
				// problems for degenerate cases.
				continue;
			}
		}

		// check if it is vertex split event
		if (*oppositeEdge.OppositePoint != Vector2d::Empty())
		{
			// some of vertex event can share the same opposite point
			queue.push(std::make_shared<VertexSplitEvent>(VertexSplitEvent(point, oppositeEdge.Distance, vertex)));
			continue;
		}
		queue.push(std::make_shared<SplitEvent>(SplitEvent(point, oppositeEdge.Distance, vertex, oppositeEdge.OppositeEdge)));
	}
}