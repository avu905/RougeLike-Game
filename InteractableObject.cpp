//
//  InteractableObject.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/11/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "InteractableObject.h"


// ========== InteractableObject Implementation ==========
InteractableObject::InteractableObject()
{}

InteractableObject::InteractableObject(int row, int col)
{
    m_row = row;
    m_col = col;
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

// ========== Staircase Implementation ==========
Staircase::Staircase()
: InteractableObject(randInt(0, 17), randInt(0, 69))
{}

Staircase::~Staircase()
{}

// ========== Idol Implementation ==========
Idol::Idol()
: InteractableObject(randInt(0, 17), randInt(0, 69))
{}

Idol::~Idol()
{}

// ========== Weapon Implementation ==========
Weapon::Weapon()
{}

Weapon::~Weapon()
{}
