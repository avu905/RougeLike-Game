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
Actor::Actor(int row, int col, int hitpoints, string weapon, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game, char c)
{
    // Set initial values for actor
    m_row = row;
    m_col = col;
    m_hitpoints = hitpoints;
    m_weapon = weapon;
    m_armorpoints = armorpoints;
    m_strpoints = strpoints;
    m_dexpoints = dexpoints;
    m_sleeptime = sleeptime;
    m_game = game;
    m_char = c;
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


// accessors
Game* Actor::game()
    {return m_game;}
int Actor::getRowNum()
    {return m_row;}
int Actor::getColNum()
    {return m_col;}
int Actor::getHitPoints()
    {return m_hitpoints;}
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
: Actor(initialRow, initialCol, 20, "short sword", 2, 2, 2, 0, game, '@')
{}

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





