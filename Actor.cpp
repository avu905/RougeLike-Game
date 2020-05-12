//
//  Actor.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "Actor.h"

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

void Actor::move(int row, int col)
{
    m_row = row;
    m_col = col;
}

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

// ===================================================
// ============== PLAYER IMPLEMENTATION ==============
// ===================================================
Player::Player(Game* game)
: Actor(randInt(0, 17), randInt(0, 69), 20, "short sword", 2, 2, 2, 0, game, '@')
{}

Player::~Player()
{}

bool Player::attemptMove(char c)
{
    // can't move in that direction
    if (c == 'h' && game()->dungeon()->level()->arr_char(getRowNum(), getColNum()-1) == '#')
        return false;
    if (c == 'l' && game()->dungeon()->level()->arr_char(getRowNum(), getColNum()+1) == '#')
        return false;
    if (c == 'j' && game()->dungeon()->level()->arr_char(getRowNum()+1, getColNum()) == '#')
        return false;
    if (c == 'k' && game()->dungeon()->level()->arr_char(getRowNum()-1, getColNum()) == '#')
        return false;
    return true;
}

// =======================================================
// ============== SNAKEWOMAN IMPLEMENTATION ==============
// =======================================================
SnakeWoman::SnakeWoman(Game* game)
: Actor(randInt(0, 17), randInt(0, 69), randInt(3, 6), "magic fangs of sleep", 3, 2, 3, 0, game, 'S')
{}

SnakeWoman::~SnakeWoman()
{}

bool SnakeWoman::attemptMove(char c)
{
    return true;
}



