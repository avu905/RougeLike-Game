//
//  Dungeon.hpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#ifndef DUNGEON_H
#define DUNGEON_H

#include<iostream>

#include "Actor.h"
class Level;
class Game;
#include "utilities.h"

using namespace std;

class Dungeon
{
public:
    Dungeon(Game* game);        // Dungeon Constructor
    ~Dungeon();                 // Dungeon Destructor
        
    // non-accessors
    void display();             // display the level
    void newLevel();            // create a new level
    
    // accessors
    Level* level();             // access pointer to current level
    int getCurrLevel();         // access current level player is on
    
private:
    Level* level_ptr;           // pointer to current level
    Game* m_game;               // pointer to game
    int curr_level;             // current level player is on
};

#endif // DUNGEON_H
