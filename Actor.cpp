//
//  Actor.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "Actor.h"
#include "globals.h"


// ===================================================
// ============== ACTOR IMPLEMENTATION ===============
// ===================================================
Actor::Actor(int row, int col, int hitpoints, string name, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game, char c, InteractableObject* object)
{
    // Set initial values for actor
    m_row = row;
    m_col = col;
    m_hitpoints = hitpoints;
    m_name = name;
    m_armorpoints = armorpoints;
    m_strpoints = strpoints;
    m_dexpoints = dexpoints;
    m_sleeptime = sleeptime;
    m_game = game;
    m_char = c;
    
    m_maxHitpoints = 99;
    m_maxArmorpoints = 99;
    m_maxStrpoints = 99;
    m_maxDexpoints = 99;
    m_maxSleeptime = 0;
    
    m_initialObject = object; 
}

Actor::~Actor()      // Actor Destructor
{}

void Actor::move(char direction)
{
    if (direction == 'h' && this->game()->dungeon()->level()->validMove(m_row, m_col-1) == true) {    // move left
        m_col = m_col - 1;
    }
    if (direction == 'l' && this->game()->dungeon()->level()->validMove(m_row, m_col+1) == true) {    // move right
        m_col = m_col + 1;
    }
    if (direction == 'k' && this->game()->dungeon()->level()->validMove(m_row-1, m_col) == true) {    // move up
        m_row = m_row - 1;
    }
    if (direction == 'j' && this->game()->dungeon()->level()->validMove(m_row+1, m_col) == true) {    // move down
        m_row = m_row + 1;
    }
}

void Actor::decreaseSleep()
{m_sleeptime--;}

void Actor::holdInitialObject(InteractableObject* object)
{
    m_initialObject = object;
}


// accessors
Game* Actor::game()
    {return m_game;}
int Actor::getRowNum()
    {return m_row;}
int Actor::getColNum()
    {return m_col;}
int Actor::getHitPoints()
    {return m_hitpoints;}
string Actor::getName()
    {return m_name;}
int Actor::getArmor()
    {return m_armorpoints;}
int Actor::getStrength()
    {return m_strpoints;}
int Actor::getDexterity()
    {return m_dexpoints;}
char Actor::getChar()
    {return m_char;}
int Actor::getSleepTime()
{return m_sleeptime;}

// ===================================================
// ============== PLAYER IMPLEMENTATION ==============
// ===================================================
Player::Player(Game* game, int initialRow, int initialCol)
: Actor(initialRow, initialCol, 20, "Player", 2, 2, 2, 0, game, '@', nullptr)
{
    // short sword added to m_inventory at index [0]
    int initialWeaponRow = 0;       // placed on a wall so technically not on level so can't pick up initial weapon at (0,0)
    int initialWeaponCol = 0;       // placed on a wall so technically not on level so can't pick up initial weapon at (0,0)
    m_inventory.push_back(new Shortsword(initialWeaponRow, initialWeaponCol, ')', game, "short sword", "slashes", 0, 2));
    // player initial holds a short sword
    holdInitialObject(m_inventory[0]);
}

Player::~Player()
{}

bool Player::attemptMove(char c)
{
    // can't move in that direction
    if (c == 'h' && game()->dungeon()->level()->getLevelChar(getRowNum(), getColNum()-1) == '#')
        return false;
    if (c == 'l' && game()->dungeon()->level()->getLevelChar(getRowNum(), getColNum()+1) == '#')
        return false;
    if (c == 'j' && game()->dungeon()->level()->getLevelChar(getRowNum()+1, getColNum()) == '#')
        return false;
    if (c == 'k' && game()->dungeon()->level()->getLevelChar(getRowNum()-1, getColNum()) == '#')
        return false;
    return true;
}

int Player::getInventorySize()
    {return m_inventory.size();}

void Player::addObjectToInventory(InteractableObject* objectToAdd)
{
    m_inventory.push_back(objectToAdd);
}



