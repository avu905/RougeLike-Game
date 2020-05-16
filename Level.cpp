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
//#include <vector>

Level::Level(Game* game)        // Level Constructor
: m_game(game), m_player(m_game->player())
{
    // TO DO (1) - write algorithm to populate levels with random walls and rooms
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
    
    // put weapon and scroll objects in level
    int numObjectsInLevel = randInt(2, 3);
    // loop and
    for (int i = 0; i < numObjectsInLevel; i++) {
        // only make short sword, mace, long sword - only make scroll armor, health, strength, dexterity
        int weaponOrScroll = randInt(1, 2);
        if (weaponOrScroll == 1) {
            int weaponType = randInt(1, 3);
            addInteractableObject(weaponType);
        }
        else if (weaponOrScroll == 2) {
            int scrollType = randInt(4, 7);
            addInteractableObject(scrollType);
        }
    }
    
    // TO DO (1) - put monsters in level
    
    // put idol or staircase in level
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
    // TO DO (1) - delete scrolls and weapons on level
    // TO DO (1) - delete monsters on level
    delete m_progressionObject;
}

void Level::display()
{
    // populate m_level with only walls and blank spaces
    // TO DO (1) - populate m_level with only walls and interactable objects (not including staircases and golden idol)
    for (int row = 0; row < 18; row++) {
        for (int col = 0; col < 70; col++) {
            if (m_level[row][col] != '#' && m_level[row][col] != '&' && m_level[row][col] != ')')
                m_level[row][col] = ' ';
        }
    }
    
    // put objects into m_level
    for (int i = 0; i < m_objects.size(); i++) {
        m_level[m_objects[i]->getRow()][m_objects[i]->getCol()] = m_objects[i]->getSymbol();
    }
    
    // put progression object onto level
    if (m_game->dungeon()->getCurrLevel() != 4)
        m_level[m_progressionObject->getRow()][m_progressionObject->getCol()] = '>';
    else if (m_game->dungeon()->getCurrLevel() == 4)
        m_level[m_progressionObject->getRow()][m_progressionObject->getCol()] = '&';
    
    // TO DO (1) - put monsters into m_level
    
    // put player onto m_level
    if (m_level[m_player->getRowNum()][m_player->getColNum()] != '#')
        m_level[m_player->getRowNum()][m_player->getColNum()] = m_player->getChar();
    
    // print out m_level
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
    // TO DO (1) - actors cannot move onto other actors
    
    // actor can move onto blank space or object
    if (m_level[row][col] == ' ' || m_level[row][col] == '>' || m_level[row][col] == '&' || m_level[row][col] == ')' || m_level[row][col] == '?')
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

bool Level::pickUpObject(string& MessageToPrint)
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
    
    // pick up an object
    if (m_player->getInventorySize() < 25) {
        for (int i = 0; i < m_objects.size(); i++) {
            if (m_player->getRowNum() == m_objects[i]->getRow() && m_player->getColNum() == m_objects[i]->getCol()) {
                MessageToPrint += "You pick up ";
                if (m_objects[i]->getSymbol() == ')') {
                    Weapon* weaponPointer = dynamic_cast<Weapon*>(m_objects[i]);
                    MessageToPrint += weaponPointer->getName();
                }
                else if (m_objects[i]->getSymbol()) {
                    Scroll* scrollPointer = dynamic_cast<Scroll*>(m_objects[i]);
                    MessageToPrint += "a scroll called ";
                    MessageToPrint += scrollPointer->getName();
                }
                m_player->addObjectToInventory(m_objects[i]);       // add object to player's m_inventory
                m_objects.erase(m_objects.begin()+i);               // erase object from levels m_objects vector (level no longer has access to that object)
            }
        }
        return true;
    }
    else {
        MessageToPrint += "Your knapsack is full; you can't pick that up.";
        return true;    // TO DO (1) - should I return true here ?????
    }
    
    // TO DO (1) - should I return falsehere or should I return true
    return false;
}

void Level::addInteractableObject(int objectType)
{
    // position of object to put into level
    int objectRow = randInt(0, 18);
    int objectCol = randInt(0, 69);
    freePosition(objectRow, objectCol);
    
    // depending on object type passed in (ie the int objectType), the corresponding object will be created
    if (objectType == 1)
        m_objects.push_back(new Shortsword(objectRow, objectCol, ')', m_game, "short sword", "slashes", 0, 2));
    else if (objectType == 2)
        m_objects.push_back(new Mace(objectRow, objectCol, ')', m_game, "mace", "swings", 0, 2));
    else if (objectType == 3)
        m_objects.push_back(new LongSword(objectRow, objectCol, ')', m_game, "long sword", "swings", 2, 4));
    else if (objectType == 4)
        m_objects.push_back(new ScrollOfImproveArmor(objectRow, objectCol, '?', m_game, "scroll of enhance armor", "Your armor glows blue.", 'A', randInt(1, 3)));
    else if (objectType == 5)
        m_objects.push_back(new ScrollOfEnhanceHealth(objectRow, objectCol, '?', m_game, "scroll of enhance health", "You feel your heart beating stronger.", 'H', randInt(3, 8)));
    else if (objectType == 6)
        m_objects.push_back(new ScrollOfRaiseStrength(objectRow, objectCol, '?', m_game, "scroll of strength", "Your muscles bulge.", 'S', randInt(1, 3)));
    else if (objectType == 7)
        m_objects.push_back(new ScrollOfEnhanceDexterity(objectRow, objectCol, '?', m_game, "scroll of enhance dexterity", "You feel like less of a klutz.", 'D', 1));
}

