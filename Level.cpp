//
//  Level.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "Actor.h"
#include "Level.h"

Level::Level(Game* game)        // Level Constructor
: m_game(game), m_player(m_game->player())
{
    // TO DO - can create if block --> if at this level make this many monsters, this many idols, this many stair cases
    m_staircase = new Staircase;
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
    
   
    // put staircase or idol randomly in level
    if (m_game->dungeon()->getCurrLevel() >= 0 && m_game->dungeon()->getCurrLevel() < 4) {
        while (m_level[m_staircase->getRow()][m_staircase->getCol()] == '#') {
            m_staircase->move(randInt(0, 17), randInt(0, 69));
        }
        m_level[m_staircase->getRow()][m_staircase->getCol()] = '>';
    }
    else if (m_game->dungeon()->getCurrLevel() == 4) {
        while (m_level[m_idol->getRow()][m_idol->getCol()] == '#') {
            m_staircase->move(randInt(0, 17), randInt(0, 69));
        }
        m_level[m_idol->getRow()][m_idol->getCol()] = '&';
    }
    
    // put player randomly in level
    while(m_level[m_player->getRowNum()][m_player->getColNum()] == '#' || (m_player->getRowNum() == m_staircase->getRow() && m_player->getColNum() == m_staircase->getCol())) {
        m_player->move(randInt(0, 17), randInt(0, 69));
    }
    
    // TO DO - loop through actor pointer vector and make sure monsters/actors placed not on a wall, other actors, weapons, scrolls, items, nor objects
}

// TO DO - implement Level Destructor
Level::~Level()                     // Level Destructor
{}

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
            
            // don't need if statement to print out staircase nor idol
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
