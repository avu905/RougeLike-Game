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

Game::~Game()
{
    // TO DO (1) - delete dungeon (dungeon should delete level - level should delete monsters and weapons/scrolls on it)
    // TO DO (1) - delete player (player should delete weapons/scrolls in its inventory)
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
        // TO DO (1) - newlines print out correctly and that there is not a newline before the grid is displayed
        // TO DO (1) - should clear screen be at the very bottom of the do while instead of the first thing?
        clearScreen();
        
        // TO DO (1) - should display be the very first thing b/c we need to display how everything look so the user knows where the player and mosnters are
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
                // TO DO (1) - there is an extra new line between where message prints out and you enter in the userInput
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
        
        // TO DO (1) - update m_level with row and position of player and erase old row and position of player after player's turn so monsters can move correctly
        // TO DO (1) - sometimes the monsters overlap when they move, but why?
        
        // TO DO (1) - loop through and if any monsters are dead print out applicable message
        // TO DO (1) - should clearDeadMonsters() come before moveMonsters() since the player can kill a monster?
        // clear all dead monsters before monsters make their move since the player could've killed a monster during the player's turn
        m_dungeon->level()->clearDeadMonsters();
        
        // TO DO (1) - if after player's turn the player kills a monster, ensure that the monster is removed immediately and that moveMonsters() does not move a dead monster
        // TO DO (1) - is userInput for moveMonsters() useless here?
        // TO DO (1) - ensure computer message is printed correctly
        // MONSTERS' TURN
        m_dungeon->level()->moveMonsters(userInput, computerMessage, messageToPrint);
        
        // TO DO (1) - if player is dead print out applicable message and delete everything - THIS MUST COME BEFORE B/C WILL HAVE TO IMMEDIATELY END GAME IF PLAYER DIES

        // heal player after each user input
        m_player->heal();
        
        // TO DO (1) - heal dragons that have not been killed before each turn the dragon takes
        // TO DO (1) - possible idea is the level will have a function to heal dragons ==> m_dungeon->level()->healDragons();
        
        
    }
    while (m_player->getHitPoints() > 0);
    
    
    // TO DO (1) - when player dies print out appropriate message
    // TO DO (1) - when player dies, need to print out "monster strikes weapon at player, DEALING FINAL BLOW"
    
    m_dungeon->level()->display();
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

