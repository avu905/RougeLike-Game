//
//  Game.h
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.

#include <iostream>
#include <vector>
#include <string>

class Player;
class Dungeon;
#include "utilities.h"

using namespace std;

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
    
    // accessors
    Dungeon* dungeon();
    Player* player();
private:
    Dungeon* m_dungeon;
    Player* m_player;
};

#endif // GAME_INCLUDED

