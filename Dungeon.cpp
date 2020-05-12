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
    cout << "Dungeon Level: " << curr_level << ", Hit points: " << m_game->player()->getHitPoints() << ", Armor: " << m_game->player()->getArmor() << ", Strength: " << m_game->player()->getStrength() << ", Dexterity: " << m_game->player()->getDexterity() << endl;
}

Dungeon::~Dungeon()             // Dungeon Destructor
{}

void Dungeon::display()         // calls level's display & keeps track of current level
{
    // print level
    level_ptr[curr_level]->display();
    
    // print dungeon level and player stats
    cout << "Dungeon Level: " << curr_level << ", Hit points: " << m_game->player()->getHitPoints() << ", Armor: " << m_game->player()->getArmor() << ", Strength: " << m_game->player()->getStrength() << ", Dexterity: " << m_game->player()->getDexterity() << endl;
}

void Dungeon::newLevel()
{
    curr_level++;
    level_ptr[curr_level] = new Level(m_game);
    delete level_ptr[curr_level-1];
}

Level* Dungeon::level()
    {return level_ptr[curr_level];}

