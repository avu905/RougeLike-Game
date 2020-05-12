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
        
    void display();
    void newLevel();
    
    // accessors
    Level* level();
    
private:
    Level* level_ptr[5];
    Game* m_game;
    int curr_level;
};

#endif // DUNGEON_H
