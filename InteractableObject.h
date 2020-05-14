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
