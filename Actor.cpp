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

void Actor::move(int row, int col)
{
    m_row = row;
    m_col = col;
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
int Actor::getArmor()
    {return m_armorpoints;}
int Actor::getStrength()
    {return m_strpoints;}
int Actor::getDexterity()
    {return m_dexpoints;}
char Actor::getChar()
    {return m_char;}


// =======================================================
// ============== MONSTER IMPLEMENTATION =================
// =======================================================
Monster::Monster(int row, int col, int hitpoints, string weapon, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game, char c)
: Actor(row, col, hitpoints, weapon, armorpoints, strpoints, dexpoints, sleeptime, game, c)
{}

Monster::~Monster()
{}

// =======================================================
// ============== SNAKEWOMAN IMPLEMENTATION ==============
// =======================================================
SnakeWoman::SnakeWoman(Game* game)
: Monster (randInt(0, 17), randInt(0, 69), SNAKEWOMAN_HIT_POINTS, SNAKEWOMAN_WEAPON, SNAKEWOMAN_ARMOR_POINTS, SNAKEWOMAN_STR_POINTS, SNAKEWOMAN_DEX_POINTS, SNAKEWOMAN_SLEEPTIME, game,'S')
{}

SnakeWoman::~SnakeWoman()
{}

bool SnakeWoman::attemptMove(char c)
{
    return true;
}

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





