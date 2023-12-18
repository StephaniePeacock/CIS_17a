/* 
 * File:   Stooge.h
 * Author: Stephanie Peacock
 * Created on December 10, 2023, 7:16 PM
 * Purpose: Stooge Class Specification
 */

#include "Player.h"
using namespace std;

#ifndef STOOGE_H
#define STOOGE_H

//template <class T>

class Stooge : public Player{
private:

public:
    Stooge() : Player() {}
    Stooge(string s) : Player(s) {}
    virtual ~Stooge() {}

    //Mutators

    //Accessors

    //Other Functions
    virtual void play(Player &p, Stooge **s) ; //Stooge gameplay logic
};

#endif /* STOOGE_H */

