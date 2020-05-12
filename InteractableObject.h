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

// ========== InteractableObject Declaration ==========
class InteractableObject
{
public:
    InteractableObject();        // constructor
    ~InteractableObject();       // destructor
    
private:
    int m_row;
    int m_col;
};

using namespace std;

#endif // INTER_OBJ_H
