//
//  InteractableObject.hpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/11/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#ifndef INTER_OBJ_H
#define INTER_OBJ_H

#include<iostream>

class Game;
#include "utilities.h"
#include <string>

using namespace std;

// =====================================================
// ========== INTERACTABLE OBJECT DECLARATION ==========
// =====================================================
class InteractableObject
{
public:
    InteractableObject();                                                  // default constructor
    InteractableObject(int row, int col, char symbol, Game* game);         // progression object constructor (staircase and idol)
    virtual ~InteractableObject();                                         // destructor
    
    // accessors
    int getRow();
    int getCol();
    char getSymbol();
    
private:
    Game* m_game;
    int m_row;
    int m_col;
    char m_symbol;
};

// =======================================================
// ========== WEAPON DECLARATION =========================
// =======================================================
// WEAPONS - shown as )
    // short swords - dex = 0; damage = 2
    // maces - dex = 0; damage = 2
    // long swords - dex = 2; damage = 4
    // magic axes - dex = 5; damage = 5
    // magic fangs of sleep - dex = 3; damage = 2; 1/5 chance puts defender to sleep for X 2-6 turns if awake; if asleep (sleeptime = Y) then defender's sleep time is max of X and Y

class Weapon : public InteractableObject
{
public:
    Weapon(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount);
    virtual ~Weapon();
private:
    string m_name;
    string m_action;
    int m_dexterityBonus;
    int m_damageAmount;
};

class Shortsword : public Weapon
{
public:
    Shortsword(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount);
    virtual ~Shortsword();
private:
};

// =======================================================
// ========== SCROLL DECLARATION =========================
// =======================================================

// =====================================================
// ========== PROGRESSION OBJECT DECLARATIONS ==========
// =====================================================
class ProgressionObject : public InteractableObject
{
public:
    ProgressionObject(int row, int col, char symbol, Game* game);
    virtual ~ProgressionObject();
private:
};

class Staircase : public ProgressionObject
{
public:
    Staircase(int row, int col, char symbol, Game* game);
    ~Staircase();
private:
};

class Idol : public ProgressionObject
{
public:
    Idol(int row, int col, char symbol, Game* game);
    ~Idol();
private:
};

#endif // INTER_OBJ_H
