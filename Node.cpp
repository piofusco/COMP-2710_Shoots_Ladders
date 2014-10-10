	// Program:		Lab 3
	// Name:		Michael Americo Pace
	// Class:		COMP 2710
	// Date: 		November 1, 2012
	// Email: 		map0009@auburn.edu
	//
	// Description:	This class represents a position on the board game. Each Node can point to 5 total other nodes.
	//				North, East, South, West and Chute/ladder can all be attached.
	// Compile instructions:   g++ Node.cpp -o lab2
	#include "Node.h"

	// Function:	Node constructor
	// Input:		string newname
	// Description:	Creates a node with name newname and sets all attached nodes to NULL.
	Node::Node(string newname)
	{
		name = newname;
		for(int i = 0 ; i < NUMBER_OF_NODES; i++)
		{
			attachedNodes[i] = NULL;
		}
		ladderOrChuteNodes = NULL;
	}

	// Function:		Node constructor
	// Description:		Parameterless constructor for node. Sets node name to "no name" and all attached nodes to NULL.
	Node::Node()
	{
		name = "no name";	
		for(int i = 0; i < NUMBER_OF_NODES; i++)
		{
			attachedNodes[i] = NULL;
		}
		ladderOrChuteNodes = NULL;
	}

	// Function:	setNodeName
	// Input:		string newname
	// Description:	Sets the name of node.
	void Node::setNodeName(string newname)
	{
		name = newname;
	}

	// Function:	getNodeName
	// Description:	Returns name of current node.
	string Node::getNodeName()
	{
		return name;
	}

	// Function:
	// Input:
	// Output:
	// Description:
	void Node::attachNewNode(Node *newNode, int direction)
	{
		attachedNodes[direction] = newNode;
	}

	// Function:	getAttachedNode
	// Input:		int direction
	// Description:	Returns pointer to int direction of current node.
	Node *Node::getAttachedNode(int direction)
	{
		return attachedNodes[direction];
	}

	// Function:	attachLadderChuteNode
	// Input:		Node *newNode
	// Description:	Attaches *newNode to ladderOrChuteNodes.
	void Node::attachLadderChuteNode(Node *newNode)
	{
		ladderOrChuteNodes = newNode;
	}

	// Function:	getLadderChuteNode
	// Description:	Returns a pointer to ladderOrChuteNodes.
	Node *Node::getLadderChuteNode()
	{
		return ladderOrChuteNodes;
	}

	// Function:	revealRoomOptions
	// Description:	Prints out valid directions connected to this node.
	void Node::revealRoomOptions()
	{
		int j = 0;
		cout << "You can go ";
		for(int i = 0; i < 4; i++)
		{
			if(attachedNodes[i] != NULL)
			{
				if(j > 0 && j < 4)
				{
				   cout << " or ";
				}
				if(i == NORTH)
				{
				   cout << "North";
				}
				else if(i == EAST)
				{
				   cout << "East";
				}
				else if(i == SOUTH)
				{
				   cout << "South";
				}
				else if(i == WEST)
				{
				   cout << "West";
				}
				j++;

			}
		}
		cout << ". ";
	}

	// Function:	isMoveValid
	// Input:		direction
	// Description:	Takes in char direction and determines if a node exists in that direction.
	bool Node::isMoveValid(char direction)
	{
		int index;
		switch(direction)
		{
			case 'N': 	index=NORTH;
						break;
			case 'E': 	index=EAST;
						break;
			case 'S':  	index=SOUTH;
						break;
			case 'W': 	index=WEST;
						break;
		}
		return attachedNodes[index]!=NULL;
	}

	// Function:	haveLadderChute
	// Output:		bool
	// Description:	Returns false if ladderOrChute is null. True otherwise.
	bool Node::haveLadderChute()
	{
		return ladderOrChuteNodes != NULL;
	}

	// Function:	toString
	// Description:	Prints out the name of the name and all its attached. Used for testing.
	void Node::toString()
	{
		cout << "I am node " << getNodeName() << "." << endl;
		cout << "I am attached to the following nodes:" << endl;
		for(int i = 0; i < 4; i++)
		{
			if(attachedNodes[i] == NULL)
			{
				cout << "NULL" << endl;
				continue;
			}
			cout << attachedNodes[i]->getNodeName() << endl;
		}
		if(haveLadderChute())
		{
			cout << "I have a ladder." << endl;
		}
		else
		{
			cout << "I don't have aladder." << endl;
		}
	}