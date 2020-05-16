//
//  Actor.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/10/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "Actor.h"
//#include "globals.h"
#include "utilities.h"


// ===================================================
// ============== ACTOR IMPLEMENTATION ===============
// ===================================================
Actor::Actor(int row, int col, int hitpoints, string name, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game, char c, InteractableObject* object)
{
    // Set initial values for actor
    m_row = row;
    m_col = col;
    m_hitpoints = hitpoints;
    m_name = name;
    m_armorpoints = armorpoints;
    m_strpoints = strpoints;
    m_dexpoints = dexpoints;
    m_sleeptime = sleeptime;
    m_game = game;
    m_char = c;
    
    m_maxHitpoints = 20;            // TO DO (1) - should this be 20 and then it's increased after reading a scroll of health
    m_maxArmorpoints = 99;
    m_maxStrpoints = 99;
    m_maxDexpoints = 99;
    m_maxSleeptime = 0;
    
    m_initialObject = object; 
}

Actor::~Actor()      // Actor Destructor
{}

void Actor::move(char direction)
{
    if (direction == 'h' && this->game()->dungeon()->level()->validMove(m_row, m_col-1) == true) {    // move left
        m_col = m_col - 1;
    }
    if (direction == 'l' && this->game()->dungeon()->level()->validMove(m_row, m_col+1) == true) {    // move right
        m_col = m_col + 1;
    }
    if (direction == 'k' && this->game()->dungeon()->level()->validMove(m_row-1, m_col) == true) {    // move up
        m_row = m_row - 1;
    }
    if (direction == 'j' && this->game()->dungeon()->level()->validMove(m_row+1, m_col) == true) {    // move down
        m_row = m_row + 1;
    }
}

void Actor::decreaseSleep()
{m_sleeptime--;}

void Actor::holdInitialObject(InteractableObject* object)
{
    m_initialObject = object;
}

void Actor::increaseArmorPoints(int increase)
{
    m_armorpoints += increase;
}

void Actor::increaseMaxHitPoints(int increase)
{
    m_maxHitpoints += increase;
}

void Actor::increaseStrengthPoints(int increase)
{
    m_strpoints += increase;
}

void Actor::increaseDexterityPoints(int increase)
{
    m_dexpoints += increase;
}
void Actor::newPlayerPositionByTeleportationScroll(int newRow, int newCol)
{
    m_row = newRow;
    m_col = newCol;
}

// TO DO (1) - implement playerCheat() correctly. should it set hitpoints and maxHitpoints to 50?
void Actor::playerCheat()
{
    m_strpoints = 9;
    m_hitpoints = 50;
    m_maxHitpoints = 50;
}

// accessors
Game* Actor::game()
    {return m_game;}
int Actor::getRowNum()
    {return m_row;}
int Actor::getColNum()
    {return m_col;}
int Actor::getHitPoints()
    {return m_hitpoints;}
int Actor::getMaxHitPoints()
    {return m_maxHitpoints;}
string Actor::getName()
    {return m_name;}
int Actor::getArmor()
    {return m_armorpoints;}
int Actor::getMaxArmorPoints()
    {return m_maxArmorpoints;}
int Actor::getStrength()
    {return m_strpoints;}
int Actor::getMaxStrengthPoints()
    {return m_maxStrpoints;}
int Actor::getDexterity()
    {return m_dexpoints;}
int Actor::getmaxDexterityPoints()
{return m_maxDexpoints;}
char Actor::getChar()
    {return m_char;}
int Actor::getSleepTime()
{return m_sleeptime;}

// ===================================================
// ============== MONSTER IMPLEMENTATION =============
// ===================================================
Monster::Monster(int row, int col, int hitpoints, string name, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game, char c, InteractableObject* object)
: Actor(row, col, randInt(5, 10), "Bogey Men", 2, randInt(2, 3), randInt(2, 3), 0, game, c, object)
{
    
}

Monster::~Monster()
{}

BogeyMen::BogeyMen(Game* game, int initialRow, int initialCol)
: Monster(initialRow, initialCol, randInt(5, 10), "Bogey Men", 2, randInt(2, 3), randInt(2, 3), 0, game, 'B', new Shortsword(0, 0, 'A', game, "short sword", "slashes", 0, 2))
{
    // create specific weapon
}

BogeyMen::~BogeyMen()
{}



// ===================================================
// ============== PLAYER IMPLEMENTATION ==============
// ===================================================
Player::Player(Game* game, int initialRow, int initialCol)
: Actor(initialRow, initialCol, 20, "Player", 2, 2, 2, 0, game, '@', nullptr)
{
    // short sword added to m_inventory at index [0]
    int initialWeaponRow = 0;       // placed on a wall so technically not on level so can't pick up initial weapon at (0,0)
    int initialWeaponCol = 0;       // placed on a wall so technically not on level so can't pick up initial weapon at (0,0)
    m_inventory.push_back(new Shortsword(initialWeaponRow, initialWeaponCol, ')', game, "short sword", "slashes", 0, 2));
    // player initially holds a short sword
    holdInitialObject(m_inventory[0]);
}

Player::~Player()
{
    // TO DO (1) - delete objects in player's inventory
}

// TO DO (1) - possibly delete attemptMove(char c)
//bool Player::attemptMove(char c)
//{
//    // can't move in that direction
//    if (c == 'h' && game()->dungeon()->level()->getLevelChar(getRowNum(), getColNum()-1) == '#')
//        return false;
//    if (c == 'l' && game()->dungeon()->level()->getLevelChar(getRowNum(), getColNum()+1) == '#')
//        return false;
//    if (c == 'j' && game()->dungeon()->level()->getLevelChar(getRowNum()+1, getColNum()) == '#')
//        return false;
//    if (c == 'k' && game()->dungeon()->level()->getLevelChar(getRowNum()-1, getColNum()) == '#')
//        return false;
//    return true;
//}

int Player::getInventorySize()
    {return m_inventory.size();}

void Player::addObjectToInventory(InteractableObject* objectToAdd)
{
    m_inventory.push_back(objectToAdd);
}

void Player::displayInventory()
{
    // clear screen before writing out inventory
    clearScreen();
    
    cout << "Inventory: " << endl;
    
    char alphabetCharacter = 'a';
    for (int i = 0; i < m_inventory.size(); i++) {
        cout << " " << alphabetCharacter << ". ";
        if (m_inventory[i]->getSymbol() == '?')
            cout << "A scroll called ";
        cout << this->inventoryObjectNameAtIndex(i) << endl;
        alphabetCharacter++;
    }
    getCharacter();
}

string Player::inventoryObjectNameAtIndex(int objectIndex)
{
    string objectName = "";
    if (m_inventory[objectIndex]->getSymbol() == ')') {
        Weapon* weaponPointer = dynamic_cast<Weapon*>(m_inventory[objectIndex]);
        objectName = weaponPointer->getName();
    }
    else if (m_inventory[objectIndex]->getSymbol() == '?') {
        Scroll* scrollPointer = dynamic_cast<Scroll*>(m_inventory[objectIndex]);
        objectName = scrollPointer->getName();
    }
    return objectName;
}

bool Player::wieldWeapon(string& MessageToPrint)
{
    // clear screen and print inventory
    clearScreen();
    cout << "Inventory: " << endl;
    char alphabetCharacter = 'a';
    for (int i = 0; i < m_inventory.size(); i++) {
        cout << " " << alphabetCharacter << ". ";
        if (m_inventory[i]->getSymbol() == '?')
            cout << "A scroll called ";
        cout << this->inventoryObjectNameAtIndex(i) << endl;
        alphabetCharacter++;
    }
    
    // inputs a character signifying which weapon they want to wield
    char weaponToWield = getCharacter();
    
    // user did not input a valid character (inputted a non-alphabet character and or a letter that doesn't correspond to an object in the inventory)
    if (!(weaponToWield - 'a' >= 0 && weaponToWield - 'a' <= m_inventory.size() - 1))
        return false;
    
    // if the inputted character refers to a weapon or not
    Weapon* validWeapon = dynamic_cast<Weapon*>(m_inventory[weaponToWield-'a']);
    if (validWeapon != nullptr ) {
        this->holdInitialObject(validWeapon);
        MessageToPrint = "You are wielding " + this->inventoryObjectNameAtIndex(weaponToWield - 'a');
    }
    else if (validWeapon == nullptr) {
        MessageToPrint = "You can't wield " + this->inventoryObjectNameAtIndex(weaponToWield - 'a');
    }
    return true;
}

bool Player::readScroll(string &MessageToPrint)
{
    // clear screen and print inventory
    clearScreen();
    cout << "Inventory: " << endl;
    char alphabetCharacter = 'a';
    for (int i = 0; i < m_inventory.size(); i++) {
        cout << " " << alphabetCharacter << ". ";
        if (m_inventory[i]->getSymbol() == '?')
            cout << "A scroll called ";
        cout << this->inventoryObjectNameAtIndex(i) << endl;
        alphabetCharacter++;
    }
    
    // inputs a character signifying which scroll they want to read
    char scrollToRead = getCharacter();
    
    // user did not input a valid character (inputted a non-alphabet character and or a letter that doesn't correspond to an object in the inventory)
    if (!(scrollToRead - 'a' >= 0 && scrollToRead - 'a' <= m_inventory.size() - 1))
        return false;
    
    // if the inputted character refers to a scroll or not
    Scroll* validScroll = dynamic_cast<Scroll*>(m_inventory[scrollToRead - 'a']);
    MessageToPrint = "You read the scroll called " + this->inventoryObjectNameAtIndex(scrollToRead - 'a') + '\n';
    if (validScroll != nullptr) {
        if (validScroll->getScrollType() == 'A') {
            int increase = validScroll->getEnhance();
            if (this->getArmor() + increase <= this->getMaxArmorPoints()) {
                this->increaseArmorPoints(increase);
                MessageToPrint += "Your armor glows blue.";
            }
        }
        else if (validScroll->getScrollType() == 'H') {
            int increase = validScroll->getEnhance();
            if (this->getMaxHitPoints() + increase <= 99) {
                this->increaseMaxHitPoints(validScroll->getEnhance());
                MessageToPrint += "You feel your heart beating stronger.";
            }
        }
        else if (validScroll->getScrollType() == 'S') {
            int increase = validScroll->getEnhance();
            if (this->getStrength() + increase <= this->getMaxStrengthPoints()) {
                this->increaseStrengthPoints(validScroll->getEnhance());
                MessageToPrint += "Your muscles bulge.";
            }
        }
        else if (validScroll->getScrollType() == 'D') {
            int increase = validScroll->getEnhance();
            if (this->getDexterity() + increase <= this->getmaxDexterityPoints()) {
                this->increaseDexterityPoints(validScroll->getEnhance());
                MessageToPrint += "You feel like less of a klutz.";
            }
        }
        // TO DO (1) - make sure reading a teleportation scroll works correctly
        else if (validScroll->getScrollType() == 'T') {
            int newRowPosition = 0;     // doesn't matter what this int's initial value is b/c freePosition() function reassgns its value
            int newColPosition = 0;     // doesn't matter what this int's initial value is b/c freePosition() function reassgns its value
            this->game()->dungeon()->level()->freePosition(newRowPosition, newColPosition);
            this->newPlayerPositionByTeleportationScroll(newRowPosition, newColPosition);
            MessageToPrint =+ "You feel your body wrenched in space and time.";
        }
        delete m_inventory[scrollToRead - 'a'];
        m_inventory.erase(m_inventory.begin()+(scrollToRead - 'a'));
    }
    else if (validScroll == nullptr) {
        MessageToPrint = "You can't read a " + this->inventoryObjectNameAtIndex(scrollToRead - 'a');
    }
    return true;
}
