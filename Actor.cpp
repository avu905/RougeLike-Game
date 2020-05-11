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
Actor::Actor(int row, int col, int hitpoints, string weapon, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game)
{
    m_game = game;
}

Actor::~Actor()      // Actor Destructor
{}

int Actor::getRowNum()
    {return m_row;}

int Actor::getColNum()
    {return m_col;}

void Actor::move(int row, int col)
{
    m_row = row;
    m_col = col;
}

Game* Actor::game()
{
    return m_game;
}

// ===================================================
// ============== PLAYER IMPLEMENTATION ==============
// ===================================================
Player::Player(Game* game)
: Actor(randInt(0, 17), randInt(0, 69), 20, "short sword", 2, 2, 2, 0, game)
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

