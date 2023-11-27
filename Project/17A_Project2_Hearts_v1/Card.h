/* 
 * File:   Card.h
 * Author: Stephanie Peacock
 * Created on November 26, 2023, 9:46 PM
 * Purpose: Card Class Specification
 */

#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

class Card{
    private:
        int  cnum;
        bool used;
        string face;
        int suit;        
    public:
        Card(int);
        void setFace();
        string getFace()     { return face; }
        int  getCnum()       { return cnum; }
        bool isUsed () const { return used; }
        void use ()          { used = true; }
        void reset()         { used = false; }
};

#endif /* CARD_H */

