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
    InteractableObject(int row, int col);        // constructor
    ~InteractableObject();       // destructor
    
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
    ~Staircase();
private:
};


// ========== Idol Declaration ==========
class Idol : public InteractableObject
{
public:
    Idol();
    ~Idol();
private:
    
};

using namespace std;

#endif // INTER_OBJ_H
