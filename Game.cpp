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

Game::Game(int goblinSmellDistance)                    // Game Constructor
{
    m_dungeon = new Dungeon(this);                     // create dungeon
    m_player = m_dungeon->level()->createPlayer();     // create player
    m_goblinSmellDistance = goblinSmellDistance;
}

Game::~Game()                                          // Game destructor
{
    delete m_dungeon;
    delete m_player;
}

Player* Game::player()
{
    return m_player;
}

Dungeon* Game::dungeon()
{
    return m_dungeon;
}

int Game::getGoblinSmellDistance()
{
    return m_goblinSmellDistance;
}


void Game::play()
{
    string messageToPrint = "";     // this sting will be modified and added to depending on what each actor (player/monster) does
    bool playerMessage = false;     // this bool lets us know if the player did an action that needs to be printed to the screen
    bool computerMessage = false;   // this bool lets us know if the monsters did an action that needs to be printed to the screen
    
    do {
        clearScreen();
        
        // display the dungeon
        m_dungeon->level()->display();
        
        // print message after player or monster does something
        if (playerMessage == true) {
            cout << messageToPrint << endl;
            playerMessage = false;
        }
        else if (computerMessage == true) {
            cout << messageToPrint << endl;
            computerMessage = false;
        }
        
        // after printing message, reset the message that needs to be printed
        messageToPrint = "";
        
        // PLAYER'S TURN
        char userInput;
        userInput = getCharacter();
        
        // player is not asleep
        if (m_player->getSleepTime() == 0) {
            if (userInput == 'q')                                                               // quit Game
                return;
            if (userInput == 'h' || userInput == 'j' || userInput == 'k' || userInput == 'l') { // player moves or attacks
                m_player->takeTurn(userInput, m_player, playerMessage, messageToPrint);
            }
            if (userInput == '>') {                                                             // take staircase
                if ( m_player->getRowNum() == m_dungeon->level()->progressObj()->getRow() && m_player->getColNum() == m_dungeon->level()->progressObj()->getCol() && m_dungeon->level()->progressObj()->getSymbol() == '>')
                    m_dungeon->newLevel();
            }
            if (userInput == 'g') {                                                             // pick up item (idol, weapon, scroll)
                 playerMessage = m_dungeon->level()->pickUpObject(messageToPrint);
            }
            if (userInput == 'i') {                                                             // display inventory
                m_player->displayInventory();
            }
            if (userInput == 'w') {                                                             // wield weapon
                playerMessage = m_player->wieldWeapon(messageToPrint);
            }
            if (userInput == 'r') {                                                             // read scroll
                playerMessage = m_player->readScroll(messageToPrint);
            }
            if (userInput == 'c') {                                                             // cheat - for testing purposes
                m_player->playerCheat();
            }
        }
        
        // player is asleep
        if (m_player->getSleepTime() != 0)
            m_player->decreaseSleep();
        
        // clear all dead monsters before monsters make their move since the player could've killed a monster during the player's turn
        m_dungeon->level()->clearDeadMonsters();
        
        // MONSTERS' TURN
        m_dungeon->level()->moveMonsters(userInput, computerMessage, messageToPrint);

        // heal player after each user input
        m_player->heal();
    }
    while (m_player->getHitPoints() > 0);
    
    m_dungeon->level()->display();
    cout << messageToPrint;
    cout << "Press q to exit game." << endl;
    char quitDead;
    while ((quitDead = getCharacter()) != 'q')
        {}
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.

