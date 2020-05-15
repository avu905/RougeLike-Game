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
    Actor(int row, int col, int hitpoints, string name, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game, char c, InteractableObject* object);
    virtual ~Actor();

    // non-accessors
    void decreaseSleep();
    virtual bool attemptMove(char c) = 0;
    virtual void move(char direction);
    virtual void holdInitialObject(InteractableObject* object);
    
    // accessors
    Game* game();
    virtual int getRowNum();
    virtual int getColNum();
    virtual int getHitPoints();
    virtual int getArmor();
    virtual int getStrength();
    virtual int getDexterity();
    virtual char getChar();
    virtual int getSleepTime();
    virtual string getName();
    
private:
    int m_row;          // current row position in level
    int m_col;          // current col position in level
    int m_hitpoints;    // hit points
    int m_maxHitpoints;
    string m_name;      // for action string
    int m_armorpoints;  // armor points
    int m_maxArmorpoints;
    int m_strpoints;    // strength points
    int m_maxStrpoints;
    int m_dexpoints;    // dexterity points
    int m_maxDexpoints;
    int m_sleeptime;    // sleep time
    int m_maxSleeptime;
    char m_char;        // actor represented by char
    Game* m_game;       // pointer to game
    
    InteractableObject* m_initialObject;       // pointer to weapon that each actor initially holds (only changes for player, not monster)
};

// ================================================
// ============== PLAYER DECLARATION ==============
// ================================================

class Player : public Actor
{
public:
    Player(Game* game, int initialRow, int initialCol);
    ~Player();
    virtual bool attemptMove(char c);
    int getInventorySize();
    void addObjectToInventory(InteractableObject* objectToAdd);
private:
    vector<InteractableObject*> m_inventory;
};

#endif // ACTOR_H
