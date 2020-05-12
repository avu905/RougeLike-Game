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

#include "utilities.h"

using namespace std;

// ========== InteractableObject Declaration ==========
class InteractableObject
{
public:
    InteractableObject();                        // non-parameter constructor for weapons
    InteractableObject(int row, int col);        // parameter constructor for staircase and idol
    virtual ~InteractableObject();               // destructor
    
    void move(int row, int col);
    
    // accessors
    int getRow();
    int getCol();
    
private:
    int m_row;
    int m_col;
};

// ========== Staircase Declaration ==========
class Staircase : public InteractableObject
{
public:
    Staircase();
    virtual ~Staircase();
private:
};


// ========== Idol Declaration ==========
class Idol : public InteractableObject
{
public:
    Idol();
    virtual ~Idol();
private:
    
};

// ========== Weapon Declaration ==========
class Weapon : public InteractableObject
{
public:
    Weapon();
    virtual ~Weapon();
private:
    string m_actionString;
    int m_dexterity;
    int m_damage;
};

class Maces : public InteractableObject
{};

class LongsSword : public InteractableObject
{};

class ShortSword : public InteractableObject
{};

class MagicAxe : public InteractableObject
{};

class MagicFangsOfSleep : public InteractableObject
{};

#endif // INTER_OBJ_H
