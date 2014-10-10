// Program:    Lab 3
// Name:       Michael Americo Pace
// Class:      COMP 2710
// Date:       November 1, 2012
// Email:      map0009@auburn.edu
//
// Description: This class reads the graph configuration file and generates the graph from user input. 
//              Handles all user input to move user from position to position until they are at the final
//              position. Will print out all moves made and the total number of moves.
// Compile instructions:   g++ Game.cpp -o lab3
#include "Game.h"

    // Function:    Game constructor
    // Description: 
    Game::Game()
    {
        initializeValidChoices();
        initializeCoordinates();
        numberOfMoves = 0;
        run();
    }

    // Function:    run
    // Description: Driver function for chute and ladder game.
    void Game::run()
    {
        string file;
        cout << "Greetings. Please enter the file: ";
        cin >> file;
        // Get file from user and determine if it exists
        while(!isFileValid(file))
        {
            cout << "This file doesn't exist. Please try again." << endl;
            cout << "Please enter the file: ";
            cin >> file;
        }
        // Read file and generate map
        readFile(file);
        // Sets a pointer to the first position on the graph
        currentRoom = Start;
        cout << "\t-----------------------------------------------------" << endl;
        cout << "                           Chutes and Ladders" << endl;
        cout << "\t-----------------------------------------------------" << endl;
        // Will run this loop until user is at the final room
        while(!atFinish(currentRoom))
        {
            displayRoomInfo(currentRoom);
            if(currentRoom->haveLadderChute())
            {
                cout << "BUT WAIT...there is a ladder! You take it to room ";
                cout << currentRoom->getLadderChuteNode()->getNodeName() << ". ";
                currentRoom = currentRoom->getLadderChuteNode();
                cout << endl;
                continue;
            }
            moves.push_back(currentRoom->getNodeName());
            cout << "What is your choice? ";
            string choice;
            cin >> choice;

            if(choice.length() > 1)
            {
                cout << "Please enter if N, E, S or W." << endl;
                continue;
            }
            else
            {
                char option = choice.at(0);
                if(isValidChoice(option) && currentRoom->isMoveValid(option))
                {
                    move(option);
                    numberOfMoves++;
                }
                else
                {
                    cout << "Please enter only valid room options." << endl;
                }
                cout << endl;
                continue;
            }
        }
        cout << "Congratulations! You have reached the finish point." << endl;
        cout << "You took " << numberOfMoves << " steps." << endl;
        cout << "The nodes you visited are: ";
        printPath();
        return;
    }

    // Function:    displayRoomInfo
    // Input:       Node* currentNode
    // Description: Displays the current room and the directions the user can go.
    void Game::displayRoomInfo(Node* currentNode)
    {
        cout << "You are currently in room " << currentNode->getNodeName() << ". ";
        currentNode->revealRoomOptions();
    }

    // Function:    move
    // Input:       char newMove
    // Description: Moves currentRoom from char newMove.
    void Game::move(char newMove)
    {
        switch(newMove)
        {
            case 'N': currentRoom = currentRoom->getAttachedNode(NORTH);
            break;
            case 'E': currentRoom = currentRoom->getAttachedNode(EAST);
            break;
            case 'S': currentRoom = currentRoom->getAttachedNode(SOUTH);
            break;
            case 'W': currentRoom = currentRoom->getAttachedNode(WEST);
            break;
        }
    }

    // Function:    printPath
    // Description: Prints all the moves made by the user once they complete the maze.
    void Game::printPath()
    {
        vector<string>::iterator moves_iter;
        for(moves_iter = moves.begin(); moves_iter != moves.end(); moves_iter++)
        {
            cout << " " << *moves_iter;
        }
        cout << "." << endl;
    }

    // Function:        atFinish
    // Input:           currentNode
    // Output:          bool
    // Description:     Determines whether currentNode points to node H6. Returns true if it does, false otherwise.
    bool Game::atFinish(Node* currentNode)
    {
        return currentNode == Finish;
    }

    // Function:    isFileValid
    // Input:       string map_file
    // Output:      bool
    // Description: Checks if file map_file exists. Returns true if it does, false otherwise.
    bool Game::isFileValid(string map_file)
    {
        ifstream fileIn;
        fileIn.open(map_file.c_str());
        if(fileIn.is_open() == false)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    // Function:       readFile
    // Input:          string fileName
    // Output:         If file is valid will read "File exists.. begin iteration." Otherwise will read "This file doesn't exist. Please try again."
    // Description:    Takes string fileName and attempts to open this file. Once file is open, will begin generating maze line by line.
    void Game::readFile(string fileName)
    {
        ifstream fileIn;
        fileIn.open(fileName.c_str());
        string line = "";
        // int number = 1;
        cout << "File exists.. begin iteration." << endl;
        while(!fileIn.eof())
        {
            getline(fileIn, line, '\n');
            getPointers(line);
            // number++;
            // cout << "Finished line number: " << number << endl;
        }
        cout << "End iteration." << endl;
    }

    // Function:        getPointers
    // Input:           string lineOfText
    // Description:     Takes a string of coordinates and puts them in an array of strings.
    void Game::getPointers(string lineOfText)
    {
        string pointers[6] = {"", "", "", "", "", ""};
        // Get the node this information concerns
        pointers[0] = lineOfText.substr(0,2);
        // cout << "Before: " << lineOfText.length() << endl;
        if (lineOfText.at(lineOfText.length()-1)=='\r')
        {
            lineOfText.erase(lineOfText.length()-1);
        }
        // cout << "After: " << lineOfText.length() << endl;
        int index = 1;
        for(int k = 1; k < lineOfText.length(); k++)
        {
            // cout << "index is: " << index << endl;
            int space1 = lineOfText.find_first_of(' ', k);
            int space2 = lineOfText.find(' ', space1+1);
            // cout << "space1: " << space1 << endl;
            // cout << "space2: " << space2 << endl;
            // When you are at the last pair of spaces space2 must be the length of string
            if(space2 == -1)
            {
                // cout << "space2 not found. Set to length." << endl;
                space2 = lineOfText.length();
                // cout << "space2: " << space2 << endl;
            }
            // If the distance between two spaces is 2, you have a *
            if(space2 - space1 == 2)
            {
                // cout << "Found an *" << endl;
                pointers[index] = "*";
                // cout << "NULL coordinate set." << endl;
            }
            // Otherwise, you have a coordinate
            else if(space2 - space1 > 2)
            {
                // cout << "Found a coordinate: ";
                pointers[index] = lineOfText.substr(space1+1, 2);
                // cout << pointers[index] << endl;
                // cout << "Coordinate set." << endl;
            }
            // Push iterator to index behind second space
            k = space2 - 1;
            // If you have reached the last space
            if(space2 == lineOfText.length()-1 || index == 6)
            {
                break;
            }
            index++;
        }
        // cout << "You found these from the line." << endl;
        // for(int i = 0; i < 6; i++)
        // {
        //     cout << i << ": ";
        //     cout << pointers[i] << endl;
        // }
        // cout << "Ending getPointers..." << endl;
        generateGraph(pointers);
    }

    // Function:        generateGraph
    // Input:           string pointerNodes[]
    // Description:     Takes each line from graph file and establishes all pointers on the board of the game.
    void Game::generateGraph(string pointerNodes[])
    {
        // cout << "generateGraph..."<<endl;
        // cout << pointerNodes[0] << endl;
        char nodeName[3];
        int index, node;
        strcpy(nodeName,(pointerNodes[0]).c_str());
        node = ((int)(nodeName[0])-65)*NUMBER_ROWS_PER_COL+(int)(nodeName[1])-49;   
        for( int i = 1; i < 5; i++)
        {
            if( pointerNodes[i] != "*" )
            {       
                // cout << "Not null."<<endl;
                strcpy(nodeName,(pointerNodes[i]).c_str());
                index = ((int)(nodeName[0])-65)*NUMBER_ROWS_PER_COL+(int)(nodeName[1])-49;
                coordinates[node]->attachNewNode(coordinates[index],i-1);
                // cout << "Attaching " << coordinates[index]->getNodeName() << endl;
            }
            else
            {
                // cout << "Attaching NULL"<<endl;
                coordinates[node]->attachNewNode(NULL,i-1); 
            }
        } 
        if( pointerNodes[5] != "*" )
        {      
            // cout <<"Not null"<<endl;
            strcpy(nodeName,(pointerNodes[5]).c_str());
            index = ((int)(nodeName[0])-65)*NUMBER_ROWS_PER_COL+(int)(nodeName[1])-49;
            coordinates[node]->attachLadderChuteNode(coordinates[index]);
            // cout << "Attaching " << coordinates[index]->getNodeName() << " as a ladder."<<endl;
        }
        else
        {
            // cout << "Attaching NULL ladder." << endl;
            // cout << pointerNodes[5] << endl;
            coordinates[node]->attachLadderChuteNode(NULL); 
        }
        // coordinates[node]->toString();
        return;
    }

    // Function:       isValidChoice
    // Input:          int choice
    // Output:         bool
    // Description:    Determines if int choice is a valid option. If valid returns true, false otherwise.
    bool Game::isValidChoice(char choice)
    {
        for(int i = 0; i < 4; i++)
        {
            if(validChoices[i] == choice)
            {
                return true;
            }
        }
        return false;
    }

    // Function:    initializeCoordinates
    // Description: Creates and adds all Nodes to array of Nodes coordinates[]
    void Game::initializeCoordinates()
    {
        char letter = 'A';
        int i = 1;
        for(int index = 0; index < MAX_COORDINATES; index++)
        {
            string nodeName = "";
            stringstream ss;
            stringstream ss1;
            ss << letter;
            nodeName += ss.str();
            ss1 << i;
            nodeName += ss1.str();
            Node* tempNode = new Node(nodeName);
            coordinates[index] = tempNode;
            i++;
            if(i == 7)
            {
                i = 1;
                letter++;
            }
        }
        Start = coordinates[0];
        Finish = coordinates[47];
    }

    // Function:      initializeValidChoices
    // Description:   Adds valid char choices to vector validChoices. These char's are the only valid option choices for the menu.
    void Game::initializeValidChoices() 
    {
      validChoices.push_back('N');
      validChoices.push_back('E');
      validChoices.push_back('S');
      validChoices.push_back('W');
    }