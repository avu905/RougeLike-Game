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
//#include "globals.h" - if uncommented causes program to build but run forever
#include "Level.h"
#include "utilities.h"

#include<string>

using namespace std;

// ===============================================
// ============== ACTOR DECLARATION ==============
// ===============================================
class Actor
{
public:
    Actor(int row, int col, int hitpoints, string weapon, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game, char c);
    virtual ~Actor();

    virtual bool attemptMove(char c) = 0;
    virtual void move(int row, int col);
    
    // accessors
    Game* game();
    virtual int getRowNum();
    virtual int getColNum();
    virtual int getHitPoints();
    virtual int getArmor();
    virtual int getStrength();
    virtual int getDexterity();
    virtual char getChar();
    
private:
    int m_row;          // current row position in level
    int m_col;          // current col position in level
    int m_hitpoints;    // hit points
    string m_weapon;    // weapon - TO DO - change to weapon pointer
    int m_armorpoints;  // armor points
    int m_strpoints;    // strength points
    int m_dexpoints;    // dexterity points
    int m_sleeptime;    // sleep time
    char m_char;        // Actor represented by char
    
    Game* m_game;
};

// ================================================
// ============== PLAYER DECLARATION ==============
// ================================================

class Player : public Actor
{
public:
    Player(Game* game);
    ~Player();
    virtual bool attemptMove(char c);
private:
    // vector<GameObjects*> m_inventory (26) 
};

// ====================================================
// ============= MONSTER DECLARATION ==================
// ====================================================
class Monster : public Actor
{
public:
    Monster(int row, int col, int hitpoints, string weapon, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game, char c);
    virtual ~Monster();
    
private:
    // Weapon* m_weapon;
};

// ============== SNAKEWOMAN DECLARATION ==============
class SnakeWoman : public Monster
{
public:
    SnakeWoman(Game* game);
    ~SnakeWoman();
    virtual bool attemptMove(char c);
private:
};

#endif // ACTOR_H
