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

#include "Actor.h"
#include "Game.h"


using namespace std;

class Level
{
public:
    Level(Game* game);      // Level Constructor
    ~Level();               // Level Destructor
    
    void display();
    
    // accessors
    char arr_char(int row, int col);
    
private:
    char m_level[18][70]; // 18 rows x 70 columns
    Game* m_game;
    // each level will have its own monsters
    // each level will have its own stairs
    // each level will have its own scrolls/weapons/items
};

#endif // LEVEL_H
