#pragma once
#include <vector>
#include <unordered_set>
#include <queue>
#include <memory>
#include <algorithm>
#include <limits>
#include "Skeleton.h"
#include "Vertex.h"
#include "Edge.h"
#include "CircularList.h"
#include "MultiEdgeEvent.h"
#include "PickEvent.h"
#include "MultiSplitEvent.h"
#include "SplitEvent.h"
#include "FaceQueueUtil.h"
#include "PrimitiveUtils.h"
#include "VertexSplitEvent.h"
#include "SplitChain.h"
#include "EChainType.h"
#include "PickEvent.h"
#include "MultiEdgeEvent.h"
#include "MultiSplitEvent.h"
#include "LavUtil.h"
#include "SingleEdgeChain.h"
#include <map>
/// <summary> 
///     Straight skeleton algorithm implementation. Base on highly modified Petr
///     Felkel and Stepan Obdrzalek algorithm. 
/// </summary>
/// <remarks> 
///     This is a C++ adopted port of java implementation from kendzi-straight-skeleton library.
/// </remarks>
class SkeletonBuilder
{	
	
protected:
	/// <summary>
	///     Check if given point is on one of edge bisectors. If so this is vertex
	///     split event. This event need two opposite edges to process but second
	///     (next) edge can be take from edges list and it is next edge on list.
	/// </summary>
	/// <param name="point">Point of event.</param>
	/// <param name="edge">candidate for opposite edge.</param>
	/// <returns>previous opposite edge if it is vertex split event.</returns>
	static std::shared_ptr<Edge> VertexOpositeEdge(std::shared_ptr<Vector2d> point, std::shared_ptr<Edge> edge);
private:	
	// Error epsilon.
	static const double SplitEpsilon;
	class ChainComparer
	{
	private:
		Vector2d _center;

	public:
		ChainComparer(Vector2d center)
		{
			_center = center;
		}

		bool operator()(std::shared_ptr<IChain> x, std::shared_ptr<IChain> y)
		{
			if (x == y)
				return true; //0;

			auto angle1 = Angle(_center, *x->PreviousEdge->Begin);
			auto angle2 = Angle(_center, *y->PreviousEdge->Begin);

			return angle1 > angle2;
			//return angle1 > angle2 ? 1 : -1;
		}

		double Angle(Vector2d p0, Vector2d p1)
		{
			auto dx = p1.X - p0.X;
			auto dy = p1.Y - p0.Y;
			return atan2(dy, dx);
		}
	};
	struct SplitCandidate
	{
	private:
		using spe = std::shared_ptr<Edge>;
		using spv2d = std::shared_ptr<Vector2d>;
	public:
		double Distance;
		spe OppositeEdge;
		spv2d OppositePoint;
		spv2d Point;

		SplitCandidate(spv2d point, double distance, spe oppositeEdge, spv2d oppositePoint)
		{
			Point = point;
			Distance = distance;
			OppositeEdge = oppositeEdge;
			OppositePoint = oppositePoint;
		}
	};
	struct SkeletonEventDistanseComparer
	{
	public:
		bool operator()(SkeletonEvent& left, SkeletonEvent& right)
		{
			return left.Distance < right.Distance;
		}
	};
	struct SplitCandidateComparer
	{
	public:
		bool operator()(SplitCandidate& left, SplitCandidate& right)
		{
			return left.Distance < right.Distance;
		}
	};	
	using queueSkeletonEvent = std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>, std::vector<std::shared_ptr<SkeletonEvent>>, SkeletonBuilder::SkeletonEventDistanseComparer()>>;
	static std::shared_ptr<std::vector<Vector2d>> InitPolygon(std::vector<Vector2d>& polygon);
	static void ProcessTwoNodeLavs(std::shared_ptr<std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>> sLav);
	static void RemoveEmptyLav(std::shared_ptr<std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>> sLav);
	static void AddMultiBackFaces(std::shared_ptr<std::vector<std::shared_ptr<EdgeEvent>>> edgeList, std::shared_ptr<Vertex> edgeVertex);
	//Renamed due to conflict with class name
	static void EmitMultiEdgeEvent(std::shared_ptr<MultiEdgeEvent> event, std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>>> queue, std::shared_ptr<std::vector<std::shared_ptr<Edge>>> edges);
	//Renamed due to conflict with class name
	static void EmitPickEvent(std::shared_ptr<PickEvent> event);
	//Renamed due to conflict with class name
	static void EmitMultiSplitEvent(std::shared_ptr<MultiSplitEvent> event, std::shared_ptr<std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>> sLav, std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>>> queue, std::shared_ptr<std::vector<std::shared_ptr<Edge>>> edges);
	static void CorrectBisectorDirection(std::shared_ptr<LineParametric2d> bisector, std::shared_ptr<Vertex> beginNextVertex, std::shared_ptr<Vertex> endPreviousVertex, std::shared_ptr<Edge> beginEdge, std::shared_ptr<Edge> endEdge);
	static std::shared_ptr<FaceNode> AddSplitFaces(std::shared_ptr<FaceNode> lastFaceNode, std::shared_ptr<IChain> chainBegin, std::shared_ptr<IChain> chainEnd, std::shared_ptr<Vertex> newVertex);
	static std::shared_ptr<Vertex> CreateOppositeEdgeVertex(std::shared_ptr<Vertex> newVertex);
	static void CreateOppositeEdgeChains(std::shared_ptr<std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>> sLav, std::shared_ptr<std::vector<std::shared_ptr<IChain>>> chains, std::shared_ptr<Vector2d> center);
	static std::shared_ptr<Vertex> CreateMultiSplitVertex(std::shared_ptr<Edge> nextEdge, std::shared_ptr<Edge> previousEdge, std::shared_ptr<Vector2d> center, double distance);
	/// <summary>
	///     Create chains of events from cluster. Cluster is set of events which meet
	///     in the same result point. Try to connect all event which share the same
	///     vertex into chain. events in chain are sorted. If events don't share
	///     vertex, returned chains contains only one event.
	/// </summary>
	/// <param name="cluster">Set of event which meet in the same result point</param>
	/// <returns>chains of events</returns>
	static std::shared_ptr<std::vector<std::shared_ptr<IChain>>> CreateChains(std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>> cluster);
	static bool IsInEdgeChain(std::shared_ptr<SplitEvent> split, std::shared_ptr<EdgeChain> chain);
	static std::shared_ptr<std::vector<std::shared_ptr<EdgeEvent>>> CreateEdgeChain(std::shared_ptr<std::vector<std::shared_ptr<EdgeEvent>>> edgeCluster);
	static void RemoveEventsUnderHeight(std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>>> queue, double levelHeight);
	static std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>> LoadAndGroupLevelEvents(std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>>> queue);
	static std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>> GroupLevelEvents(std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>> levelEvents);
	static bool IsEventInGroup(std::shared_ptr<std::unordered_set<std::shared_ptr<Vertex>, Vertex::HashFunction>> parentGroup, std::shared_ptr<SkeletonEvent> event);
	static void AddEventToGroup(std::shared_ptr<std::unordered_set<std::shared_ptr<Vertex>, Vertex::HashFunction>> parentGroup, std::shared_ptr<SkeletonEvent> event);
	static std::shared_ptr<SkeletonEvent> CreateLevelEvent(std::shared_ptr<Vector2d> eventCenter, double distance, std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>> eventCluster);
	/// <summary> Loads all not obsolete event which are on one level. As level heigh is taken epsilon. </summary>
	static std::shared_ptr<std::vector<std::shared_ptr<SkeletonEvent>>> LoadLevelEvents(std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>>> queue);
	static int AssertMaxNumberOfInteraction(int& count);
	static std::shared_ptr<std::vector<std::vector<Vector2d>>> MakeClockwise(std::shared_ptr<std::vector<std::vector<Vector2d>>>& holes);
	static std::shared_ptr<std::vector<Vector2d>> MakeCounterClockwise(std::vector<Vector2d>& polygon);
	static void InitSlav(std::vector<Vector2d>& polygon, std::shared_ptr<std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>> sLav, std::shared_ptr<std::vector<std::shared_ptr<Edge>>> edges, std::shared_ptr<std::vector<std::shared_ptr<FaceQueue>>> faces);
	static Skeleton AddFacesToOutput(std::shared_ptr<std::vector<std::shared_ptr<FaceQueue>>> faces);
	static void InitEvents(std::shared_ptr<std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>> sLav, std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>>> queue, std::shared_ptr<std::vector<std::shared_ptr<Edge>>> edges);
	static void ComputeSplitEvents(std::shared_ptr<Vertex> vertex, std::shared_ptr<std::vector<std::shared_ptr<Edge>>> edges, std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>>> queue, double distanceSquared);
	static void ComputeEvents(std::shared_ptr<Vertex> vertex, std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>>> queue, std::shared_ptr<std::vector<std::shared_ptr<Edge>>> edges);
	/// <summary>
	///     Calculate two new edge events for given vertex. events are generated
	///     using current, previous and next vertex in current lav. When two edge
	///     events are generated distance from source is check. To queue is added
	///     only closer event or both if they have the same distance.
	/// </summary>
	static double ComputeCloserEdgeEvent(std::shared_ptr<Vertex> vertex, std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>>> queue);
	static std::shared_ptr<SkeletonEvent> CreateEdgeEvent(std::shared_ptr<Vector2d> point, std::shared_ptr<Vertex> previousVertex, std::shared_ptr<Vertex> nextVertex);
	static void ComputeEdgeEvents(std::shared_ptr<Vertex> previousVertex, std::shared_ptr<Vertex> nextVertex, std::shared_ptr<std::priority_queue<std::shared_ptr<SkeletonEvent>>> queue);
	static std::shared_ptr<std::vector<SplitCandidate>> CalcOppositeEdges(std::shared_ptr<Vertex> vertex, std::shared_ptr<std::vector<std::shared_ptr<Edge>>> edges);
	static bool EdgeBehindBisector(LineParametric2d bisector, LineLinear2d edge);
	static std::shared_ptr<SplitCandidate> CalcCandidatePointForSplit(std::shared_ptr<Vertex> vertex, std::shared_ptr<Edge> edge);
	static std::shared_ptr<Edge> ChoseLessParallelVertexEdge(std::shared_ptr<Vertex> vertex, std::shared_ptr<Edge> edge);
	static Vector2d ComputeIntersectionBisectors(std::shared_ptr<Vertex> vertexPrevious, std::shared_ptr<Vertex> vertexNext);
	static std::shared_ptr<Vertex> FindOppositeEdgeLav(std::shared_ptr<std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>> sLav, std::shared_ptr<Edge> oppositeEdge, std::shared_ptr<Vector2d>center);
	static std::shared_ptr<Vertex> ChooseOppositeEdgeLav(std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> edgeLavs, std::shared_ptr<Edge> oppositeEdge, std::shared_ptr<Vector2d> center);
	static std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> FindEdgeLavs(std::shared_ptr<std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction>> sLav, std::shared_ptr<Edge> oppositeEdge, std::shared_ptr<CircularList> skippedLav);
	
	/// <summary>
		///     Take next lav vertex _AFTER_ given edge, find vertex is always on RIGHT
		///     site of edge.
		/// </summary>
	static std::shared_ptr<Vertex> GetEdgeInLav(std::shared_ptr<CircularList> lav, std::shared_ptr<Edge> oppositeEdge);
	static void AddFaceBack(std::shared_ptr<Vertex> newVertex, std::shared_ptr<Vertex> va, std::shared_ptr<Vertex> vb);
	static void AddFaceRight(std::shared_ptr<Vertex> newVertex, std::shared_ptr<Vertex> vb);
	static void AddFaceLeft(std::shared_ptr<Vertex> newVertex, std::shared_ptr<Vertex> va);
	static double CalcDistance(Vector2d intersect, Edge currentEdge);
	static Vector2d CalcVectorBisector(Vector2d norm1, Vector2d norm2);
	static std::shared_ptr<LineParametric2d> CalcBisector(std::shared_ptr<Vector2d> p, Edge e1, Edge e2);
	template<typename T>
	size_t hash(const std::shared_ptr<T>& ptr)
	{
		return ((size_t)ptr.get()) / sizeof(T);
	}
	template<typename T>
	bool equal_to(const std::shared_ptr<T>& left, const std::shared_ptr<T>& right)
	{
		return left.get() == right.get();
	}

public:
	/// <summary> Creates straight skeleton for given polygon. </summary>
	static Skeleton Build(std::vector<Vector2d>& polygon);
	/// <summary> Creates straight skeleton for given polygon with holes. </summary>
	static Skeleton Build(std::vector<Vector2d>& polygon, std::shared_ptr<std::vector<std::vector<Vector2d>>>& holes);
};

