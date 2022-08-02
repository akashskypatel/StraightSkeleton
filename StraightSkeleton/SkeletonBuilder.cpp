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
	std::shared_ptr<FaceNode> fn = std::make_shared<FaceNode>(newVertex);
	va->RightFace->AddPush(fn);
	FaceQueueUtil::ConnectQueues(fn, vb->LeftFace);
}

inline void SkeletonBuilder::AddFaceRight(std::shared_ptr<Vertex> newVertex, Vertex vb)
{
	std::shared_ptr<FaceNode> fn = std::make_shared<FaceNode>(newVertex);
	vb.RightFace->AddPush(fn);
	newVertex->RightFace = fn;
}

inline void SkeletonBuilder::AddFaceLeft(std::shared_ptr<Vertex> newVertex, Vertex va)
{
	std::shared_ptr<FaceNode> fn = std::make_shared<FaceNode>(newVertex);
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

void SkeletonBuilder::InitSlav(std::vector<Vector2d>& polygon, std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>& sLav, std::vector<std::shared_ptr<Edge>>& edges, std::vector<FaceQueue*>& faces)
{
	CircularList edgesList;
	size_t size = polygon.size();
	for (size_t i = 0; i < size; i++)
	{
		size_t j = (i + 1) % size;
		edgesList.AddLast(std::make_shared<Edge>(polygon[i], polygon[j]));
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
		auto vertex = std::make_shared<Vertex>(curEdge->End, 0, curEdge->BisectorNext, curEdge, nextEdge);
		lav->AddLast(vertex);
	}
	for (auto vertex : *lav)
	{
		auto next = std::dynamic_pointer_cast<Vertex>(vertex->Next);
		auto curVertex = dynamic_pointer_cast<Vertex>(vertex);
		// create face on right site of vertex
		
		auto rightFace = std::make_shared<FaceNode>(curVertex);

		auto faceQueue = std::make_shared<FaceQueue>();
		faceQueue->SetEdge(curVertex->NextEdge);

		faceQueue->AddFirst(rightFace);
		faces.push_back(faceQueue.get());
		curVertex->RightFace = rightFace;

		// create face on left site of next vertex
		auto leftFace = std::make_shared<FaceNode>(next);
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

		return std::make_shared<SplitCandidate>(candidatePoint, distance, edge, std::make_shared<Vector2d>(Vector2d::Empty()));
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
			queue.push(std::make_shared<VertexSplitEvent>(point, oppositeEdge.Distance, vertex));
			continue;
		}
		queue.push(std::make_shared<SplitEvent>(point, oppositeEdge.Distance, vertex, oppositeEdge.OppositeEdge));
	}
}

Vector2d SkeletonBuilder::ComputeIntersectionBisectors(std::shared_ptr<Vertex> vertexPrevious, std::shared_ptr<Vertex> vertexNext)
{
	auto bisectorPrevious = vertexPrevious->Bisector;
	auto bisectorNext = vertexNext->Bisector;

	auto intersectRays2d = PrimitiveUtils::IntersectRays2D(*bisectorPrevious, *bisectorNext);
	auto intersect = intersectRays2d.Intersect;

	// skip the same points
	if (*vertexPrevious->Point == intersect || *vertexNext->Point == intersect)
		return Vector2d::Empty();

	return intersect;
}

std::shared_ptr<SkeletonEvent> SkeletonBuilder::CreateEdgeEvent(std::shared_ptr<Vector2d> point, std::shared_ptr<Vertex> previousVertex, std::shared_ptr<Vertex> nextVertex)
{
	return std::make_shared<EdgeEvent>(point, CalcDistance(*point, *previousVertex->NextEdge), previousVertex, nextVertex);
}

double SkeletonBuilder::ComputeCloserEdgeEvent(std::shared_ptr<Vertex> vertex, std::priority_queue<std::shared_ptr<SkeletonEvent>>& queue)
{
	auto nextVertex = std::dynamic_pointer_cast<Vertex>(vertex->Next);
	auto previousVertex = std::dynamic_pointer_cast<Vertex>(vertex->Previous);

	auto point = vertex->Point;

	// We need to chose closer edge event. When two evens appear in epsilon
	// we take both. They will create single MultiEdgeEvent.
	auto point1 = std::make_shared<Vector2d>(ComputeIntersectionBisectors(vertex, nextVertex));
	auto point2 = std::make_shared<Vector2d>(ComputeIntersectionBisectors(previousVertex, vertex));

	if (*point1 == Vector2d::Empty() && *point2 == Vector2d::Empty())
		return -1;

	auto distance1 = DBL_MAX;
	auto distance2 = DBL_MAX;

	if (*point1 != Vector2d::Empty())
		distance1 = point->DistanceSquared(*point1);
	if (*point2 != Vector2d::Empty())
		distance2 = point->DistanceSquared(*point2);

	if (fabs(distance1 - SplitEpsilon) < distance2)
		queue.push(CreateEdgeEvent(point1, vertex, nextVertex));
	if (fabs(distance2 - SplitEpsilon) < distance1)
		queue.push(CreateEdgeEvent(point2, previousVertex, vertex));

	return distance1 < distance2 ? distance1 : distance2;
}

int SkeletonBuilder::AssertMaxNumberOfInteraction(int& count)
{
	count++;
	if (count > 10000)
		throw std::exception("Too many interaction: bug?");
	return count;
}

void SkeletonBuilder::ComputeEdgeEvents(std::shared_ptr<Vertex> previousVertex, std::shared_ptr<Vertex> nextVertex,	std::priority_queue<std::shared_ptr<SkeletonEvent>>& queue)
{
	auto point = std::make_shared<Vector2d>(ComputeIntersectionBisectors(previousVertex, nextVertex));
	if (*point != Vector2d::Empty())
		queue.push(CreateEdgeEvent(point, previousVertex, nextVertex));
}

void SkeletonBuilder::InitEvents(std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>& sLav, std::priority_queue<std::shared_ptr<SkeletonEvent>>& queue, std::vector<std::shared_ptr<Edge>>& edges)
{
	for (auto lav : sLav)
	{
		for (auto vertex : *lav)
		{
			auto curVertex = std::dynamic_pointer_cast<Vertex>(vertex);
			ComputeSplitEvents(curVertex, edges, queue, -1);
		}
	}
	for (auto lav : sLav)
	{
		for (auto vertex : *lav)
		{
			auto curVertex = std::dynamic_pointer_cast<Vertex>(vertex);
			auto nextVertex = std::dynamic_pointer_cast<Vertex>(vertex->Next);
			ComputeEdgeEvents(curVertex, nextVertex, queue);
		}
	}
}

std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>> SkeletonBuilder::LoadLevelEvents(std::priority_queue<std::shared_ptr<SkeletonEvent>>& queue)
{
	auto level = std::make_shared<std::vector<std::shared_ptr<SkeletonEvent>>>();
	std::shared_ptr<SkeletonEvent> levelStart = nullptr;
	// skip all obsolete events in level
	do
	{
		if (queue.empty())
		{
			levelStart = nullptr;
		} 
		else
		{
			levelStart = queue.top();
			queue.pop();
		}
		//levelStart = queue.empty() ? nullptr : queue.top();
	} while (levelStart != nullptr && levelStart->IsObsolete());


	// all events obsolete
	if (levelStart == nullptr || levelStart->IsObsolete())
		return level;

	auto levelStartHeight = levelStart->Distance;

	level->push_back(levelStart);

	std::shared_ptr<SkeletonEvent> event = nullptr;
	while ((event = queue.top()) != nullptr &&
		fabs(event->Distance - levelStartHeight) < SplitEpsilon)
	{
		auto nextLevelEvent = queue.top();
		queue.pop();
		if (!nextLevelEvent->IsObsolete())
			level->push_back(nextLevelEvent);
	}
	return level;
}

void SkeletonBuilder::AddEventToGroup(std::shared_ptr<std::unordered_set<std::shared_ptr<Vertex>, Vertex::HashFunction>> parentGroup, std::shared_ptr<SkeletonEvent> event)
{
	
	if (typeid(*event) == typeid(SplitEvent)) //TODO: verify
	{
		auto splitEvent = std::dynamic_pointer_cast<SplitEvent>(event);
		parentGroup->insert(splitEvent->Parent);
	}		
	else if (typeid(*event) == typeid(EdgeEvent))//TODO: verify
	{
		auto edgeEvent = std::dynamic_pointer_cast<EdgeEvent>(event);
		parentGroup->insert(edgeEvent->PreviousVertex);
		parentGroup->insert(edgeEvent->NextVertex);
	}
}

std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>> SkeletonBuilder::GroupLevelEvents(std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>>& levelEvents)
{
	auto ret = std::make_shared<std::vector<std::shared_ptr<SkeletonEvent>>>();

	auto parentGroup = std::make_shared<std::unordered_set<std::shared_ptr<Vertex>, Vertex::HashFunction>>();

	while (levelEvents->size() > 0)
	{
		parentGroup->clear();

		auto event = levelEvents->at(0);
		levelEvents->erase(levelEvents->begin() + 0);
		auto eventCenter = event->V;
		auto distance = event->Distance;

		AddEventToGroup(parentGroup, event);

		auto cluster = std::make_shared<std::vector<std::shared_ptr<SkeletonEvent>>>(); //new List<SkeletonEvent>{ @event };
		cluster->push_back(event);

		for (size_t j = 0; j < levelEvents->size(); j++)
		{
			auto test = levelEvents->at(j);

			if (IsEventInGroup(parentGroup, test))
			{
				// Because of numerical errors split event and edge event
				// can appear in slight different point. Epsilon can be
				// apply to level but event point can move rapidly even for
				// little changes in level. If two events for the same level
				// share the same parent, they should be merge together.

				auto item = levelEvents->at(j);
				levelEvents->erase(levelEvents->begin() + j);
				cluster->push_back(item);
				AddEventToGroup(parentGroup, test);
				j--;
			}
			// is near
			else if (eventCenter->DistanceTo(*test->V) < SplitEpsilon)
			{
				// group all event when the result point are near each other
				auto item = levelEvents->at(j);
				levelEvents->erase(levelEvents->begin() + j);
				cluster->push_back(item);
				AddEventToGroup(parentGroup, test);
				j--;
			}
		}

		// More then one event share the same result point, we need to
		// create new level event.
		ret->push_back(CreateLevelEvent(eventCenter, distance, cluster));
	}
	return ret;
}

bool SkeletonBuilder::IsEventInGroup(std::shared_ptr<std::unordered_set<std::shared_ptr<Vertex>, Vertex::HashFunction>>& parentGroup, std::shared_ptr<SkeletonEvent>& event)
{
	if (typeid(*event) == typeid(SplitEvent))
	{
		auto splitEvent = std::dynamic_pointer_cast<SplitEvent>(event);
		return parentGroup->contains(splitEvent->Parent);
	}
	else if (typeid(*event) == typeid(EdgeEvent))
	{
		auto edgeEvent = std::dynamic_pointer_cast<EdgeEvent>(event);
		return parentGroup->contains(edgeEvent->PreviousVertex) || parentGroup->contains(edgeEvent->NextVertex);
	}
	return false;
}

std::shared_ptr<SkeletonEvent> SkeletonBuilder::CreateLevelEvent(std::shared_ptr<Vector2d> eventCenter, double distance, std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>>& eventCluster)
{
	auto chains = CreateChains(eventCluster);

	if (chains->size() == 1)
	{
		auto chain = chains->at(0);
		if (chain->ChainType == EChainType::CLOSED_EDGE)
			return std::make_shared<PickEvent>(eventCenter, distance, std::dynamic_pointer_cast<EdgeChain>(chain));
		if (chain->ChainType == EChainType::EDGE)
			return std::make_shared<MultiEdgeEvent>(eventCenter, distance, std::dynamic_pointer_cast<EdgeChain>(chain));
		if (chain->ChainType == EChainType::SPLIT)
			return std::make_shared<MultiSplitEvent>(eventCenter, distance, chains);
	}

	if (std::any_of(chains->begin(), chains->end(), [](const std::shared_ptr<IChain> chain) {return chain->ChainType == EChainType::CLOSED_EDGE; }))
		throw std::exception("Found closed chain of events for single point, but found more then one chain");
	return std::make_shared<MultiSplitEvent>(eventCenter, distance, chains);
}

std::shared_ptr<std::vector<std::shared_ptr<IChain>>> SkeletonBuilder::CreateChains(std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>>& cluster)
{
	auto edgeCluster = std::make_shared<std::vector<std::shared_ptr<EdgeEvent>>>(); //new List<EdgeEvent>();
	auto splitCluster = std::make_shared<std::vector<std::shared_ptr<SplitEvent>>>(); //new List<SplitEvent>();
	auto vertexEventsParents = std::make_shared<std::unordered_set<std::shared_ptr<Vertex>, Vertex::HashFunction>>();  //new HashSet<Vertex>();

	for(auto skeletonEvent : *cluster)
	{
		if (typeid(*skeletonEvent) == typeid(EdgeEvent)) //TODO: verify
		{
			auto e = std::dynamic_pointer_cast<EdgeEvent>(skeletonEvent);
			edgeCluster->push_back(e);
		}	
		else
		{
			if (typeid(*skeletonEvent) == typeid(VertexSplitEvent))
			{
				// It will be processed in next loop to find unique split
				// events for one parent.
			}
			else if (typeid(*skeletonEvent) == typeid(SplitEvent))
			{
				auto splitEvent = std::dynamic_pointer_cast<SplitEvent>(skeletonEvent);
				// If vertex and split event exist for the same parent
				// vertex and at the same level always prefer split.
				vertexEventsParents->insert(splitEvent->Parent);
				splitCluster->push_back(splitEvent);
			}
		}
	}

	for(auto skeletonEvent : *cluster)
	{
		if (typeid(*skeletonEvent) == typeid(VertexSplitEvent))
		{
			auto vertexEvent = std::dynamic_pointer_cast<VertexSplitEvent>(skeletonEvent);
			if (!vertexEventsParents->contains(vertexEvent->Parent))
			{
				// It can be created multiple vertex events for one parent.
				// Its is caused because two edges share one vertex and new
				//event will be added to both of them. When processing we
				// need always group them into one per vertex. Always prefer
				// split events over vertex events.
				vertexEventsParents->insert(vertexEvent->Parent);
				splitCluster->push_back(vertexEvent);
			}
		}
	}

	auto edgeChains = std::make_shared<std::vector<std::shared_ptr<EdgeChain>>>(); //new List<EdgeChain>();

	// We need to find all connected edge events, and create chains from
	// them. Two event are assumed as connected if next parent of one
	// event is equal to previous parent of second event.
	while (edgeCluster->size() > 0)
		edgeChains->push_back(std::make_shared<EdgeChain>(CreateEdgeChain(edgeCluster)));

	auto chains = std::make_shared<std::vector<std::shared_ptr<IChain>>>();  //new List<IChain>(edgeChains.Count);
	for(auto edgeChain : *edgeChains)		
		chains->push_back(edgeChain);

splitEventLoop:
	while (!splitCluster->empty())
	{
		auto split = splitCluster->at(0);
		splitCluster->erase(splitCluster->begin() + 0);

		for(auto chain : *edgeChains)
		{
			// check if chain is split type
			if (IsInEdgeChain(split, chain))
				goto splitEventLoop;
		}


		// split event is not part of any edge chain, it should be added as
		// new single element chain;
		chains->push_back(std::make_shared<SplitChain>(split));
	}

	// Return list of chains with type. Possible types are edge chain,
	// closed edge chain, split chain. Closed edge chain will produce pick
	//event. Always it can exist only one closed edge chain for point
	// cluster.
	return chains;
}

bool SkeletonBuilder::IsInEdgeChain(std::shared_ptr<SplitEvent> split, std::shared_ptr<EdgeChain> chain)
{
	auto splitParent = split->Parent;
	auto edgeList = chain->EdgeList;
	return std::any_of(edgeList->begin(), edgeList->end(), 
		[splitParent]
	(const std::shared_ptr<EdgeEvent> edgeEvent) 
		{ 
			return edgeEvent->PreviousVertex == splitParent || edgeEvent->NextVertex == splitParent; 
		});
}

std::shared_ptr<std::vector<std::shared_ptr<EdgeEvent>>> SkeletonBuilder::CreateEdgeChain(std::shared_ptr<std::vector<std::shared_ptr<EdgeEvent>>>& edgeCluster)
{
	auto edgeList = std::make_shared<std::vector<std::shared_ptr<EdgeEvent>>>();

	edgeList->push_back(edgeCluster->at(0));
	edgeCluster->erase(edgeCluster->begin() + 0);

	// find all successors of edge event
	// find all predecessors of edge event
	loop:
	for (;;)
	{
		auto beginVertex = edgeList->at(0)->PreviousVertex;
		auto endVertex = edgeList->at(edgeList->size() - 1)->NextVertex;

		for (size_t i = 0; i < edgeCluster->size(); i++)
		{
			auto edge = edgeCluster->at(i);
			if (edge->PreviousVertex == endVertex)
			{
				// edge should be added as last in chain
				edgeCluster->erase(edgeCluster->begin() + i);
				edgeList->push_back(edge);
				goto loop;
			}
			if (edge->NextVertex == beginVertex)
			{
				// edge should be added as first in chain
				edgeCluster->erase(edgeCluster->begin() + i);
				edgeList->insert(edgeList->begin(), edge);
				goto loop;
			}
		}
		break;
	}

	return edgeList;
}