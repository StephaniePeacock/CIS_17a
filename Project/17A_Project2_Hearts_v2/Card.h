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
        string face;
        int suit;        
    public:
        Card() : cnum(0),face(""), suit(0){}
        Card(int);
        virtual ~Card(){}
        void setFace();
        string getFace()     { return face; }
        int  getCnum()       { return cnum; }
        int  getSuit()       { return suit; }
        //other functions
        bool operator <(const Card &right) const {  //for scoring & sorting
            return cnum < right.cnum;
        }
        bool operator >(const Card &right) const {  //for scoring & sorting
            return cnum > right.cnum;
        }
        bool operator ==(const Card &right) const { //for setting match status
            return suit == right.suit;
        }
};

#endif /* CARD_H */

