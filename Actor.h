//
//  Actor.hpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <string>

#include "Dungeon.h"
#include "Game.h"
#include "Level.h"
#include "utilities.h"

#include<string>

using namespace std;

// ============== ACTOR DECLARATION ==============
class Actor
{
public:
    Actor(int row, int col, int hitpoints, string weapon, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game);
    virtual ~Actor();
    
    
    virtual bool attemptMove() = 0;
    void move(int row, int col);
    
    // accessors
    int getRowNum();
    int getColNum();
    Game* game();
    
private:
    int m_row;          // current row position in level
    int m_col;          // current col position in level
    int m_hitpoints;    // hit points
    string m_weapon;    // weapon
    int m_armorpoints;  // armor points
    int m_strpoints;    // strength points
    int m_dexpoints;    // dexterity points
    int m_sleeptime;    // sleep time
    
    Game* m_game;
};

// ============== PLAYER DECLARATION ==============

class Player : public Actor
{
public:
    Player(Game* game);
    ~Player();
    virtual bool attemptMove();
private:
    // inventory
};

#endif // ACTOR_H
