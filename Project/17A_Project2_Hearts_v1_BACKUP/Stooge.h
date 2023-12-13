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
    Stooge() : Player() {cout << "Stooge Created" << endl;}
    Stooge(string s) : Player(s) {}
    ~Stooge() {cout << "Deleting Stooge" << endl;}

    //Mutators

    //Accessors

    //Other Functions
    void play(Player &, Stooge **, int) { cout << "Stooge played." << endl; }
};

#endif /* STOOGE_H */

