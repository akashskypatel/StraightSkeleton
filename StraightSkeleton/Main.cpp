// StraightSkeleton.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <memory>
#include <unordered_set>
#include "CircularList.h"
#include "Edge.h"
#include "LineLinear2d.h"
#include "leaker.h"
//#include <vector>
//#include "LinkedList.h"

int main()
{	
	/*
	std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction> lav;

	std::shared_ptr<CircularList> list1 = std::make_shared<CircularList>();
	list1->AddLast(Edge(Vector2d(2.48, 1.38), Vector2d(2.68, 4.90)));
	list1->AddLast(Edge(Vector2d(3.61, 2.16), Vector2d(5.54, 9.43)));

	lav.insert(list1);

	std::cout << lav.size() << "\n";
	*/
	
	CircularList list;
	list.AddLast(Edge(Vector2d(2.48, 1.38), Vector2d(2.68, 4.90)));
	list.AddLast(Edge(Vector2d(3.61, 2.16), Vector2d(5.54, 9.43)));
	for (auto node : list)
	{
		std::cout << node->ToString() << "\n";
	}
	/*
	CircularList list;
	list.AddLast(Edge(Vector2d(2.48, 1.38), Vector2d(2.68, 4.90)));

	for (CircularNode* node : list)
	{
		std::cout << node->ToString() << "\n";
	}
	*/

	/*
	list.AddLast(e1);
	
	
	CircularList<Edge> list;
	list.AddLast(Edge(Vector2d(2.48, 1.38), Vector2d(2.68, 4.90)));
	Edge e1 = Edge(Vector2d(2, 1), Vector2d(2, 4));
	list.AddLast(e1);
	Edge* e2 = new Edge(Vector2d(10.25, 15.45), Vector2d(8, 2.65));
	list.AddLast(*e2);
	delete e2;
	for (auto node : list)
	{
		std::cout << node.Data.ToString() << "\n";
	}
	*/
	/*
	std::vector<Edge> list;
	list.push_back(Edge(Vector2d(2.48, 1.38), Vector2d(2.68, 4.90)));
	
	
	
	LinkedList<Edge> list;
	list.AddTail(Edge(Vector2d(2.48, 1.38), Vector2d(2.68, 4.90)));
	*/
}
