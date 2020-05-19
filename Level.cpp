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

Level::Level(Game* game, int curr_level)        // Level Constructor
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
        // weapons : short sword, mace, long sword ONLY
        // scrolls : armor, health, strength, dexterity ONLY
    int numObjectsInLevel = randInt(2, 3);
    for (int i = 0; i < numObjectsInLevel; i++) {
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
    
    // put monsters in level
        // goblin : level 0 - 4
        // snake woman : level 0 - 4
        // bogey man : level 2 - 4
        // dragon : level 3 - 4
    int numMonstersInLevel = randInt(2, 5 * (curr_level + 1) + 1);
    for (int monstersAdded = 0; monstersAdded < numMonstersInLevel; monstersAdded++) {
        if (curr_level == 0 || curr_level == 1) {          // goblins, snakewomen
            addMonster(randInt(0, 1));
        }
        else if (curr_level == 2) {                        // goblins, snakewomen, bogeymen
            addMonster(randInt(0, 2));
        }
        else if (curr_level == 3 || curr_level == 4) {     // goblins, snakewomen, bogeymen, dragons
            addMonster(randInt(0, 3));
        }
    }
    
    // put idol or staircase in level
    int progressionObjectRow = randInt(0, 17);
    int progressionObjectCol = randInt(0, 69);
    freePosition(progressionObjectRow, progressionObjectCol);
    if (curr_level != 4)
        m_progressionObject = new Staircase(progressionObjectRow, progressionObjectCol, '>', m_game);
    else if (curr_level == 4)
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
    // populate m_level with only walls and interactable objects (not including staircases and golden idol)
    // TO DO (1) - is the if statement correct - should it be "if (m_level[row][col] != '#' && m_level[row][col] != '?' && m_level[row][col] != ')')"
    for (int row = 0; row < 18; row++) {
        for (int col = 0; col < 70; col++) {
            if (m_level[row][col] != '#' && m_level[row][col] != '?' && m_level[row][col] != ')')
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
    
    // put monsters into m_level
    for (int i = 0; i < m_monsters.size(); i++) {
        m_level[m_monsters[i]->getRowNum()][m_monsters[i]->getColNum()] = m_monsters[i]->getChar() ;
    }
    
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
    cout << "Dungeon Level: " << m_game->dungeon()->getCurrLevel() << ", Hit points: " << m_player->getHitPoints() << ", Armor: " << m_player->getArmor() << ", Strength: " << m_player->getStrength() << ", Dexterity: " << m_player->getDexterity() << endl << endl;
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

bool Level::pickUpObject(string& messageToPrint)
{
    // pick up the idol - win game and exit
    if (m_player->getRowNum() == m_progressionObject->getRow() && m_player->getColNum() == m_progressionObject->getCol() && m_progressionObject->getSymbol() == '&') {
        cout << endl << "You pick up the golden idol" << endl << "Congratulations, you won!" << endl << "Press q to exit game.";
        char quit;
        while ((quit = getCharacter()) != 'q')
            {}
        exit(0);
        return true;
    }
    
    // pick up an object
    // TO DO (1) - make sure the if statement should be < 26 and not < 25
    if (m_player->getInventorySize() < 26) {
        for (int i = 0; i < m_objects.size(); i++) {
            if (m_player->getRowNum() == m_objects[i]->getRow() && m_player->getColNum() == m_objects[i]->getCol()) {
                messageToPrint += "You pick up ";
                if (m_objects[i]->getSymbol() == ')') {
                    Weapon* weaponPointer = dynamic_cast<Weapon*>(m_objects[i]);
                    messageToPrint += weaponPointer->getName();
                }
                else if (m_objects[i]->getSymbol()) {
                    Scroll* scrollPointer = dynamic_cast<Scroll*>(m_objects[i]);
                    messageToPrint += "a scroll called ";
                    messageToPrint += scrollPointer->getName();
                }
                m_player->addObjectToInventory(m_objects[i]);         // add object to player's m_inventory
                m_objects.erase(m_objects.begin() + i);               // erase object from levels m_objects vector (level no longer has access to that object)
            }
        }
        return true;
    }
    else {
        messageToPrint += "Your knapsack is full; you can't pick that up.";
        return true;    // TO DO (1) - should I return true here ?????
    }
    
    // TO DO (1) - should I return false here or should I return true
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

void Level::addMonster(int monsterType)
{
    int initialMonsterRow = randInt(0, 17);
    int initialMonsterCol = randInt(0, 69);
    freePosition(initialMonsterRow, initialMonsterCol);
    if (monsterType == 0) {
        m_monsters.push_back(new Goblin(m_game, initialMonsterRow, initialMonsterCol));
    }
    else if (monsterType == 1) {
        m_monsters.push_back(new SnakeWomen(m_game, initialMonsterRow, initialMonsterCol));
    }
    else if (monsterType == 2) {
        m_monsters.push_back(new BogeyMen(m_game, initialMonsterRow, initialMonsterCol));
    }
    else if (monsterType == 3) {
        m_monsters.push_back(new Dragon(m_game, initialMonsterRow, initialMonsterCol));
    }
}

void Level::clearDeadMonsters()
{
    // TO DO (1) - fix : when player deals final blow to monster, monster doesn't die immediatley. The monster instead can attack the player again and then after the monster is erased
    for (int i = 0; i < m_monsters.size(); i++) {
        if (m_monsters[i]->getHitPoints() <= 0) {
            // TO DO (1) - monsters should drop an item if they die by calling drop item function
            monsterDropItem(m_monsters[i]);
            delete m_monsters[i];
            m_monsters.erase(m_monsters.begin() + i);
        }
    }
}

void Level::monsterDropItem(Monster* monster)
{
    if (monster->getChar() == 'B') {
        if (isObjectAtSpot(monster) == true)
            return;
        bool chanceOfDropping = trueWithProbability(0.10);
        if (chanceOfDropping == true)
            m_objects.push_back(new MagicAxe(monster->getRowNum(), monster->getColNum(), ')', m_game, "magic axe", "chops", 5, 5));
    }
    else if (monster->getChar() == 'S') {
        if (isObjectAtSpot(monster) == true)
            return;
        bool chanceOfDropping = trueWithProbability(0.3333333);
        if (chanceOfDropping == true)
            m_objects.push_back(new MagicFangsOfSleep(monster->getRowNum(), monster->getColNum(), ')', m_game, "magic fangs of sleep", "strikes", 3, 2));
    }
    // TO DO (1) - sometimes dragon will drop a weapon ?????
    else if (monster->getChar() == 'D') {
        if (isObjectAtSpot(monster) == true)
            return;
        int scrollToDrop = randInt(0, 4);
        if (scrollToDrop == 0)
            m_objects.push_back(new ScrollOfTeleportation(monster->getRowNum(), monster->getColNum(), '?', m_game, "scroll of teleportation", "You feel your body wrenched in space and time.", 'T', 0));
        else if (scrollToDrop == 1)
            m_objects.push_back(new ScrollOfImproveArmor(monster->getRowNum(), monster->getColNum(), '?', m_game, "scroll of enhance armor", "Your armor glows blue.", 'A', randInt(1, 3)));
        else if (scrollToDrop == 2)
            // ScrollOfRaiseStrength(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance);
            m_objects.push_back(new ScrollOfRaiseStrength(monster->getRowNum(), monster->getColNum(), '?', m_game, "scroll of strength", "Your muscles bulge.", 'S', randInt(1, 3)));
        else if (scrollToDrop == 3)
            m_objects.push_back(new ScrollOfEnhanceHealth(monster->getRowNum(), monster->getColNum(), '?', m_game, "scroll of enhance health", "You feel your heart beating stronger.", 'H', randInt(3, 8)));
        else if (scrollToDrop == 4)
            m_objects.push_back(new ScrollOfEnhanceDexterity(monster->getRowNum(), monster->getColNum(), '?', m_game, "scroll of enhance dexterity", "You feel like less of a klutz.", 'D', 1));
    }
    else if (monster->getChar() == 'G') {
        if (isObjectAtSpot(monster) == true)
            return;
        bool chanceOfDropping = trueWithProbability(0.3333333);
        int magicAxeOrMagicFangsOfSleep = randInt(0, 1);
        if (chanceOfDropping == true && magicAxeOrMagicFangsOfSleep == 0)
            m_objects.push_back(new MagicFangsOfSleep(monster->getRowNum(), monster->getColNum(), ')', m_game, "magic fangs of sleep", "strikes", 3, 2));
        else if (chanceOfDropping == true && magicAxeOrMagicFangsOfSleep == 1)
            m_objects.push_back(new MagicAxe(monster->getRowNum(), monster->getColNum(), ')', m_game, "magic axe", "chops", 5, 5));
    }
}

bool Level::isObjectAtSpot(Monster* monster)
{
    // only checks if weapon or scroll is at that position
    for (int i = 0; i < m_objects.size(); i++) {
        if (monster->getRowNum() == m_objects[i]->getRow() && monster->getColNum() == m_objects[i]->getCol())
            return true;
    }
    
    // checks if staircase or idol is at that position
    if (monster->getRowNum() == m_progressionObject->getRow() && monster->getColNum() == m_progressionObject->getCol())
        return true;
    
    // there is not object at that position
    return false;
}

void Level::moveMonsters(char userInput, bool& message, string& messageToPrint)
{
    for (int i = 0; i < m_monsters.size(); i++) {
        m_monsters[i]->takeTurn(userInput, m_monsters[i], message, messageToPrint);
    }
}

int Level::findPath(char levelCopy[][70], int startRow, int startCol, int endRow, int endCol, int pathLength)
{
    // TO DO (1) - optimize recursive algorithm - don't go backwards
    
    // base case (1) - found length from start to end position. Return length
    if (startRow == endRow && startCol == endCol)
        return pathLength;
    
    // base case (2) - invalid starting position (start on wall, monster, or position that has already been searched)
    if (levelCopy[startRow][startCol] != ' ' && levelCopy[startRow][startCol] !=  '>' && levelCopy[startRow][startCol] != '&' && levelCopy[startRow][startCol] != ')' && levelCopy[startRow][startCol] != '?')
        return 10000;
    
    // base case (3) - if goblin is too far to smell, don't move goblin
    if (pathLength > m_game->getGoblinSmellDistance())
        return 10000;
    
    int pathLengthIfGoLeft = 0;
    int pathLengthIfGoRight = 0;
    int pathLengthIfGoUp = 0;
    int pathLengthIfGoDown = 0;
    
    // recursive call on each direction
    pathLengthIfGoUp = findPath(levelCopy, startRow-1, startCol, endRow, endCol, pathLength+1);
    pathLengthIfGoDown = findPath(levelCopy, startRow+1, startCol, endRow, endCol, pathLength+1);
    pathLengthIfGoLeft = findPath(levelCopy, startRow, startCol-1, endRow, endCol, pathLength+1);
    pathLengthIfGoRight = findPath(levelCopy, startRow, startCol+1, endRow, endCol, pathLength+1);
    
    // return optimal path direction
    if  (pathLengthIfGoUp <= pathLengthIfGoDown && pathLengthIfGoUp <= pathLengthIfGoLeft && pathLengthIfGoUp <= pathLengthIfGoRight) {
        return pathLengthIfGoUp;
    }
    else if (pathLengthIfGoDown <= pathLengthIfGoLeft && pathLengthIfGoDown <= pathLengthIfGoRight) {
        return pathLengthIfGoDown;
    }
    else if (pathLengthIfGoLeft <= pathLengthIfGoRight) {
        return pathLengthIfGoLeft;
    }
    else {
        return pathLengthIfGoRight;
    }
}
