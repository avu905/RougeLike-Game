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
    Game(int goblinSmellDistance);          // Game constructor
    ~Game();                                // Game destructor
    void play();
    
    // accessors
    Dungeon* dungeon();                     // access dungeon
    Player* player();                       // access player
private:
    Dungeon* m_dungeon;                     // pointer to dungeon
    Player* m_player;                       // pointer to player
};

#endif // GAME_INCLUDED

