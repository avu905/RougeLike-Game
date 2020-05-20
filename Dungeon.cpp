//
//  Dungeon.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "Dungeon.h"

#include "Level.h"

Dungeon::Dungeon(Game* game)    // Dungeon Constructor
{
    m_game = game;
    curr_level = 0;
    level_ptr = new Level(game, curr_level);
}

Dungeon::~Dungeon()             // Dungeon Destructor
{
    delete level_ptr;
}

void Dungeon::display()         // calls level's display & keeps track of current level
{
    level_ptr->display();
}

void Dungeon::newLevel()
{
    curr_level++;
    delete level_ptr;
    level_ptr = new Level(m_game, curr_level);
}

Level* Dungeon::level()
    {return level_ptr;}

int Dungeon::getCurrLevel()
    {return curr_level;}
