//
//  InteractableObject.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/11/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "Game.h"
#include "Dungeon.h"
#include "InteractableObject.h"

// ========================================================
// ========== INTERACTABLE OBJECT IMPLEMENTATION ==========
// ========================================================
InteractableObject::InteractableObject()                    // default constructor
{}

InteractableObject::InteractableObject(int row, int col, char symbol, Game* game)   // progression object constructor
: m_row(row), m_col(col), m_symbol(symbol), m_game(game)
{}

InteractableObject::~InteractableObject()
{}

int InteractableObject::getRow()
    {return m_row;}

int InteractableObject::getCol()
    {return m_col;}

char InteractableObject::getSymbol()
    {return m_symbol;}

// =======================================================
// ========== PROGRESSION OBJECT IMPLEMENTATION ==========
// =======================================================
ProgressionObject::ProgressionObject(int row, int col, char symbol, Game* game)
: InteractableObject(row, col, symbol, game)
{}

ProgressionObject::~ProgressionObject()
{}

Staircase::Staircase(int row, int col, char symbol, Game* game)
: ProgressionObject(row, col, symbol, game)
{}

Staircase::~Staircase()
{}

Idol::Idol(int row, int col, char symbol, Game* game)
: ProgressionObject(row, col, symbol, game)
{}

Idol::~Idol()
{}



