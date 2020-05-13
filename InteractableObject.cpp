//
//  InteractableObject.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/11/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "InteractableObject.h"

// ========================================================
// ========== INTERACTABLE OBJECT IMPLEMENTATION ==========
// ========================================================
//InteractableObject::InteractableObject()
//{}

InteractableObject::InteractableObject(int row, int col, char c)
{
    m_row = row;
    m_col = col;
    m_symbol = c;
}

InteractableObject::~InteractableObject()
{}

void InteractableObject::move(int row, int col)
{
    m_row = row;
    m_col = col;
}

int InteractableObject::getRow()
    {return m_row;}

int InteractableObject::getCol()
    {return m_col;}

char InteractableObject::getSymbol()
    {return m_symbol;}

// =======================================================
// ========== PROGRESSION OBJECT IMPLEMENTATION ==========
// =======================================================
ProgressionObject::ProgressionObject(char c)
: InteractableObject(randInt(0, 17), randInt(0, 69), c)
{}

ProgressionObject::~ProgressionObject()
{}


// ========== STAIRCASE IMPLEMENTATION ==========
Staircase::Staircase()
: ProgressionObject('>')
{}

Staircase::~Staircase()
{}

// ========== IDOL IMPLEMENTATION ==========
Idol::Idol()
: ProgressionObject('&')
{}

Idol::~Idol()
{}
