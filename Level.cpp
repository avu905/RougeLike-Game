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
    // populate level with monsters, idol, and staircase
    // TO DO - if block "if at this level then make this many monsters, this many idols, this many staircases,etc"
                // or create a function saying if this is the current level, make this monster
    // TO DO - delete snakewomen in level destructor (and delete other monsters)
    // TO DO - many snakewoman, 1 dragon, 1 goblin, 1 bogeyman per level
    if (m_game->dungeon()->getCurrLevel() == 0) {
        m_progressionObject = new Staircase;
        int maxMonsters = randInt(2, 5*(m_game->dungeon()->getCurrLevel()+1)+1);
        for (int i = 0; i < maxMonsters; i++) {
            m_monsters.push_back(new SnakeWoman(game));
        }
    }
    if (m_game->dungeon()->getCurrLevel() == 1)
        m_progressionObject = new Staircase;
    if (m_game->dungeon()->getCurrLevel() == 2)
        m_progressionObject = new Staircase;
    if (m_game->dungeon()->getCurrLevel() == 3)
        m_progressionObject = new Staircase;
    if (m_game->dungeon()->getCurrLevel() == 4)
        m_progressionObject = new Idol;
        
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
    while (m_level[m_progressionObject->getRow()][m_progressionObject->getCol()] == '#') {
        m_progressionObject->move(randInt(0, 17), randInt(0, 69));
    }
   //m_level[m_progressionObject->getRow()][m_progressionObject->getCol()] =
    if (m_game->dungeon()->getCurrLevel() != 4)
        m_level[m_progressionObject->getRow()][m_progressionObject->getCol()] = '>';
    else if (m_game->dungeon()->getCurrLevel() == 4)
        m_level[m_progressionObject->getRow()][m_progressionObject->getCol()] = '&';
    
    // put player randomly in level - not on a wall
    while(m_level[m_player->getRowNum()][m_player->getColNum()] == '#') {
        m_player->move(randInt(0, 17), randInt(0, 69));
    }
    
    // TO DO - randomly place monster in level
    // TO DO - not on a wall
    // TO DO - not on another actor
    for (int i = 0; i < m_monsters.size(); i++) {
        while(m_level[m_monsters[i]->getRowNum()][m_monsters[i]->getColNum()] == '#' || (m_monsters[i]->getRowNum() == m_player->getRowNum() && m_monsters[i]->getColNum() == m_player->getColNum())) {
            m_monsters[i]->move(randInt(0, 17), randInt(0, 69));
        }
    }
}

// TO DO - implement Level Destructor
Level::~Level()                     // Level Destructor
{
    delete m_progressionObject;
    for (int i = 0; i < m_monsters.size(); i++) {
        delete m_monsters[i];
    }
}

void Level::display()
{
    // reassign values into temporary 2D array
    char temp[18][70];
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++){
            temp[i][j] = m_level[i][j];
        }
    }
    
    // TO DO - put in loop to print out monsters
    // TO DO - put in loop to print out weapons
    // TO DO - put loop to print out scrolls
    
    // put monsters into 2D array
    for (int r = 0; r < 18; r++) {
        for (int c = 0; c < 70; c++) {
            for (int i = 0; i < m_monsters.size(); i++) {
                if (r == m_monsters[i]->getRowNum() && c == m_monsters[i]->getColNum())
                    temp[r][c] = m_monsters[i]->getChar();
            }
        }
    }
    // put player into 2D arry and print
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            if (i == m_player->getRowNum() && j == m_player->getColNum())
                temp[i][j] = m_player->getChar();
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
