//
//  Game.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.

#include "Game.h"
#include "utilities.h"
#include <iostream>

#include "Dungeon.h"

#include <string>
#include <vector>

using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)     // Game Constructor
{
    m_dungeon = new Dungeon(this);                     // create dungeon
    m_player = m_dungeon->level()->createPlayer();     // create player
}

Player* Game::player()
{
    return m_player;
}

Dungeon* Game::dungeon()
{
    return m_dungeon;
}


void Game::play()
{
    // string message = ""; //
    // bool displayPlayerMessage = false;
    // bool displayComputerMessage = false;
    
    do {
        // TO DO (1) - check board for dead monsters and clear board of dead monsters (destruct monster)
        // TO DO (1) - 1/10th chance player hitpoints will increase
        
        // TO DO (1) - newlines print out correctly and that there is not a newline before the grid is displayed
        clearScreen();
        
        char userInput;
        
        m_dungeon->level()->display();
        
        userInput = getCharacter();
        
        // player is not asleep
        if (m_player->getSleepTime() == 0) {
            if (userInput == 'q')           // quit Game
                return;
            if (userInput == 'h' || userInput == 'j' || userInput == 'k' || userInput == 'l')   // player moves or attacks
                m_player->move(userInput);
            if (userInput == '>') {                                                             // take staircase
                if ( m_player->getRowNum() == m_dungeon->level()->progressObj()->getRow() && m_player->getColNum() == m_dungeon->level()->progressObj()->getCol() && m_dungeon->level()->progressObj()->getSymbol() == '>')
                    m_dungeon->newLevel();
            }
            if (userInput == 'g') {                                                             // pick up item (idol, weapon, scroll)
                m_dungeon->level()->pickUpObject();
            }
        }
        
        
        // player is asleep
        if (m_player->getSleepTime() != 0)
            m_player->decreaseSleep();
    }
    while (m_player->getHitPoints() > 0);
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.

