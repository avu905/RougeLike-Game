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

Game::~Game()
{
    // TO DO (1) - delete dungeon (dungeon should delete level - level should delete monsters and weapons/scrolls on it)
    // TO DO (1) - delete player (player should delete weapons/scrolls in its inventory)
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
    string messageToPrint = "";     // this sting will be modified and added to depending on what each actor (player/monster) does
    bool playerMessage = false;
    bool computerMessage = false;
    
    do {
        // TO DO (1) - check board for dead monsters and clear board of dead monsters (destruct monster)
        // TO DO (1) - HEAL 1/10th chance player hitpoints will increase
        
        // TO DO (1) - newlines print out correctly and that there is not a newline before the grid is displayed
        clearScreen();
        
        // display the dungeon
        m_dungeon->level()->display();
        
        // print message after player or monster does something
        if (playerMessage == true) {             // print message when player does something
            cout << messageToPrint << endl;
            playerMessage = false;
        }
        else if (computerMessage == true) {       // print message when computer/monsters do something
            cout << messageToPrint << endl;
            computerMessage = false;
        }
        
        // after printing message, reset the message that needs to be printed
        messageToPrint = "";
        
        char userInput;
        userInput = getCharacter();
        // player is not asleep
        if (m_player->getSleepTime() == 0) {
            if (userInput == 'q')           // quit Game
                return;
            if (userInput == 'h' || userInput == 'j' || userInput == 'k' || userInput == 'l') { // player moves or attacks
                // TO DO (1) - update player message here m_player->takeTurn(userInput, m_player, playerMessage, messageToPrint);
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
        
        // TO DO (1) - move the monsters only after the player has moved
                // TO DO (1) - move the monsters
                // TO DO (1) - update computer message if there is a message to be printed out
        // TO DO (1) - finish implementing this ==> computerMessage = m_dungeon->level()->moveMonsters();
//        for (int i = 0; i < m_dungeon->level()->numberOfMonstersOnlevel(); i++) {
//            m_dungeon->level()->moveMonsters(); AND moveMonsters will call the move() function for monsters
              // m_dungeon->level()->moveMonsters()->takeTurn()
              //
//        }
        
        // TO DO (1) - if player is dead print out applicable message and delet everything - THIS MUST COME BEFORE B/C WILL HAVE TO IMMEDIATELY END GAME IF PLAYER DIES
        
        // TO DO (1) - loop through and if any monsters are dead print out applicable message
        // clear all dead monsters
        m_dungeon->level()->clearDeadMonsters();
        
        
    }
    while (m_player->getHitPoints() > 0);
    
    
    // TO DO (1) - when player dies print out appropriate message
        // TO DO (1) - printout player has died
        // TO DO (1) -
    
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.

