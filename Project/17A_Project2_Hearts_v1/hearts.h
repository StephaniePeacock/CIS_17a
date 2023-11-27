/* 
 * File:   hearts.h
 * Author: Stephanie Peacock
 * Created on November 25, 2023, 6:45 PM
 */

#ifndef HEARTS_H
#define HEARTS_H

//Constants
const int DECK = 52;    //constant number of cards



enum Order {FIRST,SECOND,THIRD,FOURTH};

class Player{
    private:
        string name;         //C-String to hold player name
        Order  order;        //To determine order for the trick    
        Card   hand[13];     //Holds the player's cards
        int    choice;       //Int value for the player's card
        bool   match;        //Enforce suit
        int    tScore;       //Trick score
        int    score;        //Game score
    public:
        Player(string);     //Player Constructor
        string getName() { return name; }
        void setOrder(Order n) { order = n; }
        Order getOrder() const  {return order; }
        void addCard(const Card& card);
};



// Input function prototypes


#endif /* HEARTS_H */

