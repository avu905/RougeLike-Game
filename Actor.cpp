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
    
    m_maxHitpoints = 20;
    m_maxArmorpoints = 99;
    m_maxStrpoints = 99;
    m_maxDexpoints = 99;
    m_maxSleeptime = 0;
    
    m_initialObject = object; 
}

Actor::~Actor()      // Actor Destructor - only for monsters to delete their weapon. Players have their own destructors that delete player's inventory
{
    delete m_initialObject;
}

void Actor::move(char direction)
{
    if (direction == 'h') {
        if (this->game()->dungeon()->level()->validMove(m_row, m_col-1) == true) {              // move left
            m_col = m_col - 1;
        }
    }
    if (direction == 'l') {
        if (this->game()->dungeon()->level()->validMove(m_row, m_col+1) == true) {              // move right
            m_col = m_col + 1;
        }
    }
    if (direction == 'k') {
        if (this->game()->dungeon()->level()->validMove(m_row-1, m_col) == true) {              // move up
            m_row = m_row - 1;
        }
    }
    if (direction == 'j') {
        if (this->game()->dungeon()->level()->validMove(m_row+1, m_col) == true) {              // move down
            m_row = m_row + 1;
        }
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

void Actor::playerCheat()
{
    m_strpoints = 9;
    m_hitpoints = 50;
    m_maxHitpoints = 50;
}

bool Actor::isMonsterAtPosition(Actor* attacker, Actor*& defender, int row, int col)
{
    for (int everyMonster = 0; everyMonster < m_game->dungeon()->level()->numberOfMonstersOnlevel(); everyMonster++) {
        if (row == game()->dungeon()->level()->monsterAtIndex(everyMonster)->getRowNum() && col == game()->dungeon()->level()->monsterAtIndex(everyMonster)->getColNum()) {
            defender = m_game->dungeon()->level()->monsterAtIndex(everyMonster);
            return true;
        }
    }
    return false;
}

void Actor::attack(Actor *attacker, Actor *defender, bool& message, string& messageToPrint)
{
    Weapon* attackerWeapon = dynamic_cast<Weapon*>(attacker->getInteractableObject());
    MagicFangsOfSleep* sleepWeapon = dynamic_cast<MagicFangsOfSleep*>(attacker->getInteractableObject());
    
    // calculate attacker and defender points
    int attackerPoints = attacker->getDexterity() + attackerWeapon->getWeaponDexterity();
    int defenderPoints = defender->getDexterity() + defender->getArmor();
    
    // update health and message to print depending on if there was an attack or not
    
    // if weapon is magic fangs of sleep
    if (sleepWeapon != nullptr) {
        if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
            int damagePointsSleep = randInt(0, attacker->getStrength() + attackerWeapon->getWeaponDamage() -1);
            defender->m_hitpoints = defender->m_hitpoints - damagePointsSleep;
            message = true;
            messageToPrint += attacker->getName() + " " + attackerWeapon->getWeaponAction() + " " + attackerWeapon->getName() + " at the " + defender->getName();
            
            if (defender->m_hitpoints <= 0) {
                messageToPrint += " dealing a final blow\n";
                return;
            }
            
            bool putToSleep = trueWithProbability(0.20);
            if (putToSleep == true) {
                message = true;
                messageToPrint += " and hits, putting " + defender->getName() + " to sleep.\n";
                int sleepTime = randInt(2, 6);
                if (defender->m_sleeptime > 0) {
                    if (defender->m_sleeptime >= sleepTime)
                        defender->m_sleeptime = defender->m_sleeptime;
                    else if (defender->m_sleeptime < sleepTime)
                        defender->m_sleeptime = sleepTime;
                }
                else if (defender->m_sleeptime == 0) {
                    defender->m_sleeptime = sleepTime;
                }
            }
            else if (putToSleep == false) {
                messageToPrint += " and hits.\n";
            }
            return;
        }
        else {
            message = true;
            messageToPrint += attacker->getName() + " " + attackerWeapon->getWeaponAction() + " " + attackerWeapon->getName() + " at the " + defender->getName() + " and misses.\n";
            return;
        }
    }

    // if weapons is not magic fangs of sleep
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
        int damagePoints = randInt(0, attacker->getStrength() + attackerWeapon->getWeaponDamage() - 1);
        defender->m_hitpoints = defender->m_hitpoints - damagePoints;
        message = true;
        messageToPrint += attacker->getName() + " " + attackerWeapon->getWeaponAction() + " " + attackerWeapon->getName() + " at the " + defender->getName();
        if (defender->m_hitpoints > 0)
            messageToPrint += " and hits.\n";
        else if (defender->m_hitpoints <= 0)
            messageToPrint += " dealing a final blow.\n";
    }
    else {
        message = true;
        messageToPrint += attacker->getName() + " " + attackerWeapon->getWeaponAction() + " " + attackerWeapon->getName() + " at the " + defender->getName() + " and misses.\n";
    }
}

void Actor::heal()
{
    bool actorWillHeal = trueWithProbability(0.10);
    if (actorWillHeal == true) {
        if (this->m_hitpoints < this->m_maxHitpoints)
            m_hitpoints++;
    }
}

void Actor::changePlayerPosition()
{
    game()->dungeon()->level()->freePosition(m_row, m_col);
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
InteractableObject* Actor::getInteractableObject()
{return m_initialObject;}

// ===================================================
// ============== MONSTER IMPLEMENTATION =============
// ===================================================
Monster::Monster(int row, int col, int hitpoints, string name, int armorpoints, int strpoints, int dexpoints, int sleeptime, Game* game, char c, InteractableObject* object)
: Actor(row, col, randInt(5, 10), name, 2, randInt(2, 3), randInt(2, 3), 0, game, c, object)
{}
//Monster::~Monster()
//{}

Goblin::Goblin(Game* game, int initialRow, int initialCol)
: Monster(initialRow, initialCol, randInt(15, 20), "Goblin", 1, 3, 1, 0, game, 'G', new Shortsword(0, 0, ')', game, "short sword", "slashes", 0, 2))
{}
//Goblin::~Goblin()
//{}
void Goblin::takeTurn(char userInput, Actor* attacker, bool& message, string& messageToPrint)
{
    // if goblin is asleep
    if (attacker->getSleepTime() > 0) {
        attacker->decreaseSleep();
        return;
    }
    
    // defender is always the player when goblin attacks
    Actor* defender = game()->player();
    
    // if player is next to the goblin, attack player
    if (attacker->getRowNum() == defender->getRowNum() && attacker->getColNum() - 1 == defender->getColNum()) {       // bogey men attack to left
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() && attacker->getColNum() + 1 == defender->getColNum()) {  // bogey men attack to right
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() - 1 && attacker->getColNum() == defender->getColNum()) {  // bogey men attack above
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() + 1 && attacker->getColNum() == defender->getColNum()) {  // bogey men attack below
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    
    // create copy of m_level to pass into goblin path algorithm
    char levelCopy [18][70];
    for (int row = 0; row < 18; row++) {
        for (int col = 0; col < 70; col++) {
            levelCopy[row][col] = game()->dungeon()->level()->getLevelChar(row, col);
        }
    }
    
    // call goblin path algorithm 4 times to find the path length starting from that direction
    int pathLengthIfGoLeft = game()->dungeon()->level()->findPath(levelCopy, attacker->getRowNum(), attacker->getColNum()-1, defender->getRowNum(), defender->getColNum(), 0, 'L');
    int pathLengthIfGoRight = game()->dungeon()->level()->findPath(levelCopy, attacker->getRowNum(), attacker->getColNum()+1, defender->getRowNum(), defender->getColNum(), 0, 'R');
    int pathLengthIfGoUp = game()->dungeon()->level()->findPath(levelCopy, attacker->getRowNum()-1, attacker->getColNum(), defender->getRowNum(), defender->getColNum(), 0, 'U');
    int pathLengthIfGoDown = game()->dungeon()->level()->findPath(levelCopy, attacker->getRowNum()+1, attacker->getColNum(), defender->getRowNum(), defender->getColNum(), 0, 'D');

    // sort through different path lengths
    int differentPathLengthsArr [4] = {pathLengthIfGoLeft, pathLengthIfGoRight, pathLengthIfGoUp, pathLengthIfGoDown};
    vector<int> differentPathLengthsVector;
    for (int i = 0; i < 4; i++) {
        if (differentPathLengthsArr[i] != 10000)
            differentPathLengthsVector.push_back(differentPathLengthsArr[i]);
    }
    
    // goblin is too far to smell, so goblin does nothing (moving in that direction is not an option)
    if (differentPathLengthsVector.empty() == true)
        return;
    
    // move in the direction of the shortest path
    int shortestPath = *min_element(differentPathLengthsVector.begin(), differentPathLengthsVector.end());
    if (shortestPath == pathLengthIfGoLeft) {
        attacker->move('h');
        return;
    }
    else if (shortestPath == pathLengthIfGoRight) {
        attacker->move('l');
        return;
    }
    else if (shortestPath == pathLengthIfGoUp) {
        attacker->move('k');
        return;
    }
    else if (shortestPath == pathLengthIfGoDown) {
        attacker->move('j');
        return;
    }
}

SnakeWomen::SnakeWomen(Game* game, int initialRow, int initialCol)
: Monster(initialRow, initialCol, randInt(3, 6), "Snake Women", 3, 2, 3, 0, game, 'S', new MagicFangsOfSleep(0, 0, ')', game, "magic fangs of sleep", "strikes", 3, 2))
{}
//SnakeWomen::~SnakeWomen()
//{}
void SnakeWomen::takeTurn(char userInput, Actor* attacker, bool& message, string& messageToPrint)
{
    // if snakewomen is asleep
    if (attacker->getSleepTime() > 0) {
        attacker->decreaseSleep();
        return;
    }
    
    // defender is always the player when snakewomen attack
    Actor* defender = game()->player();
    
    // if player is next to the snakewoemn, attack player
    if (attacker->getRowNum() == defender->getRowNum() && attacker->getColNum() - 1 == defender->getColNum()) {       // bogey men attack to left
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() && attacker->getColNum() + 1 == defender->getColNum()) {  // bogey men attack to right
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() - 1 && attacker->getColNum() == defender->getColNum()) {  // bogey men attack above
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() + 1 && attacker->getColNum() == defender->getColNum()) {  // bogey men attack below
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    
    if (defender->getRowNum() >= attacker->getRowNum() - 3 && defender->getRowNum() <= attacker->getRowNum() + 3 && defender->getColNum() >= attacker->getColNum() - 3 && defender->getColNum() <= attacker->getColNum() + 3) {

        int initialBogeyMenRow = attacker->getRowNum();
        int initialBogeyMenCol = attacker->getColNum();
        
        if (attacker->getColNum() - defender->getColNum() <= 3 && attacker->getColNum() - defender->getColNum() > 0) {
            attacker->move('h');
            if (initialBogeyMenRow != attacker->getRowNum() && initialBogeyMenCol != attacker->getColNum())
                return;
        }
        else if (attacker->getColNum() - defender->getColNum() >= -3 && attacker->getColNum() - defender->getColNum() < 0) {
            attacker->move('l');
            if (initialBogeyMenRow != attacker->getRowNum() && initialBogeyMenCol != attacker->getColNum())
                return;
        }
        else if (attacker->getRowNum() - defender->getRowNum() <= 3 && attacker->getRowNum() - defender->getRowNum() > 0) {
            attacker->move('k');
            if (initialBogeyMenRow != attacker->getRowNum() && initialBogeyMenCol != attacker->getColNum())
                return;
        }
        else if (attacker->getRowNum() - defender->getRowNum() >= -3 && attacker->getRowNum() - defender->getRowNum() < 0) {
            attacker->move('j');
            if (initialBogeyMenRow != attacker->getRowNum() && initialBogeyMenCol != attacker->getColNum())
                return;
        }
    }
    // no code needed for snakewomen to do nothing if snakewomen is too far to "smell" player
}

BogeyMen::BogeyMen(Game* game, int initialRow, int initialCol)
: Monster(initialRow, initialCol, randInt(5, 10), "Bogey Men", 2, randInt(2, 3), randInt(2, 3), 0, game, 'B', new Shortsword(0, 0, ')', game, "short sword", "slashes", 0, 2))
{}
//BogeyMen::~BogeyMen()
//{}
void BogeyMen::takeTurn(char userInput, Actor* attacker, bool& message, string& messageToPrint)
{
    // if bogeymen is asleep
    if (attacker->getSleepTime() > 0) {
        attacker->decreaseSleep();
        return;
    }
    
    // defender is always the player when bogeymen attack
    Actor* defender = game()->player();
    
    // if player is next to bogeymen, attack player
    if (attacker->getRowNum() == defender->getRowNum() && attacker->getColNum() - 1 == defender->getColNum()) {       // bogey men attack to left
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() && attacker->getColNum() + 1 == defender->getColNum()) {  // bogey men attack to right
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() - 1 && attacker->getColNum() == defender->getColNum()) {  // bogey men attack above
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() + 1 && attacker->getColNum() == defender->getColNum()) {  // bogey men attack below
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    
    if (defender->getRowNum() >= attacker->getRowNum() - 5 && defender->getRowNum() <= attacker->getRowNum() + 5 && defender->getColNum() >= attacker->getColNum() - 5 && defender->getColNum() <= attacker->getColNum() + 5) {

        int initialBogeyMenRow = attacker->getRowNum();
        int initialBogeyMenCol = attacker->getColNum();
        
        if (attacker->getColNum() - defender->getColNum() <= 5 && attacker->getColNum() - defender->getColNum() > 0) {
            attacker->move('h');
            if (initialBogeyMenRow != attacker->getRowNum() && initialBogeyMenCol != attacker->getColNum())
                return;
        }
        else if (attacker->getColNum() - defender->getColNum() >= -5 && attacker->getColNum() - defender->getColNum() < 0) {
            attacker->move('l');
            if (initialBogeyMenRow != attacker->getRowNum() && initialBogeyMenCol != attacker->getColNum())
                return;
        }
        else if (attacker->getRowNum() - defender->getRowNum() <= 5 && attacker->getRowNum() - defender->getRowNum() > 0) {
            attacker->move('k');
            if (initialBogeyMenRow != attacker->getRowNum() && initialBogeyMenCol != attacker->getColNum())
                return;
        }
        else if (attacker->getRowNum() - defender->getRowNum() >= -5 && attacker->getRowNum() - defender->getRowNum() < 0) {
            attacker->move('j');
            if (initialBogeyMenRow != attacker->getRowNum() && initialBogeyMenCol != attacker->getColNum())
                return;
        }
    }
    
    // no code needed for bogeymen to do nothing if bogeymen is too far to "smell" player
}

Dragon::Dragon(Game* game, int initialRow, int initialCol)
: Monster(initialRow, initialCol, randInt(20, 25), "Dragon", 4, 4, 4, 0, game, 'D', new LongSword(0, 0, ')', game, "long sword", "swings", 2, 4))
{}
//Dragon::~Dragon()
//{}
void Dragon::takeTurn(char userInput, Actor* attacker, bool& message, string& messageToPrint)
{
    // heal dragon
    attacker->heal();
    
    // if dragon is asleep
    if (attacker->getSleepTime() > 0) {
        attacker->decreaseSleep();
        return;
    }
    
    // defender is always the player when dragon attacks
    Actor* defender = game()->player();
    
    // if player is next to the dragon, attack player
    if (attacker->getRowNum() == defender->getRowNum() && attacker->getColNum() - 1 == defender->getColNum()) {       // bogey men attack to left
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() && attacker->getColNum() + 1 == defender->getColNum()) {  // bogey men attack to right
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() - 1 && attacker->getColNum() == defender->getColNum()) {  // bogey men attack above
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
    else if (attacker->getRowNum() == defender->getRowNum() + 1 && attacker->getColNum() == defender->getColNum()) {  // bogey men attack below
        attacker->attack(attacker, defender, message, messageToPrint);
        return;
    }
}

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
    // delete player's inventory
    for (int inv = 0; inv < m_inventory.size(); inv++) {
        if (m_inventory[inv] != getInteractableObject())
            delete m_inventory[inv];
    }
}

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
        MessageToPrint = "You are wielding " + this->inventoryObjectNameAtIndex(weaponToWield - 'a') + "\n";
    }
    else if (validWeapon == nullptr) {
        MessageToPrint = "You can't wield " + this->inventoryObjectNameAtIndex(weaponToWield - 'a') + "\n";
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
                MessageToPrint += "Your armor glows blue.\n";
            }
        }
        else if (validScroll->getScrollType() == 'H') {
            int increase = validScroll->getEnhance();
            if (this->getMaxHitPoints() + increase <= 99) {
                this->increaseMaxHitPoints(validScroll->getEnhance());
                MessageToPrint += "You feel your heart beating stronger.\n";
            }
        }
        else if (validScroll->getScrollType() == 'S') {
            int increase = validScroll->getEnhance();
            if (this->getStrength() + increase <= this->getMaxStrengthPoints()) {
                this->increaseStrengthPoints(validScroll->getEnhance());
                MessageToPrint += "Your muscles bulge.\n";
            }
        }
        else if (validScroll->getScrollType() == 'D') {
            int increase = validScroll->getEnhance();
            if (this->getDexterity() + increase <= this->getmaxDexterityPoints()) {
                this->increaseDexterityPoints(validScroll->getEnhance());
                MessageToPrint += "You feel like less of a klutz.\n";
            }
        }
        else if (validScroll->getScrollType() == 'T') {
            int newRowPosition = 0;     // doesn't matter what this int's initial value is b/c freePosition() function reassgns its value
            int newColPosition = 0;     // doesn't matter what this int's initial value is b/c freePosition() function reassgns its value
            this->game()->dungeon()->level()->freePosition(newRowPosition, newColPosition);
            this->newPlayerPositionByTeleportationScroll(newRowPosition, newColPosition);
            MessageToPrint += "You feel your body wrenched in space and time.\n";
        }
        delete m_inventory[scrollToRead - 'a'];
        m_inventory.erase(m_inventory.begin()+(scrollToRead - 'a'));
    }
    else if (validScroll == nullptr) {
        MessageToPrint = "You can't read a " + this->inventoryObjectNameAtIndex(scrollToRead - 'a') + "\n";
    }
    return true;
}

void Player::takeTurn(char userInput, Actor* attacker, bool& message, string& messageToPrint)
{
    Actor* defender = nullptr;
    
    if (userInput == 'h') {                 // move or attack left
        if (isMonsterAtPosition(attacker, defender, attacker->getRowNum(), attacker->getColNum() - 1) == true) {
            attacker->attack(attacker, defender, message, messageToPrint);
        }
        else
            attacker->move(userInput);
    }
    else if (userInput == 'l') {           // move or attack right
        if (isMonsterAtPosition(attacker, defender, attacker->getRowNum(), attacker->getColNum() + 1) == true) {
            attacker->attack(attacker, defender, message, messageToPrint);
        }
        else
            attacker->move(userInput);
    }
    else if (userInput == 'k') {           // move or attack above
        if (isMonsterAtPosition(attacker, defender, attacker->getRowNum() - 1, attacker->getColNum()) == true) {
            attacker->attack(attacker, defender, message, messageToPrint);
        }
        else
            attacker->move(userInput);
    }
    else if (userInput == 'j') {           // move or attack below
        if (isMonsterAtPosition(attacker, defender, attacker->getRowNum() + 1, attacker->getColNum()) == true) {
            attacker->attack(attacker, defender, message, messageToPrint);
        }
        else
            attacker->move(userInput);
    }
}
