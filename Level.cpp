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
    // TO DO - write algorithm to populate levels with random walls and rooms
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            m_level[i][j] = ' ';
        }
    }
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
    
    // TO DO - put weapon and scroll objects in level
    // TO DO - put monsters in level
    
    // TO DO - put idol or staircase in level
    int progressionObjectRow = randInt(0, 17);
    int progressionObjectCol = randInt(0, 69);
    freePosition(progressionObjectRow, progressionObjectCol);
    if (m_game->dungeon()->getCurrLevel() != 4)
        m_progressionObject = new Staircase(progressionObjectRow, progressionObjectCol, '>', m_game);
    else if (m_game->dungeon()->getCurrLevel() == 4)
        m_progressionObject = new Idol(progressionObjectRow, progressionObjectCol, '&', m_game);
    
    // must create level before player so during construction of level, must know where to place player into level before creating player at that position
    initialPlayerRow = randInt(0, 17);
    initialPlayerCol = randInt(0, 69);
}

// TO DO - implement Level Destructor
Level::~Level()                     // Level Destructor
{
    // TO DO (1) - finish implementing level destructor (especially for monster vector and weapons and scrolls)
    // TO DO (1) - delete progression object, monsters, weapons, scrolls
    delete m_progressionObject;
}

void Level::display()
{
    // populate m_level with only walls and blank spaces
    // TO DO (1) - populate m_level with only walls and interactable objects (not including staircases and golden idol)
    for (int row = 0; row < 18; row++) {
        for (int col = 0; col < 70; col++) {
            if (m_level[row][col] != '#')
                m_level[row][col] = ' ';
        }
    }
    
    // TO DO (1) - put objects into m_level
    
    // put progression object onto level
    if (m_game->dungeon()->getCurrLevel() != 4)
        m_level[m_progressionObject->getRow()][m_progressionObject->getCol()] = '>';
    else if (m_game->dungeon()->getCurrLevel() == 4)
        m_level[m_progressionObject->getRow()][m_progressionObject->getCol()] = '&';
    
    // TO DO (1) - put monsters into m_level
    
    // put player onto m_level
    if (m_level[m_player->getRowNum()][m_player->getColNum()] != '#')
        m_level[m_player->getRowNum()][m_player->getColNum()] = m_player->getChar();
    
    
    // print out level
    for (int row = 0; row < 18; row++) {
        for (int col = 0; col < 70; col++) {
            cout << m_level[row][col];
        }
        cout << endl;
    }
    
    // print out stats
    cout << "Dungeon Level: " << m_game->dungeon()->getCurrLevel() << ", Hit points: " << m_player->getHitPoints() << ", Armor: " << m_player->getArmor() << ", Strength: " << m_player->getStrength() << ", Dexterity: " << m_player->getDexterity() << endl;
}

bool Level::validMove(int row, int col)
{
    // actor can move onto blank space
    // TO DO (1) - actor can move onto interactable objects (staircase, idol, weapon, scroll)
    if (m_level[row][col] == ' ' || m_level[row][col] == '>' || m_level[row][col] == '&')
        return true;
    return false;
}

Player* Level::createPlayer()
{
    // if player is created at a wall, then get new player coordinates
    while (m_level[initialPlayerRow][initialPlayerCol] == '#') {
        initialPlayerRow = randInt(0, 17);
        initialPlayerCol = randInt(0, 69);
    }
    
    m_player = new Player(m_game, initialPlayerRow, initialPlayerCol);
    return m_player;
}

void Level::freePosition(int &row, int &col)        // obtains a free position (not wall, not monster, not object)
{
    while (m_level[row][col] != ' ') {
        row = randInt(0, 17);
        col = randInt(0, 69);
    }
}

bool Level::pickUpObject()
{
    // pick up the idol - win game and exit
    if (m_player->getRowNum() == m_progressionObject->getRow() && m_player->getColNum() == m_progressionObject->getCol() && m_progressionObject->getSymbol() == '&') {
        cout << endl << "You pick up the golden idol" << endl << "Congratulations, you won!" << endl << "Press q to exit the game.";
        char quit;
        while ((quit = getCharacter()) != 'q')
            {}
        exit(0);
        return true;
    }
    
    return false;
}


