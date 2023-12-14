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
            return this->cnum < right.cnum;
        }
        bool operator >(const Card &right) const {  //for scoring & sorting
            return this->cnum > right.cnum;
        }
        bool operator ==(const Card &right) const { //for setting match status
            return this->suit == right.suit;
        }
        bool operator !=(const Card &right) const { //for setting match status
            return this->suit == right.suit;
        }
        
    //    Card & operator =(const Card &right) { //for setting match status
    //        if(this->cnum != right.cnum){
    //            cnum = right.cnum;
    //        }
    //        return *this;
    //    }
};

#endif /* CARD_H */

