//
//  Level.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "Actor.h"
#include "InteractableObject.h"
#include "Level.h"

Level::Level(Game* game)        // Level Constructor
: m_game(game), m_player(m_game->player())
{
    // TO DO - if block "if at this level then make this many monsters, this many idols, this many staircases,etc"
                // or create a function saying if this is the current level, make this monster
    // TO DO - delete staircase, delete idol, delete snakewomen,
    // TO DO - many snakewoman, 1 dragon, 1 goblin, 1 bogeyman per level
    if (m_game->dungeon()->getCurrLevel() == 0) {
        m_staircase = new Staircase;
        // should have this many monster pointers
        // loop to fill m_actor vector with monsters
        int maxMonsters = randInt(2, 5*(m_game->dungeon()->getCurrLevel()+1)+1);
        for (int i = 0; i < maxMonsters; i++) {
            m_actor[i] = new SnakeWoman(game);
        }
    }
    if (m_game->dungeon()->getCurrLevel() == 1)
        m_staircase = new Staircase;
    if (m_game->dungeon()->getCurrLevel() == 2)
        m_staircase = new Staircase;
    if (m_game->dungeon()->getCurrLevel() == 3)
        m_staircase = new Staircase;
    if (m_game->dungeon()->getCurrLevel() == 4)
        m_idol = new Idol;
        
    // TO DO - write algorithm to properly create level with walls
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            m_level[i][j] = ' ';
        }
    }
    // TO DO - delete hardcoded wall perimeter
    for (int i = 0; i < 70; i++) {
        m_level[0][i] = '#';
    }
    for (int i = 0; i < 70; i++) {
        m_level[17][i] = '#';
    }
    
    for (int i = 1; i < 17; i++) {
        m_level[i][0] = '#';
        m_level[i][69] = '#';
    }
    for (int k = 3; k < 12; k++) {
        m_level[k][7] = '#';
    }
    
   
    // TO DO - move changing 2D level array into display function and out of constructor
    // put staircase or idol randomly in level
    if (m_game->dungeon()->getCurrLevel() >= 0 && m_game->dungeon()->getCurrLevel() < 4) {
        while (m_level[m_staircase->getRow()][m_staircase->getCol()] == '#') {
            m_staircase->move(randInt(0, 17), randInt(0, 69));
        }
        m_level[m_staircase->getRow()][m_staircase->getCol()] = '>';
    }
    else if (m_game->dungeon()->getCurrLevel() == 4) {
        while (m_level[m_idol->getRow()][m_idol->getCol()] == '#') {
            m_idol->move(randInt(0, 17), randInt(0, 69));
        }
        m_level[m_idol->getRow()][m_idol->getCol()] = '&';
    }
    
    // TO DO - on 4th level, can't put player onto idol
    // put player randomly in level
    while(m_level[m_player->getRowNum()][m_player->getColNum()] == '#' || (m_player->getRowNum() == m_staircase->getRow() && m_player->getColNum() == m_staircase->getCol())) {
        m_player->move(randInt(0, 17), randInt(0, 69));
    }
    
    // TO DO - loop through actor pointer vector and make sure monsters/actors placed not on a wall, other actors, weapons, scrolls, items, nor objects
    // randomly place monster into level - (1) wall (2) player (3) staircase (4) idol (5) another monster
    for (int i = 0; i < m_actor.size(); i++) {
        while(m_level[m_actor[i]->getRowNum()][m_actor[i]->getColNum()] == '#') {
            m_actor[i]->move(randInt(0, 17), randInt(0, 69));
        }
    }
}

// TO DO - implement Level Destructor
Level::~Level()                     // Level Destructor
{
    // TO DO - delete staircase and idol (done in level destructor)
}

void Level::display()
{
    // reassign values in 2D level array
    char temp[18][70];
    for (int i = 0; i < 18; i++){
        for (int j = 0; j < 70; j++){
            temp[i][j] = m_level[i][j];
        }
    }
    
    // print out 2D level array
    // TO DO - put in if statements to print out monsters and all items/objects/weapons, etc
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            if (i == m_player->getRowNum() && j == m_player->getColNum())
                temp[i][j] = '@';
            // if the row is snake's row and if the col is snake's col - TO DO finish this
            if (i == m_actor[i]->getRowNum() && j == m_actor[i]->getColNum())
                temp[i][j] = 'S';
            // don't need if statement to print out staircase nor idol - TO DO (fix and move changing to > or & into display function)
            cout << temp[i][j];
        }
        cout << endl;
    }
    
}

char Level::arr_char(int row, int col)
{
    return m_level[row][col];
    
}

void Level::set_char(int row, int col, char c)
{
    m_level[row][col] = c;
    
}
