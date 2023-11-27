/* 
 * File:   Card.h
 * Author: Stephanie Peacock
 * Created on November 26, 2023, 9:46 PM
 * Purpose: Deck Class Specification
 */

#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck{
    private:
        int nCards;
        Card **card;
    public:
        Deck();             //constructor - #cards to make
        ~Deck();            //destructor
        void display();
        void shuffle();     //shuffle the deck
    //    void deal(Player & p, int i, const Card& n){ p.addCard(n); }
};

#endif /* DECK_H */

