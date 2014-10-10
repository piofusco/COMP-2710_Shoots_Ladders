COMP-2710ShootsLadders
========================

Simple shoots and ladders game written in C++. Reads in a map board from file and the game begins. Here is the description:

Goals:

• To develop a maze application that use graph representation

• To learn the use of pointers and dynamic memory allocations

• To learn about how to manipulate graph data structures

• To perform Object-Oriented Analysis, Design, and Testing

The graph abstraction is an important one since it is used in many different areas of computer sciences and software engineering. For instance, the Internet makes use of graphs representing the Internet router network configuration in order to determine the best route for forwarding packets from the source at one end of the Internet to the destination at the other end. Once a graph is constructed to represent the Internet configuration accurately, then the router executes an algorithm to determine the shortest path from each node to each destination and stores the information in its routing table.

In Lab 3, you will have fun constructing a similar graph to represent a pointer-based maze, with ladders and chutes, which can be used by the user to implement a simple game. You will analyze, design, implement and test the pointer-based maze game system. Once the graph is constructed by the game system, the user will try to traverse the maze from a starting point to a finish point, by selecting the direction to take at each node. Your program must follow the pointer to each node as the user traverse the graph. Since the maze configuration is hidden from the user, he/she will first randomly select each direction and learn and remember past dead-end routes and try to find the correct route to the finish point. When the user reaches the finish point, the program will print out the number of steps taken by the user and the all the nodes visited by the user in the correct sequence.

What is a graph?
A graph is consists of multiple nodes and edges. For instance, a graph can be represented by the figure below, where the circles represent the nodes and the lines represent the edges. An edge connects two nodes. In this lab assignment, we will only consider special graphs, where each node can have four normal edges, in the four directions: North, East, South and West. In addition, each node may also have at most one additional edge for either a ladder or chute that will link that node to another node that is not in the vicinity. An implementation detail to note here is that although the edge is represented by a single line, there are actually two links in both directions between the two nodes. For example, the line between A1 and B1 below is implemented by a link from A1 to B1 and another link from B1 to A1. The chute and ladder edges are only unidirectional.

See image called "GAMEBOARD" for picture.

What is the ladder and chute maze game system?
In the ladder and chute maze game, there is a maze of rooms and passages connecting the rooms. The maze of rooms and passages can be represented by a graph, such as the graph shown above. The nodes can be thought of as rooms and an edge represents a passage that connects one room to another. Each room can be connected normally to four rooms in the four directions: North, East, South and West, but may also be connected through secret passage ways to distant rooms, as represented by the graph above.
In this lab assignment, you will implement the maze above using references to instances of a Node class, which you will define. Each node in the graph will correspond to an instance of the Node class. The edges correspond to the links that connect one node to another and can be represented in Node as a pointer variable that points to another Node class object. Since there are four possible normal links, Node must contain four links (pointers) to other Node objects in the normal directions, but may have an additional link (pointer) to a distant node. Your Node class must be defined as follows (additional features may also be defined):

class Node {
public:
private:
Node(string newname);
Node();
void setNodeName(string newname);
string getNodeName();
void attachNewNode(Node *newNode, int direction);
Node *getAttachedNode(int direction);
void attachLadderChuteNode(Node *newNode);
Node *getLadderChuteNode();
string name;
Node *attachedNodes[4];
Node *ladderOrChuteNodes;
}

Your graph will consist of Node objects that are linked together through pointers. The member variable attachedNodes list will contain pointers to nodes in the four directions, for e.g. attachedNodes[0] will contain a pointer to the node in the North direction, attachedNodes[1] will contain a pointer to the node in the East direction and so forth. The member variable name will contain the name of the node, e.g. ‘A1’. You must implement the constructors Node(char newname) and Node(); and all the functions: setNodeName(char newname), getNodeName(), attachNewNode(Node *newNode, int direction), and getAttachedNode(int direction). In the beginning, you can create all the nodes statically using an array of Node objects. Alternatively, you can also create the nodes dynamically.

The Start variable is a pointer that points to the node where the user starts, which may represent room A1. The goal is to reach the finish which is the node that is referenced by the Finish variable which may reference the node representing the room H6.

Graph Configuration
The configuration of the graph that you will use in the program will be read in from a text file. Each line in the file indicates information on each node, i.e. the name of the node, the links that may exist from that node to another node in the North, East, South and West directions and another possible link for a ladder or chute. If there is no link in a specific direction, then there is an ‘*’ in place of the node name. For example, the first eight lines of the configuration file for the graph above is as follows:

A1 A2 B1 @ @ @

B1 @ @ @ A1 @ 

C1 C2 @ @ @ E3

D1 D2 @ @ @ @

@ E1 E2 F1 @ @

@ F1 @ @ @ E1 

@ @ G1 G2 @ @

@ H1 H2 @ @ @ 

In the first line of the configuration file above, the name of the node is A1. It has a pointer to node A2 in the North direction and a pointer to node B1 in the East direction but no link in either the South or West direction and no ladder or chute link. Thus the South, West, and Ladder/Chute pointers are set to NULL.

Your program will first read the graph configuration file and construct the graph data structures used for the maze game. Your program must run correctly with any graph configuration file. Several test configuration files will be released to you close to the deadline for you to test the correct execution of your program. All graph configuration files will have exactly 48 nodes, but their edges will be different.

The game will traverse the graph based on the inputs given by the user. When the user is at a current room, the program will display the allowable moves in the North, East, South or West directions. The user will then enter the desired direction. Your program must traverse to the next node by following the attachedNode pointer using the getAttachedNode() function. If a node that a user entered has a Chute or Ladder link (pointer), i.e. the ladderOrChuteNode pointer is not NULL, then the user will automatically and immediately be placed at the node that is pointed to by the ladderOrChuteNode pointer. While the program traverses the graph, it also counts the number of steps and keeps track of the nodes that it visited. Upon reaching the finish point, it will print out the congratulation banner and the number of steps taken.

The user interface must check for correct input value from the users. If there is any error, e.g. selecting an invalid direction, then the program must display the appropriate error message and continue to prompt for the correct input. Your program must not exit or terminate when there is an incorrect input value.

