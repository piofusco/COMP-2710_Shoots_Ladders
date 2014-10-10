// Program:		Aubiebook
// Name:		Michael Americo Pace
// Class:		COMP 2710
// Date: 		November 1, 2012
// Email: 		map0009@auburn.edu
//
// Description:	Class definition of the Game class.
#ifndef     GAME_H   
#define     GAME_H
#include "Node.h"
#include <string.h>
#include <vector>

#define NUMBER_ROWS_PER_COL 6
#define MAX_COORDINATES 48
class Game	
{
    public:
    Game();
    void run();
    void displayRoomInfo(Node* currentRoom);
    void move(char newMove);
    void printPath();
    bool atFinish(Node* currentRoom);
    void readFile(string fileName);
    bool isFileValid(string map_file);
    void getPointers(string lineOfText);
    void generateGraph(string pointerNodes[]);
    bool isValidChoice(char choice);
    void initializeCoordinates();
    void initializeValidChoices();
    Node *Start;                                // "head" pointer of beginning of path
    Node *Finish;                               // "tail" pointer of end of path
    Node *currentRoom;                          // Points at the current room you are in
    Node *coordinates[MAX_COORDINATES];			// Holds every possible coordinate of graph
    vector<char> validChoices;		            // vector of valid users entries for the menu
    vector<string> moves;                       // vector of name of positions user has visited
    int numberOfMoves;                          // counter for total number of moves
};
#endif