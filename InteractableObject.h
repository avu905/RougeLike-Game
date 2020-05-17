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
// 2 or 3 scrolls or weapons are put on each level
    // short sword
    // mace
    // long sword
    // NOT magic fangs of sleep
    // NOT magic axes
    // NOT teleportation scrolls
    // scroll of improve armor
    // scroll of raise strength
    // scroll of enhance health
    // scroll of enhance dexterity
class Weapon : public InteractableObject
{
public:
    Weapon();       // constructor for weapon
    Weapon(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount); // constructor for weapons put into level
    virtual ~Weapon();
    string getName();
    int getWeaponDexterity();
    int getWeaponDamage();
    string getWeaponAction();
    
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
    ~Shortsword();
private:
};

class Mace : public Weapon
{
public:
    Mace(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount);
    ~Mace();
private:
};

class LongSword : public Weapon
{
public:
    LongSword(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount);
    ~LongSword();
private:
};

class MagicAxe : public Weapon
{
public:
    MagicAxe(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount);
    ~MagicAxe();
private:
};

class MagicFangsOfSleep : public Weapon
{
public:
    MagicFangsOfSleep(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount);
    ~MagicFangsOfSleep();
private:
    // TO DO (1) - should fangs to sleep have it's own private data member m_sleep
};
// =======================================================
// ========== SCROLL DECLARATION =========================
// =======================================================
class Scroll : public InteractableObject
{
public:
    Scroll(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance);
    virtual ~Scroll();
    string getName();
    char getScrollType();
    int getEnhance();
private:
    string m_name;
    string m_action;
    char m_scrollType;
    int m_enhance;          // m_enhance is irrelevant for teleportation scroll since I use the freePosition() function instead
                            // TO DO (1) - just a note: any instantiation of teleportation scroll will have it's m_enhance be set to 0 since it's useless fo teleportation scrolls
};

class ScrollOfTeleportation : public Scroll
{
public:
    ScrollOfTeleportation(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance);
    ~ScrollOfTeleportation();
private:
};

class ScrollOfImproveArmor : public Scroll
{
public:
    ScrollOfImproveArmor(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance);
    ~ScrollOfImproveArmor();
private:
};

class ScrollOfRaiseStrength : public Scroll
{
public:
    ScrollOfRaiseStrength(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance);
    ~ScrollOfRaiseStrength();
private:
};

class ScrollOfEnhanceHealth : public Scroll
{
public:
    ScrollOfEnhanceHealth(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance);
    ~ScrollOfEnhanceHealth();
private:
};

class ScrollOfEnhanceDexterity : public Scroll
{
public:
    ScrollOfEnhanceDexterity(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance);
    ~ScrollOfEnhanceDexterity();
private:
};

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
