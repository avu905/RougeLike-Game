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
    m_player = new Player(this);
    m_player->move(randInt(0, 17), randInt(0, 69));
    m_dungeon = new Dungeon(this);
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
    cout << "Press q to exit game." << endl;
    char c;
    while ((c = getCharacter()) != 'q') {
        if (c == 'h' && m_player->attemptMove() == true) {        // move left
            m_player->move(m_player->getRowNum(), m_player->getColNum()-1);
        }
        if (c == 'l' && m_player->attemptMove() == true) {        // move right
            m_player->move(m_player->getRowNum(), m_player->getColNum()+1);
        }
        if (c == 'k') {          // move up
            m_player->move(m_player->getRowNum()-1, m_player->getColNum());
        }
        if (c == 'j') {          // move down
            m_player->move(m_player->getRowNum()+1, m_player->getColNum());
        }
//        if (getCharacter() == 'g')      // pick up object
//            {}
//        if (getCharacter() == 'w')      // wield weapon and select from inventory
//            {}
//        if (getCharacter() == 'r')      // read scroll and select from inventory
//            {}
//        if (getCharacter() == 'i')      // see inventory
//            {}
//        if (getCharacter() == '>')      // go down stairway
//            {}
//        if (getCharacter() == 'c')      // cheat
//            {}
        clearScreen();
        m_dungeon->display();
        // TO DO - call diff functions that cout "dragon attacks and hits" etc.
    };
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.

