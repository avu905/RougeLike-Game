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
    
    // TO DO - write algorithm to properly create level
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            m_level[i][j] = ' ';
        }
    }
    
    // TO DO - delete hardcoded wall perimeter
    for (int i = 0; i < 70; i++){
        m_level[0][i] = '#';
    }
    for (int i = 0; i < 70; i++){
        m_level[17][i] = '#';
    }
    
    for (int i = 1; i < 17; i++) {
        m_level[i][0] = '#';
        m_level[i][69] = '#';
    }
    for (int k = 3; k < 12; k++) {
        m_level[k][7] = '#';
    }
    
    m_level[m_game->player()->getRowNum()][m_game->player()->getColNum()] = '@';
}

Level::~Level()                     // Level Destructor
{}

void Level::display()
{
    // update characters in level
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            if (m_level[i][j] != '#')
                m_level[i][j] = ' ';
        }
    }
    
    // put player at new position in level
    m_level[m_game->player()->getRowNum()][m_game->player()->getColNum()] = '@';
    
    // draw level
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
