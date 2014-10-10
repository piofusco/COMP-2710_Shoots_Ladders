// Program:		Lab 3
// Name:		Michael Americo Pace
// Class:		COMP 2710
// Date: 		November 1, 2012
// Email: 		map0009@auburn.edu
//
// Description:	Class definition of Node class.
#ifndef NODE_H
#define NODE_H

#define NORTH	0
#define EAST	1
#define SOUTH	2
#define WEST	3

#define NUMBER_OF_NODES 4

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

class Node 
{
	public:
	Node(string newname);
	Node();
	void setNodeName(string newname);
	string getNodeName();
	void attachNewNode(Node *newNode, int direction);
	Node *getAttachedNode(int direction);
	void attachLadderChuteNode(Node *newNode);
	Node *getLadderChuteNode();
	void revealRoomOptions();
	bool isMoveValid(char direction);
	bool haveLadderChute();
	void toString();
	private:
	string name;
	Node *attachedNodes[NUMBER_OF_NODES];
	Node *ladderOrChuteNodes;
};
#endif