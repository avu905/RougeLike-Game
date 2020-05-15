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

//class Actor;
//#include "Actor.h"
class Monster;
#include "Game.h"
#include "InteractableObject.h"
#include "utilities.h"

using namespace std;

class Level
{
public:
    Level(Game* game);                      // Level Constructor
    ~Level();                               // Level Destructor
    
    // non-accessors
    void display();                                        // display the level
    bool validMove(int row, int col);                      // check if actor can move to that position
    Player* createPlayer();                                // create a new player and return a pointer to the player
    void freePosition(int &row, int &col);                 // set to free position on m_level
    bool pickUpObject(string& MessageToPrint);             // pick up idol, scroll, or weapon
    void addInteractableObject(int objectType);            // create/dynamically allocate a new interactable object (weapon/scroll) and place in the level
    
    // accessors
    char getLevelChar(int row, int col) {return m_level[row][col];}
    InteractableObject* progressObj() {return m_progressionObject;}
    
private:
    char m_level[18][70];                           // level layout
    Game* m_game;                                   // pointer to game
    Player* m_player;                               // pointer to player
    
    int initialPlayerRow;                           // must make level before placing
    int initialPlayerCol;                           // must make level
    
    ProgressionObject* m_progressionObject;         // pointer to staircase or idol
    vector<InteractableObject*> m_objects;          // vector of pointers to objects (weapons or scrolls) on level
    
    vector<Monster*> m_monsters;
    //int maxMonsters = randInt(2, 5*(m_game->dungeon()->getCurrLevel()+1)+1);
    // each level will have its own monsters
    // each level will have its own scrolls/weapons/items
};

#endif // LEVEL_H
