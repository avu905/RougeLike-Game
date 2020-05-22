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
    // add walls to m_level
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 70; j++) {
            m_level[i][j] = '#';
        }
    }
    
    // call function to make rooms and corridors
    makeRooms();
    
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

Level::~Level()                     // Level Destructor
{
    // delete progression object
    delete m_progressionObject;
    
    //delete scrolls and weapons on level
    for (int o = 0; o < m_objects.size(); o++) {
        delete m_objects[o];
    }
    
    // delete monsters on level
    for (int m = 0; m < m_monsters.size(); m++) {
        delete m_monsters[m];
    }
}

void Level::display()
{
    // populate m_level with only walls and interactable objects (not including staircases and golden idol)
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
    // can't move onto player
    if (row == m_game->player()->getRowNum() && col == m_game->player()->getColNum())
        return false;
    
    // can't move onto monster
    for (int i = 0; i < m_monsters.size(); i++) {
        if (row == m_monsters[i]->getRowNum() && col == m_monsters[i]->getColNum())
            return false;
    }
    
    // can't move onto wall
    if (m_level[row][col] == '#')
        return false;
    
    return true;
    
    // actor can move onto blank space or object
//    if (m_level[row][col] == ' ' || m_level[row][col] == '>' || m_level[row][col] == '&' || m_level[row][col] == ')' || m_level[row][col] == '?')
//        return true;
//
//    return false;
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
    if (m_player->getInventorySize() < 26) {
        for (int i = 0; i < m_objects.size(); i++) {
            if (m_player->getRowNum() == m_objects[i]->getRow() && m_player->getColNum() == m_objects[i]->getCol()) {
                messageToPrint += "You pick up ";
                if (m_objects[i]->getSymbol() == ')') {
                    Weapon* weaponPointer = dynamic_cast<Weapon*>(m_objects[i]);
                    messageToPrint += weaponPointer->getName() + "\n";
                }
                else if (m_objects[i]->getSymbol()) {
                    Scroll* scrollPointer = dynamic_cast<Scroll*>(m_objects[i]);
                    messageToPrint += "a scroll called ";
                    messageToPrint += scrollPointer->getName() + "\n";
                }
                m_player->addObjectToInventory(m_objects[i]);         // add object to player's m_inventory
                m_objects.erase(m_objects.begin() + i);               // erase object from levels m_objects vector (level no longer has access to that object)
            }
        }
        return true;
    }
    else {                                                            // full inventory - can't pick up object
        messageToPrint += "Your knapsack is full; you can't pick that up.\n";
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
    // get free position for monster
    int initialMonsterRow = randInt(0, 17);
    int initialMonsterCol = randInt(0, 69);
    freePosition(initialMonsterRow, initialMonsterCol);
    // add monster
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
    // drop item depending on monster that died
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
    
    // there is no object at that position
    return false;
}

void Level::moveMonsters(char userInput, bool& message, string& messageToPrint)
{
    for (int i = 0; i < m_monsters.size(); i++) {
        m_monsters[i]->takeTurn(userInput, m_monsters[i], message, messageToPrint);
    }
}

int Level::findPath(char levelCopy[][70], int startRow, int startCol, int endRow, int endCol, int pathLength, char dirEntered)
{
    // base case (1) - found length from start to end position. Return length
    if (startRow == endRow && startCol == endCol)
        return pathLength;
    
    // base case (2) - invalid starting position (start on wall, monster, or position that has already been searched)
    if (levelCopy[startRow][startCol] != ' ' && levelCopy[startRow][startCol] !=  '>' && levelCopy[startRow][startCol] != '&' && levelCopy[startRow][startCol] != ')' && levelCopy[startRow][startCol] != '?')
        return 10000;
    
    // base case (3) - if goblin is too far to smell, don't move goblin
    if (pathLength > m_game->getGoblinSmellDistance())
        return 10000;
    
    // TO DO (1) - make sure this base case is correct - base case (4) - if shortest possible path is more than 15, immediately return
    int totalLength = 0;
    if (startRow > endRow)
        totalLength += startRow - endRow;
    else if (startRow < endRow)
        totalLength += endRow - startRow;
    if (startCol > endCol)
        totalLength += startCol - endCol;
    else if (startCol < endCol)
        totalLength += endCol - startCol;
    if (totalLength > m_game->getGoblinSmellDistance())
        return 10000;
    
    // function returns 10000 unless an optimal smell distance is found
    int pathLengthIfGoLeft = 10000;
    int pathLengthIfGoRight = 10000;
    int pathLengthIfGoUp = 10000;
    int pathLengthIfGoDown = 10000;
    
    // recursive call on each direction
    if (dirEntered == 'D') {
        pathLengthIfGoDown = findPath(levelCopy, startRow+1, startCol, endRow, endCol, pathLength+1, 'D');
        pathLengthIfGoLeft = findPath(levelCopy, startRow, startCol-1, endRow, endCol, pathLength+1, 'L');
        pathLengthIfGoRight = findPath(levelCopy, startRow, startCol+1, endRow, endCol, pathLength+1, 'R');
    }
    else if (dirEntered == 'U') {
        pathLengthIfGoUp = findPath(levelCopy, startRow-1, startCol, endRow, endCol, pathLength+1, 'U');
        pathLengthIfGoLeft = findPath(levelCopy, startRow, startCol-1, endRow, endCol, pathLength+1, 'L');
        pathLengthIfGoRight = findPath(levelCopy, startRow, startCol+1, endRow, endCol, pathLength+1, 'R');
    }
    else if (dirEntered == 'L') {
        pathLengthIfGoUp = findPath(levelCopy, startRow-1, startCol, endRow, endCol, pathLength+1, 'U');
        pathLengthIfGoDown = findPath(levelCopy, startRow+1, startCol, endRow, endCol, pathLength+1, 'D');
        pathLengthIfGoLeft = findPath(levelCopy, startRow, startCol-1, endRow, endCol, pathLength+1, 'L');
    }
    else if (dirEntered == 'R') {
        pathLengthIfGoRight = findPath(levelCopy, startRow, startCol+1, endRow, endCol, pathLength+1, 'R');
        pathLengthIfGoUp = findPath(levelCopy, startRow-1, startCol, endRow, endCol, pathLength+1, 'U');
        pathLengthIfGoDown = findPath(levelCopy, startRow+1, startCol, endRow, endCol, pathLength+1, 'D');
    }
    
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

void Level::makeRooms()
{
    // random number of rooms to make
    int numRooms = randInt(3, 6);
    int layout = randInt(1, 2);
    
    // create 3 rooms
    if (numRooms == 3) {
        if (layout == 1) {
            // make rooms
            int row1start = randInt(1, 4);
            int row1end = randInt(13, 16);
            int col1start = randInt(1, 3);
            for (int i = row1start; i < row1end; i++) {
                for (int j = col1start; j < 12; j++) {
                    m_level[i][j] = ' ';
                }
            }
            int row2start = randInt(1, 5);
            int row2end = randInt(11, 16);
            for (int i = row2start; i < row2end; i++) {
                for (int j = 16; j < 35; j++)
                    m_level[i][j] = ' ';
            }
            int row3start = randInt(1, 6);
            int row3end = randInt(13, 15);
            int col3end = randInt(54, 67);
            for (int i = row3start; i < row3end; i++) {
                for (int j = 42; j < col3end; j++)
                    m_level[i][j] = ' ';
            }
            // make cooridors
            int c1 = randInt(6, 9);
            for (int j = 12; j < 16; j++) {
                m_level[c1][j] = ' ';
            }
            
            int c2 = randInt(6, 9);
            for (int j = 35; j < 42; j++) {
                m_level[c2][j] = ' ';
            }
        }
        else if (layout == 2) {
            // make rooms
            int row1start = randInt(2, 5);
            int row1end = randInt(11, 16);
            int col1start = randInt(3, 5);
            for (int i = row1start; i < row1end; i++) {
                for (int j = col1start; j < 20; j++) {
                    m_level[i][j] = ' ';
                }
            }
            int row2start = randInt(3, 5);
            int row2end = randInt(11, 16);
            for (int i = row2start; i < row2end; i++) {
                for (int j = 24; j < 45; j++)
                    m_level[i][j] = ' ';
            }
            int row3start = randInt(4, 8);
            int row3end = randInt(14, 16);
            int col3end = randInt(62, 67);
            for (int i = row3start; i < row3end; i++) {
                for (int j = 52; j < col3end; j++) {
                    m_level[i][j] = ' ';
                }
            }
            // make corridors
            int c1 = randInt(6, 10);
            for (int j = 20; j < 24; j++) {
                m_level[c1][j] = ' ';
            }
            int c2 = randInt(9, 10);
            for (int j = 45; j < 52; j++) {
                m_level[c2][j] = ' ';
            }
        }
    }
    // create 4 rooms
    else if (numRooms == 4) {
        if (layout == 1) {
            // make rooms
            int row1start = randInt(1, 4);
            int row1end = randInt(10, 16);
            int col1start = randInt(1, 3);
            for (int i = row1start; i < row1end; i++) {
                for (int j = col1start; j < 10; j++) {
                    m_level[i][j] = ' ';
                }
            }
            int row2start = randInt(1, 4);
            int row2end = randInt(10, 16);
            for (int i = row2start; i < row2end; i++) {
                for (int j = 12; j < 25; j++) {
                    m_level[i][j] = ' ';
                }
            }
            int row3start = randInt(1, 4);
            int row3end = randInt(10, 16);
            for (int i = row3start; i < row3end; i++) {
                for (int j = 30; j < 41; j++)
                    m_level[i][j] = ' ';
            }
            int row4start = randInt(1, 4);
            int row4end = randInt(10, 16);
            int col4end = randInt(61, 68);
            for (int i = row4start; i < row4end; i++) {
                for (int j = 50; j < col4end; j++) {
                    m_level[i][j] = ' ';
                }
            }
            // make corridors
            int c1 = randInt(5, 9);
            for (int j = 10; j < 12; j++) {
                m_level[c1][j] = ' ';
            }
            int c2 = randInt(5, 9);
            for (int j = 25; j < 30; j++) {
                m_level[c2][j] = ' ';
            }
            int c3 = randInt(5, 9);
            for (int j = 41; j < 50; j++) {
                m_level[c3][j] = ' ';
            }
        }
        else if (layout == 2) {
            int row1start = randInt(1, 4);
            int row1end = randInt(10, 16);
            int col1start = randInt(1, 3);
            for (int i = row1start; i < row1end; i++) {
                for (int j = col1start; j < 15; j++) {
                    m_level[i][j] = ' ';
                }
            }
            int row2start = randInt(1, 4);
            int row2end = randInt(10, 16);
            for (int i = row2start; i < row2end; i++) {
                for (int j = 20; j < 32; j++) {
                    m_level[i][j] = ' ';
                }
            }
            int row3start = randInt(1, 4);
            int row3end = randInt(10, 16);
            for (int i = row3start; i < row3end; i++) {
                for (int j = 36; j < 43; j++)
                    m_level[i][j] = ' ';
            }
            int row4start = randInt(1, 4);
            int row4end = randInt(10, 16);
            int col4end = randInt(63, 68);
            for (int i = row4start; i < row4end; i++) {
                for (int j = 57; j < col4end; j++) {
                    m_level[i][j] = ' ';
                }
            }
            // make corridors
            int c1 = randInt(5, 9);
            for (int j = 15; j < 20; j++) {
                m_level[c1][j] = ' ';
            }
            int c2 = randInt(5, 9);
            for (int j = 32; j < 36; j++) {
                m_level[c2][j] = ' ';
            }
            int c3 = randInt(5, 9);
            for (int j = 43; j < 57; j++) {
                m_level[c3][j] = ' ';
            }
        }
    }
    // create 5 rooms
    else if (numRooms == 5) {
        // make rooms
        int row1start = 13;
        int row1end = randInt(15, 16);
        int col1start = randInt(1, 3);
        int col1end = randInt(8, 27);
        for (int i = row1start; i < row1end; i++) {
            for (int j = col1start; j < col1end; j++) {
                m_level[i][j] = ' ';
            }
        }
        int row2start = randInt(1, 3);
        int row2end = 8;
        int col2start = randInt(1, 3);
        int col2end = 12;
        for (int i = row2start; i < row2end; i++) {
            for (int j = col2start; j < col2end; j++) {
                m_level[i][j] = ' ';
            }
        }
        int row3start = randInt(1, 3);
        int row3end = randInt(8, 11);
        int col3start = 16;
        int col3end = 23;
        for (int i = row3start; i < row3end; i++) {
            for (int j = col3start; j < col3end; j++) {
                m_level[i][j] = ' ';
            }
        }
        int row4start = randInt(1, 3);
        int row4end = randInt(7, 16);
        int col4start = 29;
        int col4end = 40;
        for (int i = row4start; i < row4end; i++) {
            for (int j = col4start; j < col4end; j++) {
                m_level[i][j] = ' ';
            }
        }
        int row5start = randInt(1, 5);
        int row5end = randInt(11, 16);
        int col5start  = 48;
        int col5end = randInt(55, 68);
        for (int i = row5start; i < row5end; i++) {
            for (int j = col5start; j < col5end; j++) {
                m_level[i][j] = ' ';
            }
        }
        // make corridors
        int c1 = randInt(4, 7);
        for (int i = 8; i < 13; i++) {
            m_level[i][c1] = ' ';
        }
        int c2 = randInt(4, 7);
        for (int j = 12; j < 16; j++) {
            m_level[c2][j] = ' ';
        }
        int c3 = randInt(4, 6);
        for (int j = 23; j < 29; j++) {
            m_level[c3][j] = ' ';
        }
        int c4 = randInt(5, 6);
        for (int j = 40; j < 48; j++) {
            m_level[c4][j] = ' ';
        }
    }
    // create 6 rooms
    else if (numRooms == 6) {
        // make rooms
        int row1start = randInt(1, 3);
        int row1end = 8;
        int col1start = randInt(1, 3);
        int col1end = 12;
        for (int i = row1start; i < row1end; i++) {
            for (int j = col1start; j < col1end; j++) {
                m_level[i][j] = ' ';
            }
        }
        int row2start = randInt(1, 3);
        int row2end = 10;
        int col2start = 15;
        int col2end = 23;
        for (int i = row2start; i < row2end; i++) {
            for (int j = col2start; j < col2end; j++) {
                m_level[i][j] = ' ';
            }
        }
        int row3start = randInt(1, 3);
        int row3end = 9;
        int col3start = 29;
        int col3end = randInt(35, 66);
        for (int i = row3start; i < row3end; i++) {
            for (int j = col3start; j < col3end; j++) {
                m_level[i][j] = ' ';
            }
        }
        
        int row4start = 11;
        int row4end = randInt(15, 16);
        int col4start = randInt(1, 3);
        int col4end = 10;
        for (int i = row4start; i < row4end; i++) {
            for (int j = col4start; j < col4end; j++) {
                m_level[i][j] = ' ';
            }
        }
        int row5start = 12;
        int row5end = randInt(15, 16);
        int col5start = 17;
        int col5end = 25;
        for (int i = row5start; i < row5end; i++) {
            for (int j = col5start; j < col5end; j++) {
                m_level[i][j] = ' ';
            }
        }
        int row6start = 12;
        int row6end = randInt(15, 16);
        int col6start = 31;
        int col6end = randInt(38, 60);
        for (int i = row6start; i < row6end; i++) {
            for (int j = col6start; j < col6end; j++) {
                m_level[i][j] = ' ';
            }
        }
        // make corridors
        int c1 = randInt(4, 8);
        for (int i = 8; i < 11; i++) {
            m_level[i][c1] = ' ';
        }
        int c2 = randInt(4, 6);
        for (int j = 12; j < 15; j++) {
            m_level[c2][j] = ' ';
        }
        int c3 = randInt(4, 7);
        for (int j = 23; j < 29; j++) {
            m_level[c3][j] = ' ';
        }
        int c4 = randInt(32, 33);
        for (int i = 9; i < 12; i++) {
            m_level[i][c4] = ' ';
        }
        int c5 = randInt(12, 14);
        for (int j = 25; j < 31; j++) {
            m_level[c5][j] = ' ';
        }
    }
}
