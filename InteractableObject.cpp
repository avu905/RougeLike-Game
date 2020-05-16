//
//  InteractableObject.cpp
//  CS 32 - Project 3
//
//  Created by Alex Vu on 5/11/20.
//  Copyright © 2020 Alex Vu. All rights reserved.
//

#include "Game.h"
#include "Dungeon.h"
#include "InteractableObject.h"

// ========================================================
// ========== INTERACTABLE OBJECT IMPLEMENTATION ==========
// ========================================================
InteractableObject::InteractableObject()                                            // default constructor
{}

InteractableObject::InteractableObject(int row, int col, char symbol, Game* game)   // progression object constructor
: m_row(row), m_col(col), m_symbol(symbol), m_game(game)
{}

InteractableObject::~InteractableObject()
{}

int InteractableObject::getRow()
    {return m_row;}
int InteractableObject::getCol()
    {return m_col;}
char InteractableObject::getSymbol()
    {return m_symbol;}

// =======================================================
// ========== WEAPON IMPLEMENTATION ======================
// =======================================================
Weapon::Weapon(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount)
: InteractableObject(row, col, symbol, game)
{
    m_name = name;
    m_action = action;
    m_dexterityBonus = dexterityBonus;
    m_damageAmount = damageAmount;
}
Weapon::~Weapon()
{}
string Weapon::getName()
    {return m_name;}

Shortsword::Shortsword(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount)
: Weapon(row, col, symbol, game, name, action, dexterityBonus, damageAmount)
{}
Shortsword::~Shortsword()
{}

Mace::Mace(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount)
: Weapon(row, col, symbol, game, name, action, dexterityBonus, damageAmount)
{}
Mace::~Mace()
{}

LongSword::LongSword(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount)
: Weapon(row, col, symbol, game, name, action, dexterityBonus, damageAmount)
{}
LongSword::~LongSword()
{}

MagicAxe::MagicAxe(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount)
: Weapon(row, col, symbol, game, name, action, dexterityBonus, damageAmount)
{}
MagicAxe::~MagicAxe()
{}

MagicFangsOfSleep::MagicFangsOfSleep(int row, int col, char symbol, Game* game, string name, string action, int dexterityBonus, int damageAmount)
: Weapon(row, col, symbol, game, name, action, dexterityBonus, damageAmount)
{}
MagicFangsOfSleep::~MagicFangsOfSleep()
{}

// =======================================================
// ========== SCROLL IMPLEMENTATION ======================
// =======================================================
// SCROLLS - shown as ?
    // scroll of teleportation
    // scroll of improve armor
    // scroll of raise strength
    // scroll of enhance health
    // scroll of enhance dexterity
Scroll::Scroll(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance)
: InteractableObject(row, col, symbol, game)
{
    m_name = name;
    m_action = action;
    m_scrollType = scrollType;
    m_enhance = enhance;
}
Scroll::~Scroll()
{}
string Scroll::getName()
    {return m_name;}
char Scroll::getScrollType()
    {return m_scrollType;}
int Scroll::getEnhance()
    {return m_enhance;}

ScrollOfTeleportation::ScrollOfTeleportation(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance)
: Scroll(row, col, symbol, game, name, action, scrollType, enhance)
{}
ScrollOfTeleportation::~ScrollOfTeleportation()
{}

ScrollOfImproveArmor::ScrollOfImproveArmor(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance)
: Scroll(row, col, symbol, game, name, action, scrollType, enhance)
{}
ScrollOfImproveArmor::~ScrollOfImproveArmor()
{}

ScrollOfRaiseStrength::ScrollOfRaiseStrength(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance)
: Scroll(row, col, symbol, game, name, action, scrollType, enhance)
{}
ScrollOfRaiseStrength::~ScrollOfRaiseStrength()
{}

ScrollOfEnhanceHealth::ScrollOfEnhanceHealth(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance)
: Scroll(row, col, symbol, game, name, action, scrollType, enhance)
{}
ScrollOfEnhanceHealth::~ScrollOfEnhanceHealth()
{}

ScrollOfEnhanceDexterity::ScrollOfEnhanceDexterity(int row, int col, char symbol, Game* game, string name, string action, char scrollType, int enhance)
: Scroll(row, col, symbol, game, name, action, scrollType, enhance)
{}
ScrollOfEnhanceDexterity::~ScrollOfEnhanceDexterity()
{}

// =======================================================
// ========== PROGRESSION OBJECT IMPLEMENTATION ==========
// =======================================================
ProgressionObject::ProgressionObject(int row, int col, char symbol, Game* game)
: InteractableObject(row, col, symbol, game)
{}

ProgressionObject::~ProgressionObject()
{}

Staircase::Staircase(int row, int col, char symbol, Game* game)
: ProgressionObject(row, col, symbol, game)
{}

Staircase::~Staircase()
{}

Idol::Idol(int row, int col, char symbol, Game* game)
: ProgressionObject(row, col, symbol, game)
{}

Idol::~Idol()
{}



