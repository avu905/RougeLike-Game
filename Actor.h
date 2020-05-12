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
    Actor(int row, int col, int hitpoints, string weapon, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game, char c);
    virtual ~Actor();

    virtual bool attemptMove(char c) = 0;
    void move(int row, int col);
    
    // accessors
    Game* game();
    int getRowNum();
    int getColNum();
    int getHitPoints();
    int getArmor();
    int getStrength();
    int getDexterity();
    
private:
    int m_row;          // current row position in level
    int m_col;          // current col position in level
    int m_hitpoints;    // hit points
    string m_weapon;    // weapon
    int m_armorpoints;  // armor points
    int m_strpoints;    // strength points
    int m_dexpoints;    // dexterity points
    int m_sleeptime;    // sleep time
    char m_char;        // Actor represented by char
    
    Game* m_game;
};

// ============== PLAYER DECLARATION ==============

class Player : public Actor
{
public:
    Player(Game* game);
    ~Player();
    virtual bool attemptMove(char c);
private:
    // inventory
};

// ============== SNAKEWOMAN DECLARATION ==============
class SnakeWoman : public Actor
{
public:
    SnakeWoman(Game* game);
    ~SnakeWoman();
    virtual bool attemptMove(char c);
private:
};

#endif // ACTOR_H
