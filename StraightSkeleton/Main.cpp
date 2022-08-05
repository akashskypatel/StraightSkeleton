// StraightSkeleton.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <unordered_set>
#include "SkeletonBuilder.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>


int main()
{	
	auto polygon = std::make_shared<std::vector<Vector2d>>();
	polygon->push_back(Vector2d(50, 50));
	polygon->push_back(Vector2d(150, 50));
	polygon->push_back(Vector2d(150, 100));
	polygon->push_back(Vector2d(50, 100));

	//auto expected = new List<Vector2d>{ new Vector2d(75.000000, 75.000000) };
	//expected.AddRange(polygon);

	for (auto p : *polygon)
	{
		std::cout << p.ToString() << "\n";
	}

	auto sk = SkeletonBuilder::Build(*polygon);
	std::cout << sk.Edges->size() << "\n";
	for (auto e : *sk.Distances)
	{
		std::cout << e.first.ToString() << "\n";
	}
	//_CrtDumpMemoryLeaks();
}
/*

class Test
{

public:
	Vector2d vec;
	/*
	Test(Vector2d v)
	{
		vec = v;
	}
	
};

void print(Test t)
{
	std::cout << t.vec.ToString() << "\n";
}

Test maketest(Vector2d v)
{
	return Test{ v };
}
Test t = maketest(Vector2d(2.48, 1.38));
print(t);

std::vector<Test> l;
l.push_back(t);

/*
std::unordered_set<std::shared_ptr<CircularList>, CircularList::HashFunction> lav;

std::shared_ptr<CircularList> list1 = std::make_shared<CircularList>();
list1->AddLast(Edge(Vector2d(2.48, 1.38), Vector2d(2.68, 4.90)));
list1->AddLast(Edge(Vector2d(3.61, 2.16), Vector2d(5.54, 9.43)));

lav.insert(list1);

std::cout << lav.size() << "\n";


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