//
//  Level.hpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <vector>

class Actor;
class Monster;
#include "Game.h"
#include "InteractableObject.h"
#include "utilities.h"

using namespace std;

class Level
{
public:
    Level(Game* game, int curr_level);      // Level Constructor
    ~Level();                               // Level Destructor
    
    // accessors
    char getLevelChar(int row, int col) {return m_level[row][col];}
    InteractableObject* progressObj() {return m_progressionObject;}
    int numberOfMonstersOnlevel() {return m_monsters.size();}
    Monster* monsterAtIndex(int index) {return m_monsters[index];}
    
    // non-accessors
    void display();                                        // display the level
    bool validMove(int row, int col);                      // check if actor can move to that position
    Player* createPlayer();                                // create a new player and return a pointer to the player
    void freePosition(int &row, int &col);                 // set to free position on m_level
    bool pickUpObject(string& MessageToPrint);             // pick up idol, scroll, or weapon
    void addInteractableObject(int objectType);            // only used in level constructor - create/dynamically allocate a new weapon/scroll and place in the level
    void addMonster(int monsterType);
    void clearDeadMonsters();                              // clear dead monsters from level
    void monsterDropItem(Monster* monster);                // monster will drop an item - only called clearDearmonsters() after a monster dies
    bool isObjectAtSpot(Monster* monster);                 // checks if there is an object at a certain position
    void moveMonsters(char userInput, bool& message, string& messageToPrint);        // moves all monsters in level after player's turn
    int findPath(char levelCopy[][70], int startRow, int startCol, int endRow, int endCol, int pathLength, char dirEntered);    // recursive goblin function
    void makeRooms();                                      // make random rooms
    
    
private:
    char m_level[18][70];                           // level layout
    Game* m_game;                                   // pointer to game
    Player* m_player;                               // pointer to player
    
    int initialPlayerRow;                           // must make level before placing
    int initialPlayerCol;                           // must make level
    
    ProgressionObject* m_progressionObject;         // pointer to staircase or idol
    vector<InteractableObject*> m_objects;          // vector of pointers to weapons or scrolls) ONLY on level
    
    vector<Monster*> m_monsters;                    // vector of pointers to monsters on level
};

#endif // LEVEL_H
