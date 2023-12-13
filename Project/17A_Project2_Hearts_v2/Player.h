/* 
 * File:   Player.h
 * Author: Stephanie Peacock
 * Created on December 10, 2023, 7:15 PM
 * Purpose: Player Class Specification
 */

#include "AbsPlayer.h"
#include "Deck.h"
#include <iomanip>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

enum Order {FIRST,SECOND,THIRD,FOURTH};

class Stooge;   //Forward Declare Stooge

class Player : public AbsPlayer {
private:
    string name;         //C-String to hold player name
    Order  order;        //To determine order for the trick    
    Card  *hand;         //Holds the player's cards
    int    size;         //current number of cards in the player's hand
    int    choice;       //Int value for the player's card
    bool   match;        //Enforce suit
    int    tScore;       //Trick score
    int    score;        //Game score
public:
    Player();
    Player(string);
    virtual ~Player();
    //Mutators
    void addCard(Card c);  //push back a card to the hand (modifies hand & size)
    void discard(int);   //pop off selected card from the hand (modifies hand & size)
    void setName(string s)  { name = s;   }
    void setOrder(Order ord){ order = ord;}
    void setChoice(int c)   { choice = c; }
    void setMatch(bool m)   { match = m;  }
    void setTrick(int t)    { tScore += t;}
    void resetTrick()       { tScore = 0; }
    void setScore(int sc)   { score = sc; }
    //Accessors
    string getName()        { return name;   }
    Order  getOrder()       { return order;  }
    int    getChoice()      { return choice; }
    bool   getMatch()       { return match;  }
    int    getTrick()       { return tScore; }
    int    getScore()       { return score;  }
    int    getSize()        { return size;   }
    int    getCard(int i)   { return hand[i].getCnum();}
    //Other Functions
    virtual void play(Player &, Stooge **);
    void mSort();
    void print();
    void played(){ cout << getName() << " played " << hand[choice].getFace();}
    
};

#endif /* PLAYER_H */

