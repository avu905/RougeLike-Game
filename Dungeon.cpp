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
    
    if (curr_level == 0)
        level_ptr[curr_level]->display();
    
    else if (curr_level > 0 && curr_level < 4) {
        level_ptr[curr_level] = new Level(m_game);
        level_ptr[curr_level]->display();
        delete level_ptr[curr_level-1];
    }
    
    else if (curr_level == 4){
        // TO DO - last level does not print out
        level_ptr[curr_level]->display();
        delete level_ptr[curr_level-1];
    }
    
    cout << "Dungeon Level: " << curr_level << ", Hit points: " << m_game->player()->getHitPoints() << ", Armor: " << m_game->player()->getArmor() << ", Strength: " << m_game->player()->getStrength() << ", Dexterity: " << m_game->player()->getDexterity() << endl;
}

void Dungeon::incrementLevel()
{curr_level++;}

Level* Dungeon::level()
{return level_ptr[curr_level];}

