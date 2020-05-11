//
//  Level.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "Level.h"

Level::Level(Game* game)        // Level Constructor
{
    m_game = game;
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            m_level[i][j] = ' ';
        }
    }
    
    // TO DO - delete hardcoded a wall
    for (int k = 3; k < 12; k++) {
        m_level[k][7] = '#';
    }
    
    m_level[m_game->player()->getRowNum()][m_game->player()->getColNum()] = '@';
}

Level::~Level()                     // Level Destructor
{}

void Level::display()
{
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            if (m_level[i][j] != '#')
                m_level[i][j] = ' ';
        }
    }
    
    m_level[m_game->player()->getRowNum()][m_game->player()->getColNum()] = '@';
    
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            cout << m_level[i][j];
        }
        cout << endl;
    }
}

char Level::arr_char(int row, int col)
{
    return m_level[row][col];
}
