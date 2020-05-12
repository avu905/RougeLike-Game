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
    curr_level = -1;
}

Dungeon::~Dungeon()             // Dungeon Destructor
{}

void Dungeon::display()         // calls level's display & keeps track of current level
{
    // print level
    level_ptr->display();
    
    // print dungeon level and player stats
    cout << "Dungeon Level: " << curr_level << ", Hit points: " << m_game->player()->getHitPoints() << ", Armor: " << m_game->player()->getArmor() << ", Strength: " << m_game->player()->getStrength() << ", Dexterity: " << m_game->player()->getDexterity() << endl;
}

void Dungeon::newLevel()
{
    if (curr_level != -1)
        delete level_ptr;
    
    curr_level++;
    level_ptr = new Level(m_game);
}

Level* Dungeon::level()
    {return level_ptr;}

int Dungeon::getCurrLevel()
    {return curr_level;}
