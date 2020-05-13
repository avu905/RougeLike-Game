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

// =====================================================
// ========== INTERACTABLE OBJECT DECLARATION ==========
// =====================================================
class InteractableObject
{
public:
//    InteractableObject();                        // non-parameter constructor for weapons
    InteractableObject(int row, int col, char c);        // parameter constructor for staircase and idol
    virtual ~InteractableObject();               // destructor
    
    void move(int row, int col);
    
    // accessors
    int getRow();
    int getCol();
    char getSymbol();
    
private:
    int m_row;
    int m_col;
    char m_symbol;
};

// =====================================================
// ========== PROGRESSION OBJECT DECLARATIONS ==========
// =====================================================
class ProgressionObject : public InteractableObject
{
public:
    ProgressionObject(char c);
    virtual ~ProgressionObject();
private:
};


// ========== STAIRCASE DECLARATION ==========
class Staircase : public ProgressionObject
{
public:
    Staircase();
    virtual ~Staircase();
private:
};


// ========== IDOL DECLARATION ==========
class Idol : public ProgressionObject
{
public:
    Idol();
    virtual ~Idol();
private:
    
};

// =========================================
// ========== WEAPON DECLARATIONS ==========
// =========================================

#endif // INTER_OBJ_H
