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
    level_ptr[0] = new Level(game);
    level_ptr[0]->display();
}

Dungeon::~Dungeon()             // Dungeon Destructor
{}

void Dungeon::display()         // calls level's display & keeps track of current level
{
    // TO DO - print current dungeon level, player's stats
    level_ptr[curr_level]->display();
}

Level* Dungeon::level()
{
    return level_ptr[curr_level];
}

