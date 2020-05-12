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
//#include "Actor.h"
#include "Game.h"

using namespace std;

class Level
{
public:
    Level(Game* game);                      // Level Constructor
    ~Level();                               // Level Destructor
    
    void display();
    void set_char(int row, int col, char c);
    
    // accessors
    char arr_char(int row, int col);
    
private:
    char m_level[18][70];                           // level layout
    Game* m_game;                                   // pointer to game
    Player* m_player;                               // pointer to player
    vector<Actor*> m_actor;                         // pointer to monsters in level
    // each level will have its own monsters
    // each level will have its own scrolls/weapons/items
};

#endif // LEVEL_H
